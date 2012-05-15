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

#include <limits>

#include "visualization/SegmentationControl.h"
#include "statistics/EstimatorMLBPMixtureLinearRegression.h"
#include "helpers/InitML.h"
#include "base/Timestamp.h"
#include "utils/IndexHash.h"
#include "data-structures/TransGrid.h"
#include "data-structures/Cell.h"
#include "utils/Colors.h"

#include "ui_MLBPControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

MLBPControl::MLBPControl(bool showML) :
    mUi(new Ui_MLBPControl()),
    mDEM(0),
    mGraph(0),
    mMixtureDist(0) {
  mUi->setupUi(this);
  connect(&View3d::getInstance().getScene(), SIGNAL(render(View3d&, Scene3d&)),
    this, SLOT(render(View3d&, Scene3d&)));
  connect(&SegmentationControl::getInstance(),
    SIGNAL(segmentUpdated(const TransGrid<double, Cell, 2>&, const DEMGraph&,
    const GraphSegmenter<DEMGraph>::Components&)),
    this,
    SLOT(segmentUpdated(const TransGrid<double, Cell, 2>&, const DEMGraph&,
    const GraphSegmenter<DEMGraph>::Components&)));
  mMaxIter = mUi->maxIterSpinBox->value();
  mTol =  mUi->tolSpinBox->value();
  mWeighted = mUi->weightedCheckBox->isChecked();
  setShowML(showML);
}

MLBPControl::~MLBPControl() {
  if (mDEM)
    delete mDEM;
  if (mGraph)
    delete mGraph;
  if (mMixtureDist)
    delete mMixtureDist;
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

void MLBPControl::setShowML(bool showML) {
  mUi->showMLCheckBox->setChecked(showML);
  View3d::getInstance().update();
}

void MLBPControl::setWeighted(bool checked) {
  mUi->weightedCheckBox->setChecked(checked);
  mWeighted = checked;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void MLBPControl::renderML() {
  glPushAttrib(GL_CURRENT_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  for (auto it = mVertices.begin(); it != mVertices.end(); ++it) {
    Grid<double, Cell, 2>::Coordinate ulPoint =
      mDEM->getULCoordinates(it->first);
    Grid<double, Cell, 2>::Coordinate urPoint =
      mDEM->getURCoordinates(it->first);
    Grid<double, Cell, 2>::Coordinate lrPoint =
      mDEM->getLRCoordinates(it->first);
    Grid<double, Cell, 2>::Coordinate llPoint =
      mDEM->getLLCoordinates(it->first);
    auto color = Colors::genColor(it->second);
    glBegin(GL_QUADS);
    glColor3f(color.mRed, color.mGreen, color.mBlue);
    glVertex3f(ulPoint(0), ulPoint(1),
      mMixtureDist->getCompDistribution(it->second).
      getLinearBasisFunction()(ulPoint));
    glVertex3f(urPoint(0), urPoint(1),
      mMixtureDist->getCompDistribution(it->second).
      getLinearBasisFunction()(urPoint));
    glVertex3f(lrPoint(0), lrPoint(1),
      mMixtureDist->getCompDistribution(it->second).
      getLinearBasisFunction()(lrPoint));
    glVertex3f(llPoint(0), llPoint(1),
      mMixtureDist->getCompDistribution(it->second).
      getLinearBasisFunction()(llPoint));
    glEnd();
  }
  glPopAttrib();
}

void MLBPControl::render(View3d& view, Scene3d& scene) {
  if (mUi->showMLCheckBox->isChecked() && mDEM)
    renderML();
}

void MLBPControl::maxIterChanged(int maxIter) {
  setMaxIter(maxIter);
}

void MLBPControl::tolChanged(double tol) {
  setTolerance(tol);
}

void MLBPControl::segmentUpdated(const TransGrid<double, Cell, 2>& dem, const
    DEMGraph& graph, const GraphSegmenter<DEMGraph>::Components& components) {
  if (mDEM)
    delete mDEM;
  mDEM = new TransGrid<double, Cell, 2>(dem);
  if (mGraph)
    delete mGraph;
  mGraph = new DEMGraph(graph);
  mComponents = components;
  mVertices = DEMGraph::VertexContainer(10, IndexHash(dem.getNumCells()(1)));
  mUi->runButton->setEnabled(true);
}

void MLBPControl::runML() {
  const double before = Timestamp::now();
  EstimatorML<LinearRegression<3> >::Container points;
  std::vector<DEMGraph::VertexDescriptor> pointsMapping;
  MixtureDistribution<LinearRegression<3>, Eigen::Dynamic>* initMixture = 0;
  mVertices.clear();
  if (Helpers::initML(*mDEM, *mGraph, mComponents, points, pointsMapping,
      initMixture, mWeighted)) {
    if (initMixture->getCompDistributions().size() > 1) {
      EstimatorMLBP<MixtureDistribution<LinearRegression<3>, Eigen::Dynamic> >
        estMixtPlane(*initMixture, *mDEM, *mGraph, pointsMapping, mMaxIter,
        mTol);
      const size_t numIter = estMixtPlane.addPointsEM(points.begin(),
        points.end());
      if (estMixtPlane.getValid()) {
        const double after = Timestamp::now();
        mUi->iterSpinBox->setValue(numIter);
        mUi->timeSpinBox->setValue(after - before);
        mUi->llSpinBox->setValue(estMixtPlane.getLogLikelihood());
        mVertices = estMixtPlane.getVerticesLabels();
        if (mMixtureDist)
          delete mMixtureDist;
        mMixtureDist =
          new MixtureDistribution<LinearRegression<3>, Eigen::Dynamic>(
          estMixtPlane.getMixtureDist());
      }
      else
        return;
    }
    else {
      for (auto it = mGraph->getVertexBegin(); it != mGraph->getVertexEnd();
          ++it)
        mVertices[it->first] = 0;
      if (mMixtureDist)
        delete mMixtureDist;
      mMixtureDist =
        new MixtureDistribution<LinearRegression<3>, Eigen::Dynamic>(
        *initMixture);
    }
    double residual = 0.0;
    for (auto it = mVertices.begin(); it != mVertices.end(); ++it) {
      double prediction = mMixtureDist->
        getCompDistribution(it->second).getLinearBasisFunction()
            (mDEM->getCoordinates(it->first));
        residual += fabs(prediction - std::get<0>(
          (*mDEM)[it->first].getHeightEstimator().
          getDist().getMode()));
    }
    residual /= mVertices.size();
    mUi->residualSpinBox->setValue(residual);
    mUi->showMLCheckBox->setEnabled(true);
    View3d::getInstance().update();
  }
  if (initMixture)
    delete initMixture;
}

void MLBPControl::showMLToggled(bool checked) {
  setShowML(checked);
}

void MLBPControl::weightedToggled(bool checked) {
  setWeighted(checked);
}

void MLBPControl::runPressed() {
  if (mDEM)
    runML();
}
