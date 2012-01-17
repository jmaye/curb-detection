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
#include "statistics/EstimatorML.h"
#include "helpers/InitML.h"
#include "base/Timestamp.h"
#include "utils/IndexHash.h"

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
    GraphSegmenter<DEMGraph>::Components&, const std::vector<Helpers::Color>&)),
    this,
    SLOT(segmentUpdated(const Grid<double, Cell, 2>&, const DEMGraph&, const
    GraphSegmenter<DEMGraph>::Components&, const
    std::vector<Helpers::Color>&)));
  mMaxIter = mUi->maxIterSpinBox->value();
  mTol =  mUi->tolSpinBox->value();
  mWeighted = mUi->weightedCheckBox->isChecked();
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

void MLControl::setWeighted(bool checked) {
  mUi->weightedCheckBox->setChecked(checked);
  mWeighted = checked;
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
    const double sampleMean = cell.getHeightEstimator().getPostPredDist().
      getMean();
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
}

void MLControl::tolChanged(double tol) {
  setTolerance(tol);
}

void MLControl::segmentUpdated(const Grid<double, Cell, 2>& dem, const DEMGraph&
  graph, const GraphSegmenter<DEMGraph>::Components& components, const
  std::vector<Helpers::Color>& colors) {
  mDEM = dem;
  mGraph = graph;
  mComponents = components;
  mColors = colors;
  mVertices = DEMGraph::VertexContainer(10, IndexHash(dem.getNumCells()(1)));
  mUi->runButton->setEnabled(true);
}

void MLControl::runML() {
  const double before = Timestamp::now();
  Eigen::Matrix<double, Eigen::Dynamic, 3> c;
  Eigen::Matrix<double, Eigen::Dynamic, 1> v;
  Eigen::Matrix<double, Eigen::Dynamic, 1> w;
  EstimatorBayesImproper<LinearRegression<3>, 3>::Container points;
  std::vector<DEMGraph::VertexDescriptor> pointsMapping;
  if (Helpers::initML(mDEM, mGraph, mComponents, points, pointsMapping, c, v,
    w, mWeighted)) {
    EstimatorML<MixtureDistribution<LinearRegression<3>, Eigen::Dynamic>, 3,
      Eigen::Dynamic> estMixtPlane(c, v, w, mMaxIter, mTol);
    const size_t numIter = estMixtPlane.addPoints(points.begin(), points.end());
    const double after = Timestamp::now();
    mUi->iterSpinBox->setValue(numIter);
    mUi->timeSpinBox->setValue(after - before);
    mUi->llSpinBox->setValue(estMixtPlane.getLogLikelihood());
    std::cout << estMixtPlane.getCoefficients() << std::endl;
    std::cout << estMixtPlane.getVariances() << std::endl;
    const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>&
      responsibilities = estMixtPlane.getResponsibilities();
    double residual = 0.0;
    for (size_t i = 0; i < (size_t)responsibilities.rows(); ++i) {
      double max = -std::numeric_limits<double>::infinity();
      size_t argmax = 0;
      for (size_t j = 0; j < (size_t)responsibilities.cols(); ++j)
        if (responsibilities(i, j) > max) {
          max = responsibilities(i, j);
          argmax = j;
        }
      mVertices[pointsMapping[i]] = argmax;
      Eigen::Matrix<double, 3, 1> point;
      point(0) = 1.0;
      point.segment(1, 2) = mDEM.getCoordinates(pointsMapping[i]);
      double prediction =
        (estMixtPlane.getCoefficients().row(mVertices[pointsMapping[i]]) *
        point)(0);
      residual += fabs(prediction -
        mDEM[pointsMapping[i]].getHeightEstimator().
        getPostPredDist().getMean());
    }
    residual /= (size_t)responsibilities.rows();
    mUi->residualSpinBox->setValue(residual);
    mUi->showMLCheckBox->setEnabled(true);
    GLView::getInstance().update();
    emit mlUpdated(mDEM, mGraph, estMixtPlane.getCoefficients(),
      estMixtPlane.getVariances(), estMixtPlane.getWeights(), mColors);
  }
}

void MLControl::showMLToggled(bool checked) {
  setShowML(checked);
}

void MLControl::weightedToggled(bool checked) {
  setWeighted(checked);
}

void MLControl::runPressed() {
  runML();
}
