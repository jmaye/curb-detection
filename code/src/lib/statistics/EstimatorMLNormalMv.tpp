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

#include "utils/OuterProduct.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
EstimatorML<NormalDistribution<M> >::EstimatorML() :
    mNumPoints(0),
    mValid(false) {
}

template <size_t M>
EstimatorML<NormalDistribution<M> >::EstimatorML(const EstimatorML& other) :
    mDistribution(other.mDistribution),
    mNumPoints(other.mNumPoints),
    mValid(other.mValid),
    mValuesSum(other.mValuesSum),
    mSquaredValuesSum(other.mSquaredValuesSum) {
}

template <size_t M>
EstimatorML<NormalDistribution<M> >&
    EstimatorML<NormalDistribution<M> >::operator = (const EstimatorML& other) {
  if (this != &other) {
    mDistribution = other.mDistribution;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
    mValuesSum = other.mValuesSum;
    mSquaredValuesSum = other.mSquaredValuesSum;
  }
  return *this;
}

template <size_t M>
EstimatorML<NormalDistribution<M> >::~EstimatorML() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorML<NormalDistribution<M> >::read(std::istream& stream) {
}

template <size_t M>
void EstimatorML<NormalDistribution<M> >::write(std::ostream& stream)
    const {
  stream << "distribution: " << std::endl << mDistribution << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

template <size_t M>
void EstimatorML<NormalDistribution<M> >::read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorML<NormalDistribution<M> >::write(std::ofstream& stream)
    const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
size_t EstimatorML<NormalDistribution<M> >::getNumPoints() const {
  return mNumPoints;
}

template <size_t M>
bool EstimatorML<NormalDistribution<M> >::getValid() const {
  return mValid;
}

template <size_t M>
const NormalDistribution<M>&
    EstimatorML<NormalDistribution<M> >::getDistribution() const {
  return mDistribution;
}

template <size_t M>
void EstimatorML<NormalDistribution<M> >::reset() {
  mNumPoints = 0;
  mValid = false;
}

template <size_t M>
void EstimatorML<NormalDistribution<M> >::addPoint(const Point& point) {
  if (mNumPoints == 0) {
    mValuesSum = Eigen::Matrix<double, M, 1>::Zero(point.size());
    mSquaredValuesSum = Eigen::Matrix<double, M, M>::Zero(point.size(),
      point.size());
  }
  mNumPoints++;
  mValuesSum += point;
  mSquaredValuesSum += outerProduct<double, M>(point);
  try {
    mValid = true;
    const Eigen::Matrix<double, M, 1> mean = mValuesSum / mNumPoints;
    mDistribution.setMean(mean);
    mDistribution.setCovariance(mSquaredValuesSum / mNumPoints -
      outerProduct<double, M>(mValuesSum) * 2 / (mNumPoints * mNumPoints) +
      outerProduct<double, M>(mean));
  }
  catch (...) {
    mValid = false;
  }
}

template <size_t M>
void EstimatorML<NormalDistribution<M> >::addPoints(const ConstPointIterator&
    itStart, const ConstPointIterator& itEnd) {
  for (auto it = itStart; it != itEnd; ++it)
    addPoint(*it);
}

template <size_t M>
void EstimatorML<NormalDistribution<M> >::addPoints(const Container& points) {
  addPoints(points.begin(), points.end());
}

template <size_t M>
void EstimatorML<NormalDistribution<M> >::addPoints(const ConstPointIterator&
    itStart, const ConstPointIterator& itEnd, const
    Eigen::Matrix<double, Eigen::Dynamic, 1>& responsibilities) {
  if (responsibilities.size() != itEnd - itStart)
    return;
  Eigen::Matrix<double, M, 1> mean =
    Eigen::Matrix<double, M, 1>::Zero(itStart->size());
  for (auto it = itStart; it != itEnd; ++it)
    mean += responsibilities(it - itStart) * (*it);
  double numPoints = responsibilities.sum();
  mean /= numPoints;
  Eigen::Matrix<double, M, M> covariance =
    Eigen::Matrix<double, M, M>::Zero(itStart->size(), itStart->size());
  for (auto it = itStart; it != itEnd; ++it)
    covariance += responsibilities(it - itStart) *
      outerProduct<double, M>(*it - mean);
  covariance /= numPoints;
  try {
    mValid = true;
    mDistribution.setMean(mean);
    mDistribution.setCovariance(covariance);
  }
  catch (...) {
    mValid = false;
  }
}
