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

#include <Eigen/Array>

#include "statistics/Randomizer.h"
#include "functions/LogBetaFunction.h"
#include "exceptions/BadArgumentException.h"
#include "exceptions/OutOfBoundException.h"
#include "exceptions/InvalidOperationException.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
DirichletDistribution<M>::DirichletDistribution(const
    Eigen::Matrix<double, M, 1>& alpha) {
  setAlpha(alpha);
}

template <size_t M>
DirichletDistribution<M>::DirichletDistribution(const
    DirichletDistribution& other) :
    mAlpha(other.mAlpha),
    mNormalizer(other.mNormalizer) {
}

template <size_t M>
DirichletDistribution<M>& DirichletDistribution<M>::operator =
    (const DirichletDistribution& other) {
  if (this != &other) {
    mAlpha = other.mAlpha;
    mNormalizer = other.mNormalizer;
  }
  return *this;
}

template <size_t M>
DirichletDistribution<M>::~DirichletDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <size_t M>
void DirichletDistribution<M>::read(std::istream& stream) {
}

template <size_t M>
void DirichletDistribution<M>::write(std::ostream& stream) const {
  stream << "alpha: " << std::endl << mAlpha.transpose();
}

template <size_t M>
void DirichletDistribution<M>::read(std::ifstream& stream) {
}

template <size_t M>
void DirichletDistribution<M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
void DirichletDistribution<M>::setAlpha(const Eigen::Matrix<double, M, 1>&
    alpha) {
  if ((alpha.cwise() <= 0).any())
    throw BadArgumentException<Eigen::Matrix<double, M, 1> >(alpha,
      "DirichletDistribution<M>::setAlpha(): alpha must be strictly positive",
      __FILE__, __LINE__);
  mAlpha = alpha;
  const LogBetaFunction<double, M> logBetaFunction;
  mNormalizer = logBetaFunction(mAlpha);
}

template <size_t M>
const Eigen::Matrix<double, M, 1>& DirichletDistribution<M>::getAlpha() const {
  return mAlpha;
}

template <size_t M>
double DirichletDistribution<M>::getAlpha(size_t idx) const {
  if (idx >= (size_t)mAlpha.size())
    throw OutOfBoundException<size_t>(idx,
      "DirichletDistribution<M>::getAlpha(): index out of bound",
      __FILE__, __LINE__);
  return mAlpha(idx);
}

template <size_t M>
double DirichletDistribution<M>::getNormalizer() const {
  return mNormalizer;
}

template <size_t M>
template <size_t N, size_t D>
double DirichletDistribution<M>::Traits<N, D>::pdf(const
    DirichletDistribution<N>& distribution, const
    Eigen::Matrix<double, N - 1, 1>& value) {
  Eigen::Matrix<double, M, 1> valueMat;
  valueMat << value, 1.0 - value.sum();
  return distribution.pdf(valueMat);
}

template <size_t M>
template <size_t D>
double DirichletDistribution<M>::Traits<2, D>::pdf(const
    DirichletDistribution<2>& distribution, const double& value) {
  Eigen::Matrix<double, 2, 1> valueMat;
  valueMat << value, 1.0 - value;
  return distribution.pdf(valueMat);
}

template <size_t M>
template <size_t N, size_t D>
double DirichletDistribution<M>::Traits<N, D>::logpdf(const
    DirichletDistribution<N>& distribution, const
    Eigen::Matrix<double, N - 1, 1>& value) {
  Eigen::Matrix<double, M, 1> valueMat;
  valueMat << value, 1.0 - value.sum();
  return distribution.logpdf(valueMat);
}

template <size_t M>
template <size_t D>
double DirichletDistribution<M>::Traits<2, D>::logpdf(const
    DirichletDistribution<2>& distribution, const double& value) {
  Eigen::Matrix<double, 2, 1> valueMat;
  valueMat << value, 1.0 - value;
  return distribution.logpdf(valueMat);
}

template <size_t M>
double DirichletDistribution<M>::pdf(const RandomVariable& value) const {
  if (fabs(value.sum() - 1.0) > std::numeric_limits<double>::epsilon() ||
      (value.cwise() <= 0).any())
    return 0.0;
  else
    return exp(logpdf(value));
}

template <size_t M>
double DirichletDistribution<M>::pdf(const typename
    ContinuousDistribution<double, M - 1>::Domain& value) const {
  return Traits<M>::pdf(*this, value);
}

template <size_t M>
double DirichletDistribution<M>::logpdf(const RandomVariable& value) const {
  if (fabs(value.sum() - 1.0) > std::numeric_limits<double>::epsilon() ||
      (value.cwise() <= 0).any())
    throw BadArgumentException<RandomVariable>(value,
      "DirichletDistribution<M>::logpdf(): input vector must sum to 1 and "
      "contains strictly positive values",
      __FILE__, __LINE__);
  double returnValue = 0;
  for (size_t i = 0; i < (size_t)mAlpha.size(); ++i)
    returnValue += (mAlpha(i) - 1) * log(value(i));
  return returnValue - mNormalizer;
}

template <size_t M>
double DirichletDistribution<M>::logpdf(const typename
    ContinuousDistribution<double, M - 1>::Domain& value) const {
  return Traits<M>::logpdf(*this, value);
}

template <size_t M>
typename DirichletDistribution<M>::RandomVariable
    DirichletDistribution<M>::getSample() const {
  const static Randomizer<double> randomizer;
  RandomVariable sampleGammaVector(mAlpha.size());
  for (size_t i = 0; i < (size_t)mAlpha.size(); ++i)
    sampleGammaVector(i) = randomizer.sampleGamma(mAlpha(i), 1.0);
  return sampleGammaVector / sampleGammaVector.sum();
}

template <size_t M>
typename DirichletDistribution<M>::Mean DirichletDistribution<M>::getMean()
    const {
  return mAlpha / mAlpha.sum();
}

template <size_t M>
typename DirichletDistribution<M>::Mode DirichletDistribution<M>::getMode()
    const {
  if ((mAlpha.cwise() <= 1).any())
    throw InvalidOperationException("DirichletDistribution<M>::getMode(): "
      "alpha must be bigger than 1");
  else
    return (mAlpha.cwise() - 1) / (mAlpha.sum() - mAlpha.size());
}

template <size_t M>
typename DirichletDistribution<M>::Covariance
    DirichletDistribution<M>::getCovariance() const {
  Covariance covariance(mAlpha.size(), mAlpha.size());
  const double sum = mAlpha.sum();
  for (size_t i = 0; i < (size_t)mAlpha.size(); ++i) {
    covariance(i, i) = mAlpha(i) * (sum - mAlpha(i)) / (sum * sum * (sum + 1));
    for (size_t j = i + 1; j < (size_t)mAlpha.size(); ++j) {
      covariance(i, j) = -mAlpha(i) * mAlpha(j) / (sum * sum * (sum + 1));
      covariance(j, i) = covariance(i, j);
    }
  }
  return covariance;
}
