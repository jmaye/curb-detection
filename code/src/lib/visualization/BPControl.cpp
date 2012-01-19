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
#include "data-structures/PropertySet.h"
#include "statistics/BeliefPropagation.h"
#include "base/Timestamp.h"
#include "utils/IndexHash.h"
#include "visualization/SegmentationControl.h"

#include "ui_BPControl.h"

#include <limits>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

BPControl::BPControl(bool showBP) :
  mUi(new Ui_BPControl()),
  mDEM(Grid<double, Cell, 2>::Coordinate(0.0, 0.0),
    Grid<double, Cell, 2>::Coordinate(4.0, 4.0),
    Grid<double, Cell, 2>::Coordinate(0.1, 0.1)),
  mGraph(mDEM) {
  mUi->setupUi(this);
  connect(&GLView::getInstance().getScene(), SIGNAL(render(GLView&, Scene&)),
    this, SLOT(render(GLView&, Scene&)));
  connect(&MLControl::getInstance(),
    SIGNAL(mlUpdated(const Grid<double, Cell, 2>&, const DEMGraph&,
    const Eigen::Matrix<double, Eigen::Dynamic, 3>&,
    const Eigen::Matrix<double, Eigen::Dynamic, 1>&,
    const Eigen::Matrix<double, Eigen::Dynamic, 1>&,
    const std::vector<Helpers::Color>&)), this,
    SLOT(mlUpdated(const Grid<double, Cell, 2>&, const DEMGraph&,
    const Eigen::Matrix<double, Eigen::Dynamic, 3>&,
    const Eigen::Matrix<double, Eigen::Dynamic, 1>&,
    const Eigen::Matrix<double, Eigen::Dynamic, 1>&,
    const std::vector<Helpers::Color>&)));
  connect(&SegmentationControl::getInstance(),
    SIGNAL(segmentUpdated(const Grid<double, Cell, 2>&, const DEMGraph&, const
    GraphSegmenter<DEMGraph>::Components&, const std::vector<Helpers::Color>&)),
    this,
    SLOT(segmentUpdated(const Grid<double, Cell, 2>&, const DEMGraph&, const
    GraphSegmenter<DEMGraph>::Components&, const
    std::vector<Helpers::Color>&)));
  mMaxIter = mUi->maxIterSpinBox->value();
  mTol =  mUi->tolSpinBox->value();
  mLogDomain = mUi->logDomainCheckBox->isChecked();
  mStrength = mUi->strengthSpinBox->value();
  if (mUi->parallButton->isChecked())
    setParallUpdates(true);
  if (mUi->seqfixButton->isChecked())
    setSeqFixUpdates(true);
  if (mUi->seqrndButton->isChecked())
    setSeqRndUpdates(true);
  if (mUi->seqmaxButton->isChecked())
    setSeqMaxUpdates(true);
  if (mUi->maxProdButton->isChecked())
    setMaxProd(true);
  if (mUi->sumProdButton->isChecked())
    setSumProd(true);
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

void BPControl::setStrength(double strength) {
  mStrength = strength;
  mUi->strengthSpinBox->setValue(strength);
  Helpers::buildFactorGraph(mDEM, mGraph, mCoefficients, mVariances, mWeights,
    mFactorGraph, mFgMapping, mStrength);
}

void BPControl::setTolerance(double tol) {
  mTol = tol;
  mUi->tolSpinBox->setValue(tol);
}

void BPControl::setShowBP(bool showBP) {
  mUi->showBPCheckBox->setChecked(showBP);
  GLView::getInstance().update();
}

void BPControl::setLogDomain(bool checked) {
  mUi->logDomainCheckBox->setChecked(checked);
  mLogDomain = checked;
}

void BPControl::setParallUpdates(bool checked) {
  mUi->parallButton->setChecked(checked);
  if (checked)
    mUpdates = std::string("PARALL");
}

void BPControl::setSeqFixUpdates(bool checked) {
  mUi->seqfixButton->setChecked(checked);
  if (checked)
    mUpdates = std::string("SEQFIX");
}

void BPControl::setSeqRndUpdates(bool checked) {
  mUi->seqrndButton->setChecked(checked);
  if (checked)
    mUpdates = std::string("SEQRND");
}

void BPControl::setSeqMaxUpdates(bool checked) {
  mUi->seqmaxButton->setChecked(checked);
  if (checked)
    mUpdates = std::string("SEQMAX");
}

void BPControl::setMaxProd(bool checked) {
  mUi->maxProdButton->setChecked(checked);
  if (checked)
    mAlgo = std::string("MAXPROD");
}

void BPControl::setSumProd(bool checked) {
  mUi->sumProdButton->setChecked(checked);
  if (checked)
    mAlgo = std::string("SUMPROD");
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
}

void BPControl::strengthChanged(double strength) {
  setStrength(strength);
}

void BPControl::tolChanged(double tol) {
  setTolerance(tol);
}

void BPControl::mlUpdated(const Grid<double, Cell, 2>& dem, const DEMGraph&
  graph, const Eigen::Matrix<double, Eigen::Dynamic, 3>& coefficients,
  const Eigen::Matrix<double, Eigen::Dynamic, 1>& variances,
  const Eigen::Matrix<double, Eigen::Dynamic, 1>& weights,
  const std::vector<Helpers::Color>& colors) {
  mDEM = dem;
  mGraph = graph;
  mCoefficients = coefficients;
  mVariances = variances;
  mWeights = weights;
  Helpers::buildFactorGraph(dem, graph, coefficients, variances, weights,
    mFactorGraph, mFgMapping, mStrength);
  mColors = colors;
  mVertices = DEMGraph::VertexContainer(10, IndexHash(dem.getNumCells()(1)));
  mUi->runButton->setEnabled(true);
  mUi->strengthSpinBox->setEnabled(true);
}

void BPControl::runBP() {
  std::vector<size_t> mapState;
  mapState.reserve(mFactorGraph.nrVars());
  if (mFactorGraph.factors()[0].nrStates() > 1) {
    const double before = Timestamp::now();
    PropertySet opts;
    opts.set("maxiter", (size_t)mMaxIter);
    opts.set("tol", mTol);
    opts.set("verbose", (size_t)0);
    opts.set("updates", mUpdates);
    opts.set("logdomain", mLogDomain);
    opts.set("inference", mAlgo);
    BeliefPropagation bp(mFactorGraph, opts);
    bp.init();
    bp.run();
    const double after = Timestamp::now();
    mUi->iterSpinBox->setValue(bp.Iterations());
    mUi->llSpinBox->setValue(bp.logZ());
    mUi->timeSpinBox->setValue(after - before);
    if (mAlgo.compare("MAXPROD") == 0)
      mapState = bp.findMaximum();
    else {
      for (size_t i = 0; i < mFactorGraph.nrVars(); ++i) {
        const dai::Factor factor = bp.beliefV(i);
        double max = -std::numeric_limits<double>::infinity();
        size_t argmax = 0;
        for (size_t j = 0; j < factor.nrStates(); ++j)
          if (factor[j] > max) {
            max = factor[j];
            argmax = j;
          }
        mapState.push_back(argmax);
      }
    }
  }
  else {
    mUi->timeSpinBox->setValue(0.0);
    for (size_t i = 0; i < mFactorGraph.nrVars(); ++i)
      mapState.push_back(0);
  }
  mVertices.clear();
  for (DEMGraph::ConstVertexIterator it = mGraph.getVertexBegin(); it !=
    mGraph.getVertexEnd(); ++it)
    mVertices[it->first] = mapState[mFgMapping[it->first]];
  mUi->showBPCheckBox->setEnabled(true);
  GLView::getInstance().update();
  emit bpUpdated(mDEM, mGraph, mVertices);
}

void BPControl::showBPToggled(bool checked) {
  setShowBP(checked);
}

void BPControl::logDomainToggled(bool checked) {
  setLogDomain(checked);
}

void BPControl::parallToggled(bool checked) {
  setParallUpdates(checked);
}

void BPControl::seqfixToggled(bool checked) {
  setSeqFixUpdates(checked);
}

void BPControl::seqrndToggled(bool checked) {
  setSeqRndUpdates(checked);
}

void BPControl::seqmaxToggled(bool checked) {
  setSeqMaxUpdates(checked);
}

void BPControl::maxProdToggled(bool checked) {
  setMaxProd(checked);
}

void BPControl::sumProdToggled(bool checked) {
  setSumProd(checked);
}

void BPControl::runPressed() {
  runBP();
}

void BPControl::segmentUpdated(const Grid<double, Cell, 2>& dem, const DEMGraph&
  graph, const GraphSegmenter<DEMGraph>::Components& components, const
  std::vector<Helpers::Color>& colors) {
  mVertices.clear();
  mUi->runButton->setEnabled(false);
  GLView::getInstance().update();
}
