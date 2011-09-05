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

template <size_t N>
EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>::EstimatorML(
  const Eigen::Matrix<double, N, 1>& means,
  const Eigen::Matrix<double, N, 1>& variances,
  const Eigen::Matrix<double, N, 1>& weights, size_t maxNumIter, double tol) :
  mMeans(means),
  mVariances(variances),
  mWeights(weights),
  mMaxNumIter(maxNumIter),
  mTol(tol),
  mNumPoints(0),
  mValid(false) {
}

template <size_t N>
EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>::EstimatorML(
  const EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>&
  other) :
  mMeans(other.mMeans),
  mVariances(other.mVariances),
  mResponsibilities(other.mResponsibilities),
  mWeights(other.mWeights),
  mMaxNumIter(other.mMaxNumIter),
  mTol(other.mTol),
  mNumPoints(other.mNumPoints),
  mValid(other.mValid) {
}

template <size_t N>
EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>&
  EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>::operator =
  (const EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>&
  other) {
  if (this != &other) {
    mMeans = other.mMeans;
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

template <size_t N>
EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>::
~EstimatorML() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t N>
void EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>::read(
  std::istream& stream) {
}

template <size_t N>
void EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>::write(
  std::ostream& stream) const {
  stream << "means: " << mMeans.transpose() << std::endl
    << "variances: " << mVariances.transpose() << std::endl
    << "weights: " << mWeights.transpose() << std::endl
    << "maxNumIter: " << mMaxNumIter << std::endl
    << "tolerance: " << mTol << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

template <size_t N>
void EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>::read(
  std::ifstream& stream) {
}

template <size_t N>
void EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>::write(
  std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t N>
size_t EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>::
getNumPoints() const {
  return mNumPoints;
}

template <size_t N>
bool EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>::
getValid() const {
  return mValid;
}

template <size_t N>
const Eigen::Matrix<double, N, 1>&
EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>::
getMeans() const {
  return mMeans;
}

template <size_t N>
const Eigen::Matrix<double, N, 1>&
EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>::
getVariances() const {
  return mVariances;
}

template <size_t N>
const Eigen::Matrix<double, Eigen::Dynamic, N>&
EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>::
getResponsibilities() const {
  return mResponsibilities;
}

template <size_t N>
const Eigen::Matrix<double, N, 1>&
EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>::
getWeights() const {
  return mWeights;
}

template <size_t N>
double EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>::
getTolerance() const {
  return mTol;
}

template <size_t N>
void EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>::
setTolerance(double tol) {
  mTol = tol;
}

template <size_t N>
size_t EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>::
getMaxNumIter() const {
  return mMaxNumIter;
}

template <size_t N>
void EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>::
setMaxNumIter(size_t maxNumIter) {
  mMaxNumIter = maxNumIter;
}

template <size_t N>
void EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>::reset() {
  mNumPoints = 0;
  mValid = false;
}

template <size_t N>
size_t EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>::
addPoints(const std::vector<double>& points) {
  size_t numIter = 0;
  reset();
  size_t K = mWeights.size();
  if (points.size()) {
    mNumPoints += points.size();
    mResponsibilities.resize(points.size(), K);
    double oldLogLikelihood = -std::numeric_limits<double>::infinity();
    while (numIter != mMaxNumIter) {
      double newLogLikelihood = 0;
      for (size_t i = 0; i < points.size(); ++i) {
        double probability = 0.0;
        for (size_t j = 0; j < K; ++j) {
          mResponsibilities(i, j) = mWeights(j) *
            NormalDistribution<1>(mMeans(j), mVariances(j))(points[i]);
          probability += mResponsibilities(i, j);
        }
        newLogLikelihood += log(probability);
        mResponsibilities.row(i) /= mResponsibilities.row(i).sum();
      }
      if (fabs(oldLogLikelihood - newLogLikelihood) < mTol)
        break;
      oldLogLikelihood = newLogLikelihood;
      Eigen::Matrix<double, N, 1> numPoints;
      for (size_t j = 0; j < K; ++j)
        numPoints(j) = mResponsibilities.col(j).sum();
      mWeights = numPoints / points.size();
      mMeans = Eigen::Matrix<double, N, 1>::Zero(K);
      for (size_t i = 0; i < points.size(); ++i)
        for (size_t j = 0; j < K; ++j)
          mMeans(j) += mResponsibilities(i, j) * points[i];
      mMeans.cwise() /= numPoints;
      mVariances = Eigen::Matrix<double, N, 1>::Zero(K);
      for (size_t i = 0; i < points.size(); ++i)
        for (size_t j = 0; j < K; ++j)
          mVariances(j) += mResponsibilities(i, j) * (points[i] - mMeans(j)) *
            (points[i] - mMeans(j));
      mVariances.cwise() /= numPoints;
      numIter++;
    }
    mValid = true;
  }
  return numIter;
}
