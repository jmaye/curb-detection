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
LinearRegressionPred<M>::LinearRegressionPred(double degrees, const
  Eigen::Matrix<double, M, 1>& coefficients, const Eigen::Matrix<double, M, M>&
  coeffCovariance, double regressionVariance, const Eigen::Matrix<double, M, 1>&
  basis) :
  StudentDistribution<1>(degrees, coefficients.dot(basis),
    regressionVariance * (1 + (basis.transpose() * coeffCovariance *
    basis)(0))),
  mCoefficients(coefficients),
  mCoeffCovariance(coeffCovariance),
  mRegressionVariance(regressionVariance),
  mBasis(basis) {
}

template <size_t M>
LinearRegressionPred<M>::LinearRegressionPred(const LinearRegressionPred<M>&
  other) :
  StudentDistribution<1>(other),
  mCoefficients(other.mCoefficients),
  mCoeffCovariance(other.mCoeffCovariance),
  mRegressionVariance(other.mRegressionVariance),
  mBasis(other.mBasis) {
}

template <size_t M>
LinearRegressionPred<M>& LinearRegressionPred<M>::operator = (const
  LinearRegressionPred<M>& other) {
  if (this != &other) {
    this->StudentDistribution<1>::operator=(other);
    mCoefficients = other.mCoefficients;
    mCoeffCovariance = other.mCoeffCovariance;
    mRegressionVariance = other.mRegressionVariance;
    mBasis = other.mBasis;
  }
  return *this;
}

template <size_t M>
LinearRegressionPred<M>::~LinearRegressionPred() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <size_t M>
void LinearRegressionPred<M>::read(std::istream& stream) {
}

template <size_t M>
void LinearRegressionPred<M>::write(std::ostream& stream) const {
  stream << "coefficients: " << std::endl << mCoefficients << std::endl
    << "coefficients covariance: " << std::endl << mCoeffCovariance << std::endl
    << "basis: " << std::endl << mBasis << std::endl
    << "regression variance: " << mRegressionVariance;
}

template <size_t M>
void LinearRegressionPred<M>::read(std::ifstream& stream) {
}

template <size_t M>
void LinearRegressionPred<M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
void LinearRegressionPred<M>::setCoefficients(const Eigen::Matrix<double, M, 1>&
  coefficients) {
  setLocation(coefficients.dot(mBasis));
  mCoefficients = coefficients;
}

template <size_t M>
const Eigen::Matrix<double, M, 1>& LinearRegressionPred<M>::getCoefficients()
  const {
  return mCoefficients;
}

template <size_t M>
void LinearRegressionPred<M>::setCoeffCovariance(const
  Eigen::Matrix<double, M, M>& coeffCovariance) {
  setScale(mRegressionVariance * (1 + (mBasis.transpose() *
    coeffCovariance * mBasis)(0)));
  mCoeffCovariance = coeffCovariance;
}

template <size_t M>
const Eigen::Matrix<double, M, M>& LinearRegressionPred<M>::getCoeffCovariance()
  const {
  return mCoeffCovariance;
}

template <size_t M>
void LinearRegressionPred<M>::setRegressionVariance(double variance) {
  setScale(variance * (1 + (mBasis.transpose() * mCoeffCovariance *
    mBasis)(0)));
  mRegressionVariance = variance;
}

template <size_t M>
double LinearRegressionPred<M>::getRegressionVariance() const {
  return mRegressionVariance;
}

template <size_t M>
void LinearRegressionPred<M>::setBasis(const Eigen::Matrix<double, M, 1>&
  basis) {
  setLocation(mCoefficients.dot(basis));
  setScale(mRegressionVariance * (1 + (basis.transpose() *
    mCoeffCovariance * basis)(0)));
  mBasis = basis;
}

template <size_t M>
const Eigen::Matrix<double, M, 1>& LinearRegressionPred<M>::getBasis() const {
  return mBasis;
}
