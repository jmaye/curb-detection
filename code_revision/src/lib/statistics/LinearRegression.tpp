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

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
LinearRegression<M>::LinearRegression(const Eigen::Matrix<double, M, 1>&
  coefficients, double variance, const Eigen::Matrix<double, M, 1>& basis) :
  NormalDistribution<1>(coefficients.dot(basis), variance),
  mCoefficients(coefficients),
  mBasis(basis) {
}

template <size_t M>
LinearRegression<M>::LinearRegression(const LinearRegression<M>& other) :
  NormalDistribution<1>(other),
  mCoefficients(other.mCoefficients),
  mBasis(other.mBasis) {
}

template <size_t M>
LinearRegression<M>& LinearRegression<M>::operator = (const LinearRegression<M>&
  other) {
  if (this != &other) {
    this->NormalDistribution<1>::operator=(other);
    mCoefficients = other.mCoefficients;
    mBasis = other.mBasis;
  }
  return *this;
}

template <size_t M>
LinearRegression<M>::~LinearRegression() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <size_t M>
void LinearRegression<M>::read(std::istream& stream) {
}

template <size_t M>
void LinearRegression<M>::write(std::ostream& stream) const {
  stream << "coefficients: " << std::endl << mCoefficients << std::endl
    << "basis: " << std::endl << mBasis << std::endl
    << "variance: " << mVariance;
}

template <size_t M>
void LinearRegression<M>::read(std::ifstream& stream) {
}

template <size_t M>
void LinearRegression<M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
void LinearRegression<M>::setCoefficients(const Eigen::Matrix<double, M, 1>&
  coefficients) {
  setMean(coefficients.dot(mBasis));
  mCoefficients = coefficients;
}

template <size_t M>
const Eigen::Matrix<double, M, 1>& LinearRegression<M>::getCoefficients()
  const {
  return mCoefficients;
}

template <size_t M>
void LinearRegression<M>::setBasis(const Eigen::Matrix<double, M, 1>& basis) {
  setMean(mCoefficients.dot(basis));
  mBasis = basis;
}

template <size_t M>
const Eigen::Matrix<double, M, 1>& LinearRegression<M>::getBasis() const {
  return mBasis;
}
