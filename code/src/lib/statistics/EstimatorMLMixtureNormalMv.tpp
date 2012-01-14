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

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M, size_t N>
EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>::EstimatorML(
  const std::vector<Eigen::Matrix<double, M, 1> >& means,
  const std::vector<Eigen::Matrix<double, M, M> >& covariances,
  const Eigen::Matrix<double, N, 1>& weights, size_t maxNumIter, double tol) :
  mMeans(means),
  mCovariances(covariances),
  mWeights(weights),
  mLogLikelihood(0),
  mMaxNumIter(maxNumIter),
  mTol(tol),
  mNumPoints(0),
  mValid(false) {
}

template <size_t M, size_t N>
EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>::EstimatorML(
  const EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>&
  other) :
  mMeans(other.mMeans),
  mCovariances(other.mCovariances),
  mResponsibilities(other.mResponsibilities),
  mWeights(other.mWeights),
  mMaxNumIter(other.mMaxNumIter),
  mTol(other.mTol),
  mNumPoints(other.mNumPoints),
  mValid(other.mValid) {
}

template <size_t M, size_t N>
EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>&
  EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>::operator =
  (const EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>&
  other) {
  if (this != &other) {
    mMeans = other.mMeans;
    mCovariances = other.mCovariances;
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
EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>::
~EstimatorML() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M, size_t N>
void EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>::read(
  std::istream& stream) {
}

template <size_t M, size_t N>
void EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>::write(
  std::ostream& stream) const {
  stream << "means: " << std::endl;
  for (size_t i = 0; i < N; ++i)
    stream << mMeans[i] << std::endl;
  stream << "covariances: " << std::endl;
  for (size_t i = 0; i < N; ++i)
    stream << mCovariances[i] << std::endl;
  stream << "weights: " << mWeights.transpose() << std::endl
    << "log-likelihood: " << mLogLikelihood << std::endl
    << "maxNumIter: " << mMaxNumIter << std::endl
    << "tolerance: " << mTol << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

template <size_t M, size_t N>
void EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>::read(
  std::ifstream& stream) {
}

template <size_t M, size_t N>
void EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>::write(
  std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M, size_t N>
size_t EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>::
getNumPoints() const {
  return mNumPoints;
}

template <size_t M, size_t N>
bool EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>::
getValid() const {
  return mValid;
}

template <size_t M, size_t N>
const std::vector<Eigen::Matrix<double, M, 1> >&
EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>::
getMeans() const {
  return mMeans;
}

template <size_t M, size_t N>
const std::vector<Eigen::Matrix<double, M, M> >&
EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>::
getCovariances() const {
  return mCovariances;
}

template <size_t M, size_t N>
const Eigen::Matrix<double, Eigen::Dynamic, N>&
EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>::
getResponsibilities() const {
  return mResponsibilities;
}

template <size_t M, size_t N>
const Eigen::Matrix<double, N, 1>&
EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>::
getWeights() const {
  return mWeights;
}


template <size_t M, size_t N>
double EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>::
getLogLikelihood() const {
  return mLogLikelihood;
}

template <size_t M, size_t N>
double EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>::
getTolerance() const {
  return mTol;
}

template <size_t M, size_t N>
void EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>::
setTolerance(double tol) {
  mTol = tol;
}

template <size_t M, size_t N>
size_t EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>::
getMaxNumIter() const {
  return mMaxNumIter;
}

template <size_t M, size_t N>
void EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>::
setMaxNumIter(size_t maxNumIter) {
  mMaxNumIter = maxNumIter;
}

template <size_t M, size_t N>
void EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>::reset() {
  mNumPoints = 0;
  mLogLikelihood = 0;
  mValid = false;
}

template <size_t M, size_t N>
size_t EstimatorML<MixtureDistribution<NormalDistribution<M>, N>, M, N>::
addPoints(const ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  reset();
  size_t numIter = 0;
  const size_t K = mWeights.size();
  if (mMeans.size() != K || mCovariances.size() != K)
    return numIter;
  const size_t dim = mMeans[0].size();
  mNumPoints = itEnd - itStart;
  if (mNumPoints < dim)
    return numIter;
  mResponsibilities.resize(mNumPoints, K);
  mLogLikelihood = -std::numeric_limits<double>::infinity();
  while (numIter != mMaxNumIter) {
    double newLogLikelihood = 0;
    for (ConstPointIterator it = itStart; it != itEnd; ++it) {
      double probability = 0.0;
      const size_t row = it - itStart;
      for (size_t j = 0; j < K; ++j) {
        mResponsibilities(row, j) = mWeights(j) *
          NormalDistribution<M>(mMeans[j], mCovariances[j])(*it);
        probability += mResponsibilities(row, j);
      }
      newLogLikelihood += log(probability);
      mResponsibilities.row(row) /= mResponsibilities.row(row).sum();
    }
    if (fabs(mLogLikelihood - newLogLikelihood) < mTol)
      break;
    mLogLikelihood = newLogLikelihood;
    Eigen::Matrix<double, N, 1> numPoints(K);
    for (size_t j = 0; j < K; ++j)
      numPoints(j) = mResponsibilities.col(j).sum();
    mWeights = numPoints / mNumPoints;
    for (size_t j = 0; j < K; ++j) {
      mMeans[j] = Eigen::Matrix<double, M, 1>::Zero(dim);
      mCovariances[j] = Eigen::Matrix<double, M, M>::Zero(dim, dim);
    }
    for (ConstPointIterator it = itStart; it != itEnd; ++it) {
      const size_t row = it - itStart;
      for (size_t j = 0; j < K; ++j)
          mMeans[j] += mResponsibilities(row, j) * (*it);
    }
    for (size_t j = 0; j < K; ++j)
      mMeans[j] /= numPoints(j);
    for (ConstPointIterator it = itStart; it != itEnd; ++it) {
      const size_t row = it - itStart;
      for (size_t j = 0; j < K; ++j)
        mCovariances[j] += mResponsibilities(row, j) * ((*it) - mMeans[j]) *
          ((*it) - mMeans[j]).transpose();
    }
    for (size_t j = 0; j < K; ++j)
      mCovariances[j] /= numPoints(j);
    for (size_t k = 0; k < K; ++k)
      for (size_t i = 0; i < dim; ++i)
        for (size_t j = i + 1; j < dim; ++j)
          mCovariances[k](i, j) = mCovariances[k](j, i);
    numIter++;
  }
  mValid = true;
  return numIter;
}
