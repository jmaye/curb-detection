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

#include <limits>

#include "statistics/EstimatorML.h"
#include "data-structures/PropertySet.h"
#include "ml/BeliefPropagation.h"
#include "helpers/FGTools.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t N, size_t M>
EstimatorMLBP<MixtureDistribution<LinearRegression<N>, M> >::EstimatorMLBP(const
    MixtureDistribution<LinearRegression<N>, M>& initDist, const
    Grid<double, Cell, 2>& dem, const DEMGraph& graph,
    std::vector<DEMGraph::VertexDescriptor>& pointsMapping, size_t maxNumIter,
    double tol) :
    mMixtureDist(initDist),
    mDEM(dem),
    mGraph(graph),
    mPointsMapping(pointsMapping),
    mLogLikelihood(0),
    mMaxNumIter(maxNumIter),
    mTol(tol),
    mNumPoints(0),
    mValid(false) {
    Helpers::buildFactorGraph(mDEM, mGraph, mMixtureDist, mFactorGraph,
      mFgMapping);
}

template <size_t N, size_t M>
EstimatorMLBP<MixtureDistribution<LinearRegression<N>, M> >::
    EstimatorMLBP(const EstimatorMLBP& other) :
    mMixtureDist(other.mMixtureDist),
    mDEM(other.mDEM),
    mGraph(other.mGraph),
    mPointsMapping(other.mPointsMapping),
    mFactorGraph(other.mFactorGraph),
    mFgMapping(other.mFgMapping),
    mResponsibilities(other.mResponsibilities),
    mLogLikelihood(other.mLogLikelihood),
    mMaxNumIter(other.mMaxNumIter),
    mTol(other.mTol),
    mNumPoints(other.mNumPoints),
    mValid(other.mValid) {
}

template <size_t N, size_t M>
EstimatorMLBP<MixtureDistribution<LinearRegression<N>, M> >&
    EstimatorMLBP<MixtureDistribution<LinearRegression<N>, M> >::
    operator = (const EstimatorMLBP& other) {
  if (this != &other) {
    mMixtureDist = other.mMixtureDist;
    mDEM = other.mDEM;
    mGraph = other.mGraph;
    mPointsMapping = other.mPointsMapping;
    mFactorGraph = other.mFactorGraph;
    mFgMapping = other.mFgMapping;
    mResponsibilities = other.mResponsibilities;
    mLogLikelihood = other.mLogLikelihood;
    mMaxNumIter = other.mMaxNumIter;
    mTol = other.mTol;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
  }
  return *this;
}

template <size_t N, size_t M>
EstimatorMLBP<MixtureDistribution<LinearRegression<N>, M> >::~EstimatorMLBP() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t N, size_t M>
void EstimatorMLBP<MixtureDistribution<LinearRegression<N>, M> >::
    read(std::istream& stream) {
}

