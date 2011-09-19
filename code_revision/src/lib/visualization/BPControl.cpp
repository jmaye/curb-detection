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

#include "visualization/BPControl.h"

#include "visualization/MLControl.h"
#include "helpers/FGTools.h"
#include "data-structures/FactorGraph.h"
#include "data-structures/PropertySet.h"
#include "statistics/BeliefPropagation.h"

#include "ui_BPControl.h"

#include <limits>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

BPControl::BPControl(bool showBP) :
  mUi(new Ui_BPControl()),
  mDEM(Grid<double, Cell, 2>::Coordinate(0.0, 0.0),
    Grid<double, Cell, 2>::Coordinate(4.0, 4.0),
    Grid<double, Cell, 2>::Coordinate(0.1, 0.1)) {
  mUi->setupUi(this);
  connect(&GLView::getInstance().getScene(), SIGNAL(render(GLView&, Scene&)),
    this, SLOT(render(GLView&, Scene&)));
  connect(&MLControl::getInstance(),
    SIGNAL(mlUpdated(const Grid<double, Cell, 2>&, const DEMGraph&,
    const Eigen::Matrix<double, Eigen::Dynamic, 3>&,
    const Eigen::Matrix<double, Eigen::Dynamic, 1>&,
    const Eigen::Matrix<double, Eigen::Dynamic, 1>&)), this,
    SLOT(mlUpdated(const Grid<double, Cell, 2>&, const DEMGraph&,
    const Eigen::Matrix<double, Eigen::Dynamic, 3>&,
    const Eigen::Matrix<double, Eigen::Dynamic, 1>&,
    const Eigen::Matrix<double, Eigen::Dynamic, 1>&)));
  mMaxIter = mUi->maxIterSpinBox->value();
  mTol =  mUi->tolSpinBox->value();
  setShowBP(showBP);
}

BPControl::~BPControl() {
  delete mUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void BPControl::setMaxIter(size_t maxIter) {
  mMaxIter = maxIter;
  mUi->maxIterSpinBox->setValue(maxIter);
}

void BPControl::setTolerance(double tol) {
  mTol = tol;
  mUi->tolSpinBox->setValue(tol);
}

void BPControl::setShowBP(bool showBP) {
  mUi->showBPCheckBox->setChecked(showBP);
  GLView::getInstance().update();
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void BPControl::renderBP() {
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

void BPControl::render(GLView& view, Scene& scene) {
  if (mUi->showBPCheckBox->isChecked())
    renderBP();
}

void BPControl::maxIterChanged(int maxIter) {
  setMaxIter(maxIter);
  runBP();
}

void BPControl::tolChanged(double tol) {
  setTolerance(tol);
  runBP();
}

void BPControl::mlUpdated(const Grid<double, Cell, 2>& dem, const DEMGraph&
  graph, const Eigen::Matrix<double, Eigen::Dynamic, 3>& coefficients,
  const Eigen::Matrix<double, Eigen::Dynamic, 1>& variances,
  const Eigen::Matrix<double, Eigen::Dynamic, 1>& weights) {
  mDEM = dem;
  FactorGraph factorGraph;
  DEMGraph::VertexContainer fgMapping;
  Helpers::buildFactorGraph(dem, graph, coefficients, variances, weights,
    factorGraph, fgMapping);
  PropertySet opts;
  opts.set("maxiter", (size_t)200);
  opts.set("tol", 1e-6);
  opts.set("verbose", (size_t)0);
  opts.set("updates", std::string("SEQRND"));
  opts.set("logdomain", false);
  opts.set("inference", std::string("MAXPROD"));
  BeliefPropagation bp(factorGraph, opts);
  bp.init();
  bp.run();
  std::vector<size_t> mapState = bp.findMaximum();
  mVertices.clear();
  for (DEMGraph::ConstVertexIterator it = graph.getVertexBegin(); it !=
    graph.getVertexEnd(); ++it)
    mVertices[it->first] = mapState[fgMapping[it->first]];
  Helpers::randomColors(mColors, factorGraph.var(0).states());
  mUi->showBPCheckBox->setEnabled(true);
  GLView::getInstance().update();
  bpUpdated(dem, graph, mVertices);
}

void BPControl::runBP() {
}

void BPControl::showBPToggled(bool checked) {
  setShowBP(checked);
}
