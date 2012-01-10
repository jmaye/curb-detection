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

#include <Eigen/QR>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
EstimatorML<NormalDistribution<M>, M>::EstimatorML() :
  mNumPoints(0),
  mValid(false) {
}

template <size_t M>
EstimatorML<NormalDistribution<M>, M>::EstimatorML(const
  EstimatorML<NormalDistribution<M>, M>& other) :
  mMean(other.mMean),
  mCovariance(other.mCovariance),
  mNumPoints(other.mNumPoints),
  mValid(other.mValid),
  mValuesSum(other.mValuesSum),
  mSquaredValuesSum(other.mSquaredValuesSum) {
}

template <size_t M>
EstimatorML<NormalDistribution<M>, M>&
  EstimatorML<NormalDistribution<M>, M>::operator =
  (const EstimatorML<NormalDistribution<M>, M>& other) {
  if (this != &other) {
    mMean = other.mMean;
    mCovariance = other.mCovariance;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
    mValuesSum = other.mValuesSum;
    mSquaredValuesSum = other.mSquaredValuesSum;
  }
  return *this;
}

template <size_t M>
EstimatorML<NormalDistribution<M>, M>::~EstimatorML() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorML<NormalDistribution<M>, M>::read(std::istream& stream) {
}

template <size_t M>
void EstimatorML<NormalDistribution<M>, M>::write(std::ostream& stream)
  const {
  stream << "mean: " << std::endl << mMean << std::endl
    << "covariance: " << std::endl << mCovariance << std::endl
    << "valid: " << mValid;
}

template <size_t M>
void EstimatorML<NormalDistribution<M>, M>::read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorML<NormalDistribution<M>, M>::write(std::ofstream& stream)
  const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
size_t EstimatorML<NormalDistribution<M>, M>::getNumPoints() const {
  return mNumPoints;
}

template <size_t M>
bool EstimatorML<NormalDistribution<M>, M>::getValid() const {
  return mValid;
}

template <size_t M>
const Eigen::Matrix<double, M, 1>&
EstimatorML<NormalDistribution<M>, M>::getMean() const {
  return mMean;
}

template <size_t M>
const Eigen::Matrix<double, M, M>&
EstimatorML<NormalDistribution<M>, M>::getCovariance() const {
  return mCovariance;
}

template <size_t M>
void EstimatorML<NormalDistribution<M>, M>::reset() {
  mNumPoints = 0;
  mValid = false;
}

template <size_t M>
void EstimatorML<NormalDistribution<M>, M>::addPoint(const Point& point) {
  if (mNumPoints == 0) {
    mValuesSum = Eigen::Matrix<double, M, 1>::Zero(point.size());
    mSquaredValuesSum = Eigen::Matrix<double, M, M>::Zero(point.size(),
      point.size());
  }
  mNumPoints++;
  mValuesSum += point;
  mSquaredValuesSum += point * point.transpose();
  mMean = 1.0 / mNumPoints * mValuesSum;
  mCovariance = 1.0 / mNumPoints * mSquaredValuesSum -
    2.0 / mNumPoints  * mMean * mValuesSum.transpose()  +
    mMean * mMean.transpose();
  const size_t dim = point.size();
  for (size_t i = 0; i < dim; ++i)
    for (size_t j = i + 1; j < dim; ++j)
    mCovariance(i, j) = mCovariance(j, i);
  const Eigen::QR<Eigen::Matrix<double, M, M> > qrDecomp = mCovariance.qr();
  if (qrDecomp.rank() == mMean.size())
    mValid = true;
  else
    mValid = false;
}

template <size_t M>
void EstimatorML<NormalDistribution<M>, M>::addPoints(const ConstPointIterator&
  itStart, const ConstPointIterator& itEnd) {
  for (ConstPointIterator it = itStart; it != itEnd; ++it)
    addPoint(*it);
}