template <size_t N, size_t M>
void EstimatorMLBP<MixtureDistribution<LinearRegression<N>, M> >::
    write(std::ostream& stream) const {
  stream << "mixture distribution: " << std::endl << mMixtureDist << std::endl
    << "log-likelihood: " << mLogLikelihood << std::endl
    << "maxNumIter: " << mMaxNumIter << std::endl
    << "tolerance: " << mTol << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

template <size_t N, size_t M>
void EstimatorMLBP<MixtureDistribution<LinearRegression<N>, M> >::
    read(std::ifstream& stream) {
}

template <size_t N, size_t M>
void EstimatorMLBP<MixtureDistribution<LinearRegression<N>, M> >::
    write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t N, size_t M>
const MixtureDistribution<LinearRegression<N>, M>&
    EstimatorMLBP<MixtureDistribution<LinearRegression<N>, M> >::
    getMixtureDist() const {
  return mMixtureDist;
}

template <size_t N, size_t M>
const Eigen::Matrix<double, Eigen::Dynamic, M>&
    EstimatorMLBP<MixtureDistribution<LinearRegression<N>, M> >::
    getResponsibilities() const {
  return mResponsibilities;
}

template <size_t N, size_t M>
size_t EstimatorMLBP<MixtureDistribution<LinearRegression<N>, M> >::
    getNumPoints() const {
  return mNumPoints;
}

template <size_t N, size_t M>
bool EstimatorMLBP<MixtureDistribution<LinearRegression<N>, M> >::getValid()
    const {
  return mValid;
}

template <size_t N, size_t M>
double EstimatorMLBP<MixtureDistribution<LinearRegression<N>, M> >::
    getLogLikelihood() const {
  return mLogLikelihood;
}

template <size_t N, size_t M>
double EstimatorMLBP<MixtureDistribution<LinearRegression<N>, M> >::
    getTolerance() const {
  return mTol;
}

template <size_t N, size_t M>
void EstimatorMLBP<MixtureDistribution<LinearRegression<N>, M> >::
    setTolerance(double tol) {
  mTol = tol;
}

template <size_t N, size_t M>
size_t EstimatorMLBP<MixtureDistribution<LinearRegression<N>, M> >::
    getMaxNumIter() const {
  return mMaxNumIter;
}

template <size_t N, size_t M>
void EstimatorMLBP<MixtureDistribution<LinearRegression<N>, M> >::
    setMaxNumIter(size_t maxNumIter) {
  mMaxNumIter = maxNumIter;
}

template <size_t N, size_t M>
void EstimatorMLBP<MixtureDistribution<LinearRegression<N>, M> >::reset() {
  mLogLikelihood = 0;
  mNumPoints = 0;
  mValid = false;
}

template <size_t N, size_t M>
size_t EstimatorMLBP<MixtureDistribution<LinearRegression<N>, M> >::
    addPointsEM(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd) {
  reset();
  size_t numIter = 0;
  const size_t K = mMixtureDist.getCompDistributions().size();
  mNumPoints = itEnd - itStart;
  if (mNumPoints == 0)
    return numIter;
  mResponsibilities.resize(mNumPoints, K);
  mLogLikelihood = -std::numeric_limits<double>::infinity();
  PropertySet opts;
  opts.set("maxiter", (size_t)200);
  opts.set("tol", 1e-9);
  opts.set("verbose", (size_t)0);
  opts.set("updates", std::string("SEQRND"));
  opts.set("logdomain", false);
  opts.set("inference", std::string("SUMPROD"));
  while (numIter != mMaxNumIter) {
    mValid = true;
    BeliefPropagation bp(mFactorGraph, opts);
    bp.init();
    try {
      bp.run();
    }
    catch (dai::Exception& e) {
      std::cout << e.what() << std::endl;
      mValid = false;
      break;
    }
    std::vector<dai::Factor> factors;
    factors.reserve(mFactorGraph.nrVars());
    for (size_t i = 0; i < mFactorGraph.nrVars(); ++i)
      factors.push_back(bp.beliefV(i));
    Eigen::Matrix<double, M, 1> numPoints =
      Eigen::Matrix<double, M, 1>::Zero(K);
    for (auto it = itStart; it != itEnd; ++it) {
      const size_t row = it - itStart;
      for (size_t j = 0 ; j < K; ++j)
        mResponsibilities(row, j) = factors[mFgMapping[mPointsMapping[row]]][j];
      numPoints += mResponsibilities.row(row).transpose();
    }
    const double logLikelihood = bp.logZ();
    if (fabs(mLogLikelihood - logLikelihood) < mTol)
      break;
    mLogLikelihood = logLikelihood;
    try {
      mMixtureDist.setAssignDistribution(CategoricalDistribution<M>(
        numPoints / mNumPoints));
      for (size_t j = 0; j < K; ++j) {
        EstimatorML<LinearRegression<N> > estComp;
        estComp.addPoints(itStart, itEnd, mResponsibilities.col(j));
        if (estComp.getValid())
          mMixtureDist.setCompDistribution(estComp.getDistribution(), j);
      }
    }
    catch (...) {
      mValid = false;
    }
    Helpers::updateNodeFactors(mDEM, mGraph, mMixtureDist, mFactorGraph,
      mFgMapping);
    numIter++;
  }
  return numIter;
}

template <size_t N, size_t M>
DEMGraph::VertexContainer
    EstimatorMLBP<MixtureDistribution<LinearRegression<N>, M> >::
    getVerticesLabels() {
  PropertySet opts;
  opts.set("maxiter", (size_t)200);
  opts.set("tol", 1e-9);
  opts.set("verbose", (size_t)0);
  opts.set("updates", std::string("SEQRND"));
  opts.set("logdomain", false);
  opts.set("inference", std::string("MAXPROD"));
  BeliefPropagation bp(mFactorGraph, opts);
  bp.init();
  bp.run();
  std::vector<size_t> mapState;
  mapState.reserve(mFactorGraph.nrVars());
  mapState = bp.findMaximum();
  DEMGraph::VertexContainer vertices;
  for (auto it = mGraph.getVertexBegin(); it != mGraph.getVertexEnd(); ++it)
    vertices[it->first] = mapState[mFgMapping[it->first]];
  return vertices;
}
