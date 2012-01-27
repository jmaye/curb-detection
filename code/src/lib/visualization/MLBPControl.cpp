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

#include "visualization/MLBPControl.h"

#include "visualization/SegmentationControl.h"
#include "helpers/InitML.h"
#include "statistics/EstimatorMLBPMixtureLinearRegression.h"
#include "base/Timestamp.h"

#include "ui_MLBPControl.h"

#include <limits>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

MLBPControl::MLBPControl(bool showMLBP) :
  mUi(new Ui_MLBPControl()),
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
  mMaxIterBP = mUi->maxIterBPSpinBox->value();
  mTolBP =  mUi->tolBPSpinBox->value();
  mWeighted = mUi->weightedCheckBox->isChecked();
  setShowMLBP(showMLBP);
}

MLBPControl::~MLBPControl() {
  delete mUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void MLBPControl::setMaxIter(size_t maxIter) {
  mMaxIter = maxIter;
  mUi->maxIterSpinBox->setValue(maxIter);
}

void MLBPControl::setTolerance(double tol) {
  mTol = tol;
  mUi->tolSpinBox->setValue(tol);
}

void MLBPControl::setShowMLBP(bool showMLBP) {
  mUi->showMLBPCheckBox->setChecked(showMLBP);
  GLView::getInstance().update();
}

void MLBPControl::setWeighted(bool checked) {
  mUi->weightedCheckBox->setChecked(checked);
  mWeighted = checked;
}

void MLBPControl::setMaxIterBP(size_t maxIter) {
  mMaxIterBP = maxIter;
  mUi->maxIterBPSpinBox->setValue(maxIter);
}

void MLBPControl::setToleranceBP(double tol) {
  mTolBP = tol;
  mUi->tolBPSpinBox->setValue(tol);
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void MLBPControl::renderMLBP() {
  const Eigen::Matrix<double, 2, 1>& resolution = mDEM.getResolution();
  glPushAttrib(GL_CURRENT_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  for (DEMGraph::ConstVertexIterator it = mVertices.begin(); it !=
    mVertices.end(); ++it) {
    const Eigen::Matrix<double, 2, 1> point =  mDEM.getCoordinates(it->first);
    const Cell& cell = mDEM[it->first];
    const double sampleMean = cell.getHeightEstimator().getPostPredDist().
      getMean();
    glBegin(GL_QUADS);
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

void MLBPControl::render(GLView& view, Scene& scene) {
  if (mUi->showMLBPCheckBox->isChecked())
    renderMLBP();
}

void MLBPControl::maxIterChanged(int maxIter) {
  setMaxIter(maxIter);
}

void MLBPControl::tolChanged(double tol) {
  setTolerance(tol);
}

void MLBPControl::maxIterBPChanged(int maxIter) {
  setMaxIterBP(maxIter);
}

void MLBPControl::tolBPChanged(double tol) {
  setToleranceBP(tol);
}

void MLBPControl::segmentUpdated(const Grid<double, Cell, 2>& dem, const
  DEMGraph& graph, const GraphSegmenter<DEMGraph>::Components& components, const
  std::vector<Helpers::Color>& colors) {
  mDEM = dem;
  mGraph = graph;
  mComponents = components;
  mColors = colors;
  mVertices = DEMGraph::VertexContainer(10, IndexHash(dem.getNumCells()(1)));
  mUi->runButton->setEnabled(true);
}

void MLBPControl::runMLBP() {
  const double before = Timestamp::now();
  Eigen::Matrix<double, Eigen::Dynamic, 3> c;
  Eigen::Matrix<double, Eigen::Dynamic, 1> v;
  Eigen::Matrix<double, Eigen::Dynamic, 1> w;
  EstimatorBayesImproper<LinearRegression<3>, 3>::Container points;
  std::vector<DEMGraph::VertexDescriptor> pointsMapping;
  if (Helpers::initML(mDEM, mGraph, mComponents, points, pointsMapping, c, v,
    w, mWeighted)) {
    if (c.rows() > 1) {
      EstimatorMLBP<MixtureDistribution<LinearRegression<3>, Eigen::Dynamic>, 3,
        Eigen::Dynamic> estMixtPlane(c, v, w, mMaxIter, mTol, mMaxIterBP,
        mTolBP);
      const size_t numIter = estMixtPlane.addPoints(points.begin(),
        points.end(), mDEM, mGraph, pointsMapping);
      const double after = Timestamp::now();
      mUi->iterSpinBox->setValue(numIter);
      mUi->timeSpinBox->setValue(after - before);
      mUi->llSpinBox->setValue(estMixtPlane.getLogLikelihood());
      std::cout << estMixtPlane.getCoefficients() << std::endl;
      std::cout << estMixtPlane.getVariances() << std::endl;
      mVertices.clear();
      DEMGraph::VertexContainer fgMapping = estMixtPlane.getFgMapping();
      const std::vector<size_t>& mapState = estMixtPlane.getMAPState();
      for (DEMGraph::ConstVertexIterator it = mGraph.getVertexBegin(); it !=
        mGraph.getVertexEnd(); ++it)
        mVertices[it->first] = mapState[fgMapping[it->first]];
      const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>&
        responsibilities = estMixtPlane.getResponsibilities();
      double residual = 0.0;
      for (size_t i = 0; i < (size_t)responsibilities.rows(); ++i) {
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
    }
    else {
      mUi->iterSpinBox->setValue(0);
      mUi->timeSpinBox->setValue(0);
      mUi->llSpinBox->setValue(0);
      std::cout << c << std::endl;
      std::cout << v << std::endl;
      mVertices.clear();
      for (DEMGraph::ConstVertexIterator it = mGraph.getVertexBegin(); it !=
        mGraph.getVertexEnd(); ++it)
        mVertices[it->first] = 0;
    }
    mUi->showMLBPCheckBox->setEnabled(true);
    GLView::getInstance().update();
//    mlUpdated(mDEM, mGraph, estMixtPlane.getCoefficients(),
//      estMixtPlane.getVariances(), estMixtPlane.getWeights(), mColors);
  }
}

void MLBPControl::showMLBPToggled(bool checked) {
  setShowMLBP(checked);
}

void MLBPControl::weightedToggled(bool checked) {
  setWeighted(checked);
}

void MLBPControl::runPressed() {
  runMLBP();
}
