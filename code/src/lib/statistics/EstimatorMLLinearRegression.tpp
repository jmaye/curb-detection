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

#include <Eigen/LU>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
EstimatorML<LinearRegression<M> >::EstimatorML() :
    mNumPoints(0),
    mValid(false) {
}

template <size_t M>
EstimatorML<LinearRegression<M> >::EstimatorML(const EstimatorML& other) :
    mLinearRegression(other.mLinearRegression),
    mNumPoints(other.mNumPoints),
    mValid(other.mValid) {
}

template <size_t M>
EstimatorML<LinearRegression<M> >&
    EstimatorML<LinearRegression<M> >::operator = (const EstimatorML& other) {
  if (this != &other) {
    mLinearRegression = other.mLinearRegression;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
  }
  return *this;
}

template <size_t M>
EstimatorML<LinearRegression<M> >::~EstimatorML() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorML<LinearRegression<M> >::read(std::istream& stream) {
}

template <size_t M>
void EstimatorML<LinearRegression<M> >::write(std::ostream& stream) const {
  stream << "linear regression: " << std::endl << mLinearRegression << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

template <size_t M>
void EstimatorML<LinearRegression<M> >::read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorML<LinearRegression<M> >::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
size_t EstimatorML<LinearRegression<M> >::getNumPoints() const {
  return mNumPoints;
}

template <size_t M>
bool EstimatorML<LinearRegression<M> >::getValid() const {
  return mValid;
}

template <size_t M>
const LinearRegression<M>&
    EstimatorML<LinearRegression<M> >::getDistribution() const {
  return mLinearRegression;
}

template <size_t M>
void EstimatorML<LinearRegression<M> >::reset() {
  mNumPoints = 0;
  mValid = false;
}

template <size_t M>
void EstimatorML<LinearRegression<M> >::addPoints(const ConstPointIterator&
    itStart, const ConstPointIterator& itEnd) {
  Eigen::Matrix<double, Eigen::Dynamic, 1> responsibilities =
    Eigen::Matrix<double, Eigen::Dynamic, 1>::Ones(itEnd - itStart);
  return addPoints(itStart, itEnd, responsibilities);
}

template <size_t M>
void EstimatorML<LinearRegression<M> >::addPoints(const ConstPointIterator&
    itStart, const ConstPointIterator& itEnd, const
    Eigen::Matrix<double, Eigen::Dynamic, 1>& responsibilities) {
  reset();
  mNumPoints = itEnd - itStart;
  size_t dim;
  if (mNumPoints != 0)
    dim = itStart->size();
  else
    return;
  if (mNumPoints < dim || responsibilities.sum() < dim)
    return;
  if ((size_t)responsibilities.size() != mNumPoints)
    return;
  Eigen::Matrix<double, Eigen::Dynamic, 1> targets(mNumPoints);
  Eigen::Matrix<double, Eigen::Dynamic, M> designMatrix(mNumPoints, (int)dim);
  for (auto it = itStart; it != itEnd; ++it) {
    const size_t row = it - itStart;
    targets(row) = (*it)(dim - 1);
    designMatrix(row, 0) = 1.0;
    designMatrix.row(row).segment(1, dim - 1) = (*it).segment(0, dim - 1);
  }
  try {
    const Eigen::Matrix<double, M, 1> coeffs =
      (designMatrix.transpose() * responsibilities.asDiagonal() * designMatrix).
      inverse() * designMatrix.transpose() * responsibilities.asDiagonal() *
      targets;
    for (size_t i = 0; i < dim; ++i)
      if (std::isnan(coeffs(i)))
        return;
    mValid = true;
    mLinearRegression.setLinearBasisFunction(
      LinearBasisFunction<double, M>(coeffs));
    mLinearRegression.setVariance(
      ((targets - designMatrix * coeffs).transpose() *
      responsibilities.asDiagonal() * (targets - designMatrix * coeffs))(0) /
      responsibilities.sum());
  }
  catch (...) {
    mValid = false;
  }
}

template <size_t M>
void  EstimatorML<LinearRegression<M> >::addPoints(const Container& points) {
  addPoints(points.begin(), points.end());
}
