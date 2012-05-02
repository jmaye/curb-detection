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

#include "statistics/StudentDistribution.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
LinearRegressionPred<M>::LinearRegressionPred(double degrees, const
    LinearBasisFunction<double, M>& linearBasisFunction, const
    Eigen::Matrix<double, M, M> coeffsCovariance,
    double variance, const Eigen::Matrix<double, M - 1, 1>& basis) :
    mDegrees(degrees),
    mLinearBasisFunction(linearBasisFunction),
    mCoeffsCovariance(coeffsCovariance),
    mVariance(variance),
    mBasis(basis) {
}

template <size_t M>
LinearRegressionPred<M>::LinearRegressionPred(const LinearRegressionPred&
    other) :
    mDegrees(other.mDegrees),
    mLinearBasisFunction(other.mLinearBasisFunction),
    mCoeffsCovariance(other.mCoeffsCovariance),
    mVariance(other.mVariance),
    mBasis(other.mBasis) {
}

template <size_t M>
LinearRegressionPred<M>& LinearRegressionPred<M>::operator = (const
    LinearRegressionPred& other) {
  if (this != &other) {
    mDegrees = other.mDegrees;
    mLinearBasisFunction = other.mLinearBasisFunction;
    mCoeffsCovariance = other.mCoeffsCovariance;
    mVariance = other.mVariance;
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
  stream << "degrees: " << mDegrees << std::endl
    << "linear basis function: " << std::endl << mLinearBasisFunction
    << std::endl
    << "coefficients covariance: " << std::endl << mCoeffsCovariance
    << std::endl
    << "variance: " << mVariance  << std::endl
    << "basis: " << std::endl << mBasis;
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
const LinearBasisFunction<double, M>&
    LinearRegressionPred<M>::getLinearBasisFunction() const {
  return mLinearBasisFunction;
}

template <size_t M>
void LinearRegressionPred<M>::setLinearBasisFunction(const
    LinearBasisFunction<double, M>& linearBasisFunction) {
  mLinearBasisFunction = linearBasisFunction;
}

template <size_t M>
double LinearRegressionPred<M>::getVariance() const {
  return mVariance;
}

template <size_t M>
void LinearRegressionPred<M>::setVariance(double variance) {
  mVariance = variance;
}

template <size_t M>
const Eigen::Matrix<double, M - 1, 1>& LinearRegressionPred<M>::getBasis()
    const {
  return mBasis;
}

template <size_t M>
void LinearRegressionPred<M>::setBasis(const Eigen::Matrix<double, M - 1, 1>&
    basis) {
  mBasis = basis;
}

template <size_t M>
double LinearRegressionPred<M>::getDegrees() const {
  return mDegrees;
}

template <size_t M>
void LinearRegressionPred<M>::setDegrees(double degrees) {
  mDegrees = degrees;
}

template <size_t M>
const Eigen::Matrix<double, M, M>&
    LinearRegressionPred<M>::getCoeffsCovariance() const {
  return mCoeffsCovariance;
}

template <size_t M>
void LinearRegressionPred<M>::
    setCoeffsCovariance(const Eigen::Matrix<double, M, M>& coeffsCovariance) {
  mCoeffsCovariance = coeffsCovariance;
}

template <size_t M>
template <size_t N, size_t D>
double LinearRegressionPred<M>::Traits<N, D>::pdf(const
    LinearRegressionPred<N>& linearRegression, const
    Eigen::Matrix<double, N, 1>& value) {
  const Eigen::Matrix<double, N, 1> x =
    (Eigen::Matrix<double, N, 1>() <<
    1.0, value.start(value.size() - 1)).finished();
  return StudentDistribution<1>(linearRegression.mDegrees,
    linearRegression.mLinearBasisFunction(
    value.start(value.size() - 1)),
    linearRegression.mVariance * (1.0 + (x.transpose() *
    linearRegression.mCoeffsCovariance * x)(0))).pdf(
    value.template end<1>()(0));
}

template <size_t M>
template <size_t D>
double LinearRegressionPred<M>::Traits<2, D>::pdf(const
    LinearRegressionPred<2>& linearRegression, const
    Eigen::Matrix<double, 2, 1>& value) {
  const Eigen::Matrix<double, 2, 1> x =
    (Eigen::Matrix<double, 2, 1>() <<
    1.0, value(0)).finished();
  return StudentDistribution<1>(linearRegression.mDegrees,
    linearRegression.mLinearBasisFunction(value(0)),
    linearRegression.mVariance * (1.0 + (x.transpose() *
    linearRegression.mCoeffsCovariance * x)(0))).pdf(value(1));
}

template <size_t M>
template <size_t N, size_t D>
double LinearRegressionPred<M>::Traits<N, D>::logpdf(const
    LinearRegressionPred<N>& linearRegression, const
    Eigen::Matrix<double, N, 1>& value) {
  const Eigen::Matrix<double, N, 1> x =
    (Eigen::Matrix<double, N, 1>() <<
    1.0, value.start(value.size() - 1)).finished();
  return StudentDistribution<1>(linearRegression.mDegrees,
    linearRegression.mLinearBasisFunction(
    value.start(value.size() - 1)),
    linearRegression.mVariance * (1.0 + (x.transpose() *
    linearRegression.mCoeffsCovariance * x)(0))).logpdf(
    value.template end<1>()(0));
}

template <size_t M>
template <size_t D>
double LinearRegressionPred<M>::Traits<2, D>::logpdf(const
    LinearRegressionPred<2>& linearRegression, const
    Eigen::Matrix<double, 2, 1>& value) {
  const Eigen::Matrix<double, 2, 1> x =
    (Eigen::Matrix<double, 2, 1>() <<
    1.0, value(0)).finished();
  return StudentDistribution<1>(linearRegression.mDegrees,
    linearRegression.mLinearBasisFunction(value(0)),
    linearRegression.mVariance * (1.0 + (x.transpose() *
    linearRegression.mCoeffsCovariance * x)(0))).logpdf(value(1));
}

template <size_t M>
template <size_t N, size_t D>
Eigen::Matrix<double, N, 1> LinearRegressionPred<M>::Traits<N, D>::getSample(
    const LinearRegressionPred<N>& linearRegression) {
  const Eigen::Matrix<double, N, 1> x =
    (Eigen::Matrix<double, N, 1>() <<
    1.0, linearRegression.mBasis).finished();
  return (Eigen::Matrix<double, N, 1>() << linearRegression.mBasis,
    StudentDistribution<1>(linearRegression.mDegrees,
    linearRegression.mLinearBasisFunction(
    linearRegression.mBasis), linearRegression.mVariance * (1.0 +
    (x.transpose() *
    linearRegression.mCoeffsCovariance * x)(0))).getSample()).finished();
}

template <size_t M>
template <size_t D>
Eigen::Matrix<double, 2, 1> LinearRegressionPred<M>::Traits<2, D>::getSample(
    const LinearRegressionPred<2>& linearRegression) {
  const Eigen::Matrix<double, 2, 1> x =
    (Eigen::Matrix<double, 2, 1>() <<
    1.0, linearRegression.mBasis).finished();
  return Eigen::Matrix<double, 2, 1>(linearRegression.mBasis(0),
    StudentDistribution<1>(linearRegression.mDegrees,
    linearRegression.mLinearBasisFunction(
    linearRegression.mBasis(0)), linearRegression.mVariance * (1.0 +
    (x.transpose() *
    linearRegression.mCoeffsCovariance * x)(0))).getSample());
}

template <size_t M>
template <size_t N, size_t D>
double LinearRegressionPred<M>::Traits<N, D>::getPredMean(const
    LinearRegressionPred<N>& linearRegression) {
  return linearRegression.mLinearBasisFunction(linearRegression.mBasis);
}

template <size_t M>
template <size_t D>
double LinearRegressionPred<M>::Traits<2, D>::getPredMean(const
    LinearRegressionPred<2>& linearRegression) {
  return linearRegression.mLinearBasisFunction(linearRegression.mBasis(0));
}

template <size_t M>
template <size_t N, size_t D>
double LinearRegressionPred<M>::Traits<N, D>::getPredVariance(const
    LinearRegressionPred<N>& linearRegression) {
  const Eigen::Matrix<double, N, 1> x =
    (Eigen::Matrix<double, N, 1>() <<
    1.0, linearRegression.mBasis).finished();
  return linearRegression.mVariance * (1.0 + (x.transpose() *
    linearRegression.mCoeffsCovariance * x)(0));
}

template <size_t M>
template <size_t D>
double LinearRegressionPred<M>::Traits<2, D>::getPredVariance(const
    LinearRegressionPred<2>& linearRegression) {
  const Eigen::Matrix<double, 2, 1> x =
    (Eigen::Matrix<double, 2, 1>() <<
    1.0, linearRegression.mBasis).finished();
  return linearRegression.mVariance * (1.0 + (x.transpose() *
    linearRegression.mCoeffsCovariance * x)(0));
}

template <size_t M>
double LinearRegressionPred<M>::pdf(const RandomVariable& value) const {
  return Traits<M>::pdf(*this, value);
}

template <size_t M>
double LinearRegressionPred<M>::logpdf(const RandomVariable& value) const {
  return Traits<M>::logpdf(*this, value);
}

template <size_t M>
typename LinearRegressionPred<M>::RandomVariable
    LinearRegressionPred<M>::getSample() const {
  return Traits<M>::getSample(*this);
}

template <size_t M>
double LinearRegressionPred<M>::getPredMean() const {
  return Traits<M>::getPredMean(*this);
}

template <size_t M>
double LinearRegressionPred<M>::getPredVariance() const {
  return Traits<M>::getPredVariance(*this);
}
