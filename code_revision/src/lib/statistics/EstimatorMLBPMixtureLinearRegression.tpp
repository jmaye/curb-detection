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

#include "statistics/BeliefPropagation.h"
#include "data-structures/PropertySet.h"
#include "helpers/FGTools.h"

#include <Eigen/QR>

#include <limits>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M, size_t N>
EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>::EstimatorMLBP(
  const Eigen::Matrix<double, N, M>& coefficients,
  const Eigen::Matrix<double, N, 1>& variances,
  const Eigen::Matrix<double, N, 1>& weights, size_t maxNumIter, double tol) :
  mCoefficients(coefficients),
  mVariances(variances),
  mWeights(weights),
  mMaxNumIter(maxNumIter),
  mTol(tol),
  mNumPoints(0),
  mValid(false) {
}

template <size_t M, size_t N>
EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>::EstimatorMLBP(
  const EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>&
  other) :
  mCoefficients(other.mCoefficients),
  mVariances(other.mVariances),
  mResponsibilities(other.mResponsibilities),
  mWeights(other.mWeights),
  mMaxNumIter(other.mMaxNumIter),
  mTol(other.mTol),
  mNumPoints(other.mNumPoints),
  mValid(other.mValid) {
}

template <size_t M, size_t N>
EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>&
  EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>::operator =
  (const EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>&
  other) {
  if (this != &other) {
    mCoefficients = other.mCoefficients;
    mVariances = other.mVariances;
    mResponsibilities = other.mResponsibilities;
    mWeights = other.mWeights;
    mMaxNumIter = other.mMaxNumIter;
    mTol = other.mTol;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
  }
  return *this;
}

template <size_t M, size_t N>
EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>
::~EstimatorMLBP() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M, size_t N>
void EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>::read(
  std::istream& stream) {
}

template <size_t M, size_t N>
void EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>::write(
  std::ostream& stream) const {
  stream << "coefficients: " << std::endl << mCoefficients << std::endl
    << "variances: " << mVariances.transpose() << std::endl
    << "weights: " << mWeights.transpose() << std::endl
    << "maxNumIter: " << mMaxNumIter << std::endl
    << "tolerance: " << mTol << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

template <size_t M, size_t N>
void EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>::read(
  std::ifstream& stream) {
}

template <size_t M, size_t N>
void EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>::write(
  std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M, size_t N>
size_t EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>::
getNumPoints() const {
  return mNumPoints;
}

template <size_t M, size_t N>
bool EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>
::getValid() const {
  return mValid;
}

template <size_t M, size_t N>
const Eigen::Matrix<double, N, M>&
EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>::
getCoefficients() const {
  return mCoefficients;
}

template <size_t M, size_t N>
const Eigen::Matrix<double, N, 1>&
EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>::
getVariances() const {
  return mVariances;
}

template <size_t M, size_t N>
const Eigen::Matrix<double, Eigen::Dynamic, N>&
EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>::
getResponsibilities() const {
  return mResponsibilities;
}

template <size_t M, size_t N>
const Eigen::Matrix<double, N, 1>&
EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>::
getWeights() const {
  return mWeights;
}

template <size_t M, size_t N>
double EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>::
getTolerance() const {
  return mTol;
}

template <size_t M, size_t N>
void EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>::
  setTolerance(double tol) {
  mTol = tol;
}

template <size_t M, size_t N>
size_t EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>::
  getMaxNumIter() const {
  return mMaxNumIter;
}

template <size_t M, size_t N>
void EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>::
  setMaxNumIter(size_t maxNumIter) {
  mMaxNumIter = maxNumIter;
}

template <size_t M, size_t N>
void EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>::reset() {
  mNumPoints = 0;
  mValid = false;
}

template <size_t M, size_t N>
size_t EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>::
  addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
  itEnd, FactorGraph& factorGraph, DEMGraph::VertexContainer& fgMapping,
  std::vector<DEMGraph::VertexDescriptor>& pointsMapping, const
  Grid<double, Cell, 2>& dem, const DEMGraph& graph) {
  reset();
  size_t numIter = 0;
  const size_t K = mWeights.size();
  const size_t dim = mCoefficients.cols();
  mNumPoints = itEnd - itStart;
  if (mNumPoints < dim)
    return numIter;
  Eigen::Matrix<double, Eigen::Dynamic, 1> targets(mNumPoints);
  Eigen::Matrix<double, Eigen::Dynamic, M> designMatrix(mNumPoints, (int)dim);
  for (ConstPointIterator it = itStart; it != itEnd; ++it) {
    const size_t row = it - itStart;
    targets(row) = (*it)(dim - 1);
    designMatrix(row, 0) = 1.0;
    designMatrix.row(row).segment(1, dim - 1) = (*it).segment(0, dim - 1);
  }
  double oldLogLikelihood = -std::numeric_limits<double>::infinity();
  mResponsibilities.resize(mNumPoints, K);
  PropertySet opts;
  opts.set("maxiter", (size_t)200);
  opts.set("tol", 1e-6);
  opts.set("verbose", (size_t)1);
  opts.set("updates", std::string("SEQRND"));
  opts.set("logdomain", false);
  opts.set("inference", std::string("SUMPROD"));
  while (numIter != mMaxNumIter) {
    BeliefPropagation bp(factorGraph, opts);
    bp.init();
    bp.run();
    double newLogLikelihood = bp.logZ();
    for (size_t i = 0; i < mResponsibilities.rows(); ++i) {
      dai::Factor fac = bp.beliefV(fgMapping[pointsMapping[i]]);
      for (size_t j = 0; j < mResponsibilities.cols(); ++j)
        mResponsibilities(i, j) = fac[j];
    }
    if (fabs(oldLogLikelihood - newLogLikelihood) < mTol)
      break;
    oldLogLikelihood = newLogLikelihood;
    Eigen::Matrix<double, N, 1> numPoints(K);
    for (size_t j = 0; j < K; ++j)
      numPoints(j) = mResponsibilities.col(j).sum();
    mWeights = numPoints / mNumPoints;
    for (size_t j = 0; j < K; ++j) {
      const Eigen::QR<Eigen::Matrix<double, Eigen::Dynamic, M> > qrDecomp =
        (mResponsibilities.col(j).asDiagonal() * designMatrix).qr();
      if (numPoints(j) > dim && (size_t)qrDecomp.rank() == dim) {
        Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> coeff;
        qrDecomp.solve(mResponsibilities.col(j).asDiagonal() * targets, &coeff);
        mCoefficients.row(j) = coeff.transpose();
        mVariances(j) = ((targets - designMatrix *
          mCoefficients.row(j).transpose()).transpose() *
          mResponsibilities.col(j).asDiagonal() * (targets - designMatrix *
          mCoefficients.row(j).transpose()))(0) / numPoints(j);
      }
    }
    Helpers::updateFactorGraph(dem, graph, mCoefficients, mVariances, mWeights,
      factorGraph, fgMapping);
    numIter++;
  }
  mValid = true;
  return numIter;
}
