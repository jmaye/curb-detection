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

#include <Eigen/Array>

#include "statistics/Randomizer.h"
#include "functions/LogBinomialFunction.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
HyperGeometricDistribution<M>::HyperGeometricDistribution(size_t numTrials,
    const Eigen::Matrix<size_t, M, 1>&  marbles) :
    mMarbles(marbles) {
  setNumTrials(numTrials);
}

template <size_t M>
HyperGeometricDistribution<M>::HyperGeometricDistribution(const
    HyperGeometricDistribution& other) :
    mMarbles(other.mMarbles),
    mNumTrials(other.mNumTrials),
    mNormalizer(other.mNormalizer) {
}

template <size_t M>
HyperGeometricDistribution<M>& HyperGeometricDistribution<M>::operator =
    (const HyperGeometricDistribution& other) {
  if (this != &other) {
    mMarbles = other.mMarbles;
    mNumTrials = other.mNumTrials;
    mNormalizer = other.mNormalizer;
  }
  return *this;
}

template <size_t M>
HyperGeometricDistribution<M>::~HyperGeometricDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <size_t M>
void HyperGeometricDistribution<M>::read(std::istream& stream) {
}

template <size_t M>
void HyperGeometricDistribution<M>::write(std::ostream& stream) const {
  stream << "marbles: " << std::endl << mMarbles << std::endl
    << "trial numbers: " << mNumTrials;
}

template <size_t M>
void HyperGeometricDistribution<M>::read(std::ifstream& stream) {
}

template <size_t M>
void HyperGeometricDistribution<M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
template <size_t N, size_t D>
double HyperGeometricDistribution<M>::Traits<N, D>::pmf(const
    HyperGeometricDistribution<N>& distribution, const
    Eigen::Matrix<int, N - 1, 1>& value) {
  Eigen::Matrix<int, M, 1> valueMat;
  valueMat << value, distribution.mNumTrials - value.sum();
  return distribution.pmf(valueMat);
}

template <size_t M>
template <size_t D>
double HyperGeometricDistribution<M>::Traits<2, D>::pmf(const
    HyperGeometricDistribution<2>& distribution, const int& value) {
  Eigen::Matrix<int, 2, 1> valueMat;
  valueMat << value, distribution.mNumTrials - value;
  return distribution.pmf(valueMat);
}

template <size_t M>
template <size_t N, size_t D>
double HyperGeometricDistribution<M>::Traits<N, D>::logpmf(const
    HyperGeometricDistribution<N>& distribution, const
    Eigen::Matrix<int, N - 1, 1>& value) {
  Eigen::Matrix<int, M, 1> valueMat;
  valueMat << value, distribution.mNumTrials - value.sum();
  return distribution.logpmf(valueMat);
}

template <size_t M>
template <size_t D>
double HyperGeometricDistribution<M>::Traits<2, D>::logpmf(const
    HyperGeometricDistribution<2>& distribution, const int& value) {
  Eigen::Matrix<int, 2, 1> valueMat;
  valueMat << value, distribution.mNumTrials - value;
  return distribution.logpmf(valueMat);
}

template <size_t M>
void HyperGeometricDistribution<M>::setNumTrials(size_t numTrials)
    throw (BadArgumentException<size_t>) {
  if (numTrials > mMarbles.sum())
    throw BadArgumentException<size_t>(numTrials,
      "HyperGeometricDistribution<M>::setNumTrials(): trials number must be "
      "smaller than the number of marbles",
      __FILE__, __LINE__);
  mNumTrials = numTrials;
  Eigen::Matrix<size_t, 2, 1> argument;
  argument << mMarbles.sum(), mNumTrials;
  const LogBinomialFunction logBinomialFunction;
  mNormalizer = logBinomialFunction(argument);
}

template <size_t M>
size_t HyperGeometricDistribution<M>::getNumTrials() const {
  return mNumTrials;
}

template <size_t M>
void HyperGeometricDistribution<M>::setMarbles(const
    Eigen::Matrix<size_t, M, 1>& marbles) {
  mMarbles = marbles;
  Eigen::Matrix<size_t, 2, 1> argument;
  argument << marbles.sum(), mNumTrials;
  const LogBinomialFunction logBinomialFunction;
  mNormalizer = logBinomialFunction(argument);
}

template <size_t M>
const Eigen::Matrix<size_t, M, 1>& HyperGeometricDistribution<M>::getMarbles()
    const {
  return mMarbles;
}

template <size_t M>
double HyperGeometricDistribution<M>::getNormalizer() const {
  return mNormalizer;
}

template <size_t M>
double HyperGeometricDistribution<M>::pmf(const RandomVariable& value) const {
  if (value.sum() != (int)mNumTrials || (value.cwise() < 0).any())
    return 0.0;
  else
    return exp(logpmf(value));
}

template <size_t M>
double HyperGeometricDistribution<M>::pmf(const typename
    DiscreteDistribution<int, M - 1>::Domain& value) const {
  return Traits<M>::pmf(*this, value);
}

template <size_t M>
double HyperGeometricDistribution<M>::logpmf(const RandomVariable&
    value) const throw (BadArgumentException<RandomVariable>) {
  if (value.sum() != (int)mNumTrials || (value.cwise() < 0).any())
    throw BadArgumentException<Eigen::Matrix<int, M, 1> >(value,
      "HyperGeometricDistribution<M>::logpmf(): value has to sum to the trials "
      "number and contains positive values",
      __FILE__, __LINE__);
  Eigen::Matrix<size_t, 2, 1> argument;
  double sum = 0.0;
  const LogBinomialFunction logBinomialFunction;
  for (size_t i = 0; i < (size_t)mMarbles.size(); ++i) {
    argument(0) = mMarbles(i);
    argument(1) = value(i);
    sum += logBinomialFunction(argument);
  }
  return sum - mNormalizer;
}

template <size_t M>
double HyperGeometricDistribution<M>::logpmf(const typename
    DiscreteDistribution<int, M - 1>::Domain& value) const {
  return Traits<M>::logpmf(*this, value);
}

template <size_t M>
typename HyperGeometricDistribution<M>::RandomVariable
    HyperGeometricDistribution<M>::getSample() const {
  // TODO: NOT IMPLEMENTED!
  return RandomVariable::Zero(mMarbles.size());
}

template <size_t M>
typename HyperGeometricDistribution<M>::Mean
    HyperGeometricDistribution<M>::getMean() const {
  return mNumTrials / (double)mMarbles.sum() * mMarbles.template cast<double>();
}

template <size_t M>
typename HyperGeometricDistribution<M>::Covariance
    HyperGeometricDistribution<M>::getCovariance() const {
  Eigen::Matrix<double, M, M> covariance(mMarbles.size(), mMarbles.size());
  const double sum = mMarbles.sum();
  for (size_t i = 0; i < (size_t)mMarbles.size(); ++i) {
    covariance(i, i) = mMarbles(i) / sum * (1 - mMarbles(i) / sum) *
        mNumTrials * (sum - mNumTrials) / (sum - 1);
    for (size_t j = i + 1; j < (size_t)mMarbles.size(); ++j) {
      covariance(i, j) = -1.0 * mNumTrials * mMarbles(i) * mMarbles(j) / sum /
        sum * (sum - mNumTrials) / (sum - 1);
      covariance(j, i) = covariance(i, j);
    }
  }
  return covariance;
}
