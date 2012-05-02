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

#include "statistics/NormalDistribution.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
LinearRegression<M>::LinearRegression(const LinearBasisFunction<double, M>&
    linearBasisFunction, double variance, const Eigen::Matrix<double, M - 1, 1>&
    basis) :
    mLinearBasisFunction(linearBasisFunction),
    mVariance(variance),
    mBasis(basis) {
}

template <size_t M>
LinearRegression<M>::LinearRegression(const LinearRegression& other) :
    mLinearBasisFunction(other.mLinearBasisFunction),
    mVariance(other.mVariance),
    mBasis(other.mBasis) {
}

template <size_t M>
LinearRegression<M>& LinearRegression<M>::operator = (const LinearRegression&
    other) {
  if (this != &other) {
    mLinearBasisFunction = other.mLinearBasisFunction;
    mVariance = other.mVariance;
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
  stream << "linear basis function: " << std::endl << mLinearBasisFunction
    << std::endl
    << "variance: " << mVariance  << std::endl
    << "basis: " << std::endl << mBasis;
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
const LinearBasisFunction<double, M>&
    LinearRegression<M>::getLinearBasisFunction() const {
  return mLinearBasisFunction;
}

template <size_t M>
void LinearRegression<M>::setLinearBasisFunction(const
    LinearBasisFunction<double, M>& linearBasisFunction) {
  mLinearBasisFunction = linearBasisFunction;
}

template <size_t M>
double LinearRegression<M>::getVariance() const {
  return mVariance;
}

template <size_t M>
void LinearRegression<M>::setVariance(double variance) {
  mVariance = variance;
}

template <size_t M>
const Eigen::Matrix<double, M - 1, 1>& LinearRegression<M>::getBasis() const {
  return mBasis;
}

template <size_t M>
void LinearRegression<M>::setBasis(const Eigen::Matrix<double, M - 1, 1>&
    basis) {
  mBasis = basis;
}

template <size_t M>
template <size_t N, size_t D>
double LinearRegression<M>::Traits<N, D>::pdf(const
    LinearRegression<N>& linearRegression, const
    Eigen::Matrix<double, N, 1>& value) {
  return NormalDistribution<1>(linearRegression.mLinearBasisFunction(
    value.start(value.size() - 1)),
    linearRegression.mVariance).pdf(value.template end<1>()(0));
}

template <size_t M>
template <size_t D>
double LinearRegression<M>::Traits<2, D>::pdf(const
    LinearRegression<2>& linearRegression, const Eigen::Matrix<double, 2, 1>&
    value) {
  return NormalDistribution<1>(
    linearRegression.mLinearBasisFunction(value(0)),
    linearRegression.mVariance).pdf(value(1));
}

template <size_t M>
template <size_t N, size_t D>
double LinearRegression<M>::Traits<N, D>::logpdf(const
    LinearRegression<N>& linearRegression, const
    Eigen::Matrix<double, N, 1>& value) {
  return NormalDistribution<1>(linearRegression.mLinearBasisFunction(
    value.start(value.size() - 1)),
    linearRegression.mVariance).logpdf(value.template end<1>()(0));
}

template <size_t M>
template <size_t D>
double LinearRegression<M>::Traits<2, D>::logpdf(const
    LinearRegression<2>& linearRegression, const Eigen::Matrix<double, 2, 1>&
    value) {
  return NormalDistribution<1>(
    linearRegression.mLinearBasisFunction(value(0)),
    linearRegression.mVariance).logpdf(value(1));
}

template <size_t M>
template <size_t N, size_t D>
Eigen::Matrix<double, N, 1> LinearRegression<M>::Traits<N, D>::getSample(const
    LinearRegression<N>& linearRegression) {
  return (Eigen::Matrix<double, N, 1>() << linearRegression.mBasis,
    NormalDistribution<1>(linearRegression.mLinearBasisFunction(
    linearRegression.mBasis), linearRegression.mVariance).getSample()).
    finished();
}

template <size_t M>
template <size_t D>
Eigen::Matrix<double, 2, 1> LinearRegression<M>::Traits<2, D>::getSample(const
    LinearRegression<2>& linearRegression) {
  return Eigen::Matrix<double, 2, 1>(linearRegression.mBasis(0),
    NormalDistribution<1>(linearRegression.mLinearBasisFunction(
    linearRegression.mBasis(0)), linearRegression.mVariance).getSample());
}

template <size_t M>
template <size_t N, size_t D>
double LinearRegression<M>::Traits<N, D>::getMean(const
    LinearRegression<N>& linearRegression) {
  return linearRegression.mLinearBasisFunction(linearRegression.mBasis);
}

template <size_t M>
template <size_t D>
double LinearRegression<M>::Traits<2, D>::getMean(const
    LinearRegression<2>& linearRegression) {
  return linearRegression.mLinearBasisFunction(linearRegression.mBasis(0));
}

template <size_t M>
double LinearRegression<M>::pdf(const RandomVariable& value) const {
  return Traits<M>::pdf(*this, value);
}

template <size_t M>
double LinearRegression<M>::logpdf(const RandomVariable& value) const {
  return Traits<M>::logpdf(*this, value);
}

template <size_t M>
typename  LinearRegression<M>::RandomVariable
    LinearRegression<M>::getSample() const {
  return Traits<M>::getSample(*this);
}

template <size_t M>
double LinearRegression<M>::getMean() const {
  return Traits<M>::getMean(*this);
}
