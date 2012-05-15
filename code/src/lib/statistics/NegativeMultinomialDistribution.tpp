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

#include "utils/OuterProduct.h"
#include "functions/LogGammaFunction.h"
#include "functions/LogFactorialFunction.h"
#include "exceptions/BadArgumentException.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
NegativeMultinomialDistribution<M>::NegativeMultinomialDistribution(size_t
    numTrials, const Eigen::Matrix<double, M, 1>& probabilities) {
  setProbabilities(probabilities);
  setNumTrials(numTrials);
}

template <size_t M>
NegativeMultinomialDistribution<M>::NegativeMultinomialDistribution(const
    NegativeMultinomialDistribution& other) :
    mProbabilities(other.mProbabilities),
    mNumTrials(other.mNumTrials) {
}

template <size_t M>
NegativeMultinomialDistribution<M>&
    NegativeMultinomialDistribution<M>::operator =
    (const NegativeMultinomialDistribution& other) {
  if (this != &other) {
    mProbabilities = other.mProbabilities;
    mNumTrials = other.mNumTrials;
  }
  return *this;
}

template <size_t M>
NegativeMultinomialDistribution<M>::~NegativeMultinomialDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <size_t M>
void NegativeMultinomialDistribution<M>::read(std::istream& stream) {
}

template <size_t M>
void NegativeMultinomialDistribution<M>::write(std::ostream& stream) const {
  stream << "success probabilities: "
    << mProbabilities.transpose() << std::endl
    << "trials number: " << mNumTrials;
}

template <size_t M>
void NegativeMultinomialDistribution<M>::read(std::ifstream& stream) {
}

template <size_t M>
void NegativeMultinomialDistribution<M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
void NegativeMultinomialDistribution<M>::setProbabilities(const
    Eigen::Matrix<double, M, 1>& probabilities) {
  if (fabs(probabilities.sum() - 1.0) >
    std::numeric_limits<double>::epsilon() ||
    (probabilities.cwise() < 0).any())
    throw BadArgumentException<Eigen::Matrix<double, M, 1> >(
      probabilities,
      "NegativeMultinomialDistribution<M>::setProbabilities(): success "
      "probabilities must sum to 1 and have probabilities bigger or equal to 0",
      __FILE__, __LINE__);
  mProbabilities = probabilities;
}

template <size_t M>
const Eigen::Matrix<double, M, 1>&
    NegativeMultinomialDistribution<M>::getProbabilities() const {
  return mProbabilities;
}

template <size_t M>
void NegativeMultinomialDistribution<M>::setNumTrials(size_t numTrials) {
  if (numTrials == 0)
    throw BadArgumentException<size_t>(numTrials,
      "NegativeMultinomialDistribution<M>::setNumTrials(): number of trials "
      "must be strictly positive",
      __FILE__, __LINE__);
  mNumTrials = numTrials;
}

template <size_t M>
size_t NegativeMultinomialDistribution<M>::getNumTrials() const {
  return mNumTrials;
}

template <size_t M>
template <size_t N, size_t D>
double NegativeMultinomialDistribution<M>::Traits<N, D>::pmf(const
    NegativeMultinomialDistribution<N>& distribution, const
    Eigen::Matrix<int, N - 1, 1>& value) {
  Eigen::Matrix<int, M, 1> valueMat;
  valueMat << value, distribution.mNumTrials;
  return distribution.pmf(valueMat);
}

template <size_t M>
template <size_t D>
double NegativeMultinomialDistribution<M>::Traits<2, D>::pmf(const
    NegativeMultinomialDistribution<2>& distribution, const int& value) {
  Eigen::Matrix<int, 2, 1> valueMat;
  valueMat << value, distribution.mNumTrials;
  return distribution.pmf(valueMat);
}

template <size_t M>
template <size_t N, size_t D>
double NegativeMultinomialDistribution<M>::Traits<N, D>::logpmf(const
    NegativeMultinomialDistribution<N>& distribution, const
    Eigen::Matrix<int, N - 1, 1>& value) {
  Eigen::Matrix<int, M, 1> valueMat;
  valueMat << value, distribution.mNumTrials;
  return distribution.logpmf(valueMat);
}

template <size_t M>
template <size_t D>
double NegativeMultinomialDistribution<M>::Traits<2, D>::logpmf(const
    NegativeMultinomialDistribution<2>& distribution, const int& value) {
  Eigen::Matrix<int, 2, 1> valueMat;
  valueMat << value, distribution.mNumTrials;
  return distribution.logpmf(valueMat);
}

template <size_t M>
double NegativeMultinomialDistribution<M>::pmf(const RandomVariable& value)
    const {
  if (value(value.size() - 1) != (int)mNumTrials ||
      (value.cwise() < 0).any())
    return 0.0;
  else
    return exp(logpmf(value));
}

template <size_t M>
double NegativeMultinomialDistribution<M>::pmf(const typename
    DiscreteDistribution<int, M - 1>::Domain& value) const {
  return Traits<M>::pmf(*this, value);
}

template <size_t M>
double NegativeMultinomialDistribution<M>::logpmf(const RandomVariable& value)
    const {
  if (value(value.size() - 1) != (int)mNumTrials ||
      (value.cwise() < 0).any())
    throw BadArgumentException<Eigen::Matrix<int, M, 1> >(value,
      "NegativeMultinomialDistribution<M>::logpmf(): value(M) must contain the "
      "trial numbers and be stricly positive",
      __FILE__, __LINE__);
  const LogGammaFunction<size_t> lgamma;
  double sum = lgamma(value.sum()) - lgamma(mNumTrials) +
    mNumTrials * log(mProbabilities(value.size() - 1));
  const LogFactorialFunction lfactorial;
  for (size_t i = 0; i < (size_t)mProbabilities.size() - 1; ++i)
    sum += value(i) *
      log(mProbabilities(i)) - lfactorial(value(i));
  return sum;
}

template <size_t M>
double NegativeMultinomialDistribution<M>::logpmf(const typename
    DiscreteDistribution<int, M - 1>::Domain& value) const {
  return Traits<M>::logpmf(*this, value);
}

template <size_t M>
typename NegativeMultinomialDistribution<M>::RandomVariable
    NegativeMultinomialDistribution<M>::getSample() const {
  // TODO: NOT IMPLEMENTED!
  return RandomVariable::Zero(mProbabilities.size());
}

template <size_t M>
typename NegativeMultinomialDistribution<M>::Mean
    NegativeMultinomialDistribution<M>::getMean() const {
  return mNumTrials / mProbabilities(mProbabilities.size() - 1) *
    mProbabilities;
}

template <size_t M>
typename NegativeMultinomialDistribution<M>::Covariance
    NegativeMultinomialDistribution<M>::getCovariance() const {
  // TODO: COVARIANCE NOT IMPLEMENTED
  const double fail = mProbabilities(mProbabilities.size() - 1);
  return mNumTrials / fail / fail *
    outerProduct<double, M>(mProbabilities) + mNumTrials /
    fail * mProbabilities.asDiagonal();
}
