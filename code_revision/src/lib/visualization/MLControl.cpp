/******************************************************************************
 * Copyright (C) 2011 by Jerome Maye                                          *
 * jerome.maye@gmail.com                                                      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

#include "visualization/MLControl.h"

#include "visualization/SegmentationControl.h"
#include "statistics/EstimatorMLBPMixtureLinearRegression.h"
#include "helpers/InitML.h"
#include "helpers/FGTools.h"
#include "statistics/BeliefPropagation.h"

#include "ui_MLControl.h"

#include <limits>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

MLControl::MLControl(bool showML) :
  mUi(new Ui_MLControl()),
  mDEM(Grid<double, Cell, 2>::Coordinate(0.0, 0.0),
    Grid<double, Cell, 2>::Coordinate(4.0, 4.0),
    Grid<double, Cell, 2>::Coordinate(0.1, 0.1)),
  mGraph(mDEM) {
  mUi->setupUi(this);
  connect(&GLView::getInstance().getScene(), SIGNAL(render(GLView&, Scene&)),
    this, SLOT(render(GLView&, Scene&)));
  connect(&SegmentationControl::getInstance(),
    SIGNAL(segmentUpdated(const Grid<double, Cell, 2>&, const DEMGraph&, const
    GraphSegmenter<DEMGraph>::Components&)), this,
    SLOT(segmentUpdated(const Grid<double, Cell, 2>&, const DEMGraph&, const
    GraphSegmenter<DEMGraph>::Components&)));
  mMaxIter = mUi->maxIterSpinBox->value();
  mTol =  mUi->tolSpinBox->value();
  setShowML(showML);
}

MLControl::~MLControl() {
  delete mUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void MLControl::setMaxIter(size_t maxIter) {
  mMaxIter = maxIter;
  mUi->maxIterSpinBox->setValue(maxIter);
}

void MLControl::setTolerance(double tol) {
  mTol = tol;
  mUi->tolSpinBox->setValue(tol);
}

void MLControl::setShowML(bool showML) {
  mUi->showMLCheckBox->setChecked(showML);
  GLView::getInstance().update();
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void MLControl::renderML() {
  const Eigen::Matrix<double, 2, 1>& resolution = mDEM.getResolution();
  glPushAttrib(GL_CURRENT_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  for (DEMGraph::ConstVertexIterator it = mVertices.begin(); it !=
    mVertices.end(); ++it) {
    const Eigen::Matrix<double, 2, 1> point =  mDEM.getCoordinates(it->first);
    const Cell& cell = mDEM[it->first];
    const double sampleMean = cell.getHeightEstimator().getMean();
    glBegin(GL_POLYGON);
    glColor3f(mColors[it->second].mRedColor, mColors[it->second].mGreenColor,
      mColors[it->second].mBlueColor);
    glVertex3f(point(0) + resolution(0) / 2.0, point(1) + resolution(1) / 2.0,
      sampleMean);
    glVertex3f(point(0) + resolution(0) / 2.0, point(1) - resolution(1) / 2.0,
      sampleMean);
    glVertex3f(point(0) - resolution(0) / 2.0, point(1) - resolution(1) / 2.0,
      sampleMean);
    glVertex3f(point(0) - resolution(0) / 2.0, point(1) + resolution(1) / 2.0,
      sampleMean);
    glEnd();
  }
  glPopAttrib();
}

void MLControl::render(GLView& view, Scene& scene) {
  if (mUi->showMLCheckBox->isChecked())
    renderML();
}

void MLControl::maxIterChanged(int maxIter) {
  setMaxIter(maxIter);
  runML();
}

void MLControl::tolChanged(double tol) {
  setTolerance(tol);
  runML();
}

void MLControl::segmentUpdated(const Grid<double, Cell, 2>& dem, const DEMGraph&
  graph, const GraphSegmenter<DEMGraph>::Components& components) {
  mDEM = dem;
  mGraph = graph;
  if (Helpers::initML(dem, graph, components, mPoints, mPointsWeights,
    mPointsMapping, mC, mV, mW)) {
    Helpers::randomColors(mColors, components.size());
    Helpers::buildFactorGraph(dem, graph, mC, mV, mW, mFactorGraph, mFgMapping);
    runML();
  }
}

void MLControl::runML() {
  if (mPoints.size()) {
  EstimatorMLBP<MixtureDistribution<LinearRegression<3>, Eigen::Dynamic>, 3,
    Eigen::Dynamic> estMixtBPPlane(mC, mW, mW, mMaxIter, mTol);
//  const size_t numIter = estMixtBPPlane.addPoints(mPoints.begin(),
//    mPoints.end(), mFactorGraph, mFgMapping, mPointsMapping, mDEM, mGraph);
    EstimatorML<MixtureDistribution<LinearRegression<3>, Eigen::Dynamic>, 3,
      Eigen::Dynamic> estMixtPlane(mC, mV, mW, mMaxIter, mTol);
    const size_t numIter = estMixtPlane.addPoints(mPoints.begin(),
      mPoints.end());
    PropertySet opts;
    opts.set("maxiter", (size_t)200);
    opts.set("tol", 1e-6);
    opts.set("verbose", (size_t)1);
    opts.set("updates", std::string("SEQRND"));
    opts.set("logdomain", false);
    opts.set("inference", std::string("MAXPROD"));
    BeliefPropagation bp(mFactorGraph, opts);
    bp.init();
    bp.run();
    std::vector<std::size_t> mapState = bp.findMaximum();
    mUi->iterSpinBox->setValue(numIter);
    const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>&
      responsibilities = estMixtPlane.getResponsibilities();
    mVertices.clear();
    for (size_t i = 0; i < (size_t)responsibilities.rows(); ++i) {
      double max = -std::numeric_limits<double>::infinity();
      size_t argmax = 0;
      for (size_t j = 0; j < (size_t)responsibilities.cols(); ++j)
        if (responsibilities(i, j) > max) {
          max = responsibilities(i, j);
          argmax = j;
        }
      mVertices[mPointsMapping[i]] = argmax;
//        mVertices[mPointsMapping[i]] = mapState[mFgMapping[mPointsMapping[i]]];
    }
    mUi->showMLCheckBox->setEnabled(true);
    GLView::getInstance().update();
    mlUpdated(mDEM, mGraph, estMixtPlane.getCoefficients(),
      estMixtPlane.getVariances(), estMixtPlane.getWeights());
  }
}

void MLControl::showMLToggled(bool checked) {
  setShowML(checked);
}
