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
EstimatorML<LinearRegression<M>, M>::EstimatorML() :
  mNumPoints(0),
  mValid(false) {
}

template <size_t M>
EstimatorML<LinearRegression<M>, M>::EstimatorML(const
  EstimatorML<LinearRegression<M>, M>& other) :
  mCoefficients(other.mCoefficients),
  mVariance(other.mVariance),
  mNumPoints(other.mNumPoints),
  mValid(other.mValid) {
}

template <size_t M>
EstimatorML<LinearRegression<M>, M>&
  EstimatorML<LinearRegression<M>, M>::operator =
  (const EstimatorML<LinearRegression<M>, M>& other) {
  if (this != &other) {
    mCoefficients = other.mCoefficients;
    mVariance = other.mVariance;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
  }
  return *this;
}

template <size_t M>
EstimatorML<LinearRegression<M>, M>::~EstimatorML() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorML<LinearRegression<M>, M>::read(std::istream& stream) {
}

template <size_t M>
void EstimatorML<LinearRegression<M>, M>::write(std::ostream& stream) const {
  stream << "coefficients: " << mCoefficients.transpose() << std::endl
    << "variance: " << mVariance << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

template <size_t M>
void EstimatorML<LinearRegression<M>, M>::read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorML<LinearRegression<M>, M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
size_t EstimatorML<LinearRegression<M>, M>::getNumPoints() const {
  return mNumPoints;
}

template <size_t M>
bool EstimatorML<LinearRegression<M>, M>::getValid() const {
  return mValid;
}

template <size_t M>
const Eigen::Matrix<double, M, 1>&
EstimatorML<LinearRegression<M>, M>::getCoefficients() const {
  return mCoefficients;
}

template <size_t M>
double EstimatorML<LinearRegression<M>, M>::getVariance() const {
  return mVariance;
}

template <size_t M>
void EstimatorML<LinearRegression<M>, M>::reset() {
  mNumPoints = 0;
  mValid = false;
}

template <size_t M>
void EstimatorML<LinearRegression<M>, M>::addPoints(const
  std::vector<Eigen::Matrix<double, M, 1> >& points) {
  Eigen::Matrix<double, Eigen::Dynamic, 1> weights =
    Eigen::Matrix<double, Eigen::Dynamic, 1>::Ones(points.size());
  return addPoints(points, weights);
}

template <size_t M>
void EstimatorML<LinearRegression<M>, M>::addPoints(const
  std::vector<Eigen::Matrix<double, M, 1> >& points, const
  Eigen::Matrix<double, Eigen::Dynamic, 1>& weights) {
  reset();
  mNumPoints = points.size();
  size_t dim;
  if (mNumPoints != 0)
    dim = points[0].size();
  else
    return;
  if ((size_t)weights.size() != mNumPoints)
    return;
  Eigen::Matrix<double, Eigen::Dynamic, 1> targets(mNumPoints);
  Eigen::Matrix<double, Eigen::Dynamic, M> designMatrix(mNumPoints, (int)dim);
  for (size_t i = 0; i < mNumPoints; ++i) {
    targets(i) = points[i](dim - 1);
    designMatrix(i, 0) = 1.0;
    designMatrix.row(i).segment(1, dim - 1) = points[i].segment(0, dim - 1);
  }
  Eigen::QR<Eigen::Matrix<double, Eigen::Dynamic, M> > qrDecomp =
    (weights.asDiagonal() * designMatrix).qr();
  if (mNumPoints > dim && (size_t)qrDecomp.rank() == dim) {
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> coeff;
    qrDecomp.solve(weights.asDiagonal() * targets, &coeff);
    mCoefficients = coeff;
    mVariance = ((targets - designMatrix * mCoefficients).transpose() *
      weights.asDiagonal() * (targets - designMatrix * mCoefficients))(0) /
      mNumPoints;
    mValid = true;
  }
  else
    mValid = false;
}
