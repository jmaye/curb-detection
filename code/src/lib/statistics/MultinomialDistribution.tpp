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

#include "functions/LogFactorialFunction.h"
#include "statistics/Randomizer.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
MultinomialDistribution<M>::MultinomialDistribution(size_t numTrials, const
    Eigen::Matrix<double, M, 1>& probabilities) {
  setProbabilities(probabilities);
  setNumTrials(numTrials);
}

template <size_t M>
MultinomialDistribution<M>::MultinomialDistribution(const
    MultinomialDistribution& other) :
    mProbabilities(other.mProbabilities),
    mNumTrials(other.mNumTrials) {
}

template <size_t M>
MultinomialDistribution<M>& MultinomialDistribution<M>::operator =
    (const MultinomialDistribution& other) {
  if (this != &other) {
    mProbabilities = other.mProbabilities;
    mNumTrials = other.mNumTrials;
  }
  return *this;
}

template <size_t M>
MultinomialDistribution<M>::~MultinomialDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <size_t M>
void MultinomialDistribution<M>::read(std::istream& stream) {
}

template <size_t M>
void MultinomialDistribution<M>::write(std::ostream& stream) const {
  stream << "success probabilities: "
    << mProbabilities.transpose() << std::endl
    << "trials number: " << mNumTrials;
}

template <size_t M>
void MultinomialDistribution<M>::read(std::ifstream& stream) {
}

template <size_t M>
void MultinomialDistribution<M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
void MultinomialDistribution<M>::setProbabilities(const
    Eigen::Matrix<double, M, 1>& probabilities) throw
    (BadArgumentException<Eigen::Matrix<double, M, 1> >) {
  if (fabs(probabilities.sum() - 1.0) > 1e-12 ||
    (probabilities.cwise() < 0).any())
    throw BadArgumentException<Eigen::Matrix<double, M, 1> >(
      probabilities,
      "MultinomialDistribution<M>::setProbabilities(): success "
      "probabilities must sum to 1 and have probabilities bigger or equal to 0",
      __FILE__, __LINE__);
  mProbabilities = probabilities;
}

template <size_t M>
double MultinomialDistribution<M>::getProbability(size_t idx) const
    throw (OutOfBoundException<size_t>) {
  if (idx >= (size_t)mProbabilities.size())
    throw OutOfBoundException<size_t>(idx,
      "MultinomialDistribution<M>::getProbability(): index out of bound",
      __FILE__, __LINE__);
  return mProbabilities(idx);
}

template <size_t M>
const Eigen::Matrix<double, M, 1>&
    MultinomialDistribution<M>::getProbabilities() const {
  return mProbabilities;
}

template <size_t M>
void MultinomialDistribution<M>::setNumTrials(size_t numTrials)
    throw (BadArgumentException<size_t>) {
  if (numTrials == 0)
    throw BadArgumentException<size_t>(numTrials,
      "MultinomialDistribution<M>::setNumTrials(): number of trials must be "
      "strictly positive",
      __FILE__, __LINE__);
  mNumTrials = numTrials;
}

template <size_t M>
size_t MultinomialDistribution<M>::getNumTrials() const {
  return mNumTrials;
}

template <size_t M>
template <size_t N, size_t D>
double MultinomialDistribution<M>::Traits<N, D>::pmf(const
    MultinomialDistribution<N>& distribution, const
    Eigen::Matrix<int, N - 1, 1>& value) {
  Eigen::Matrix<int, M, 1> valueMat;
  valueMat << value, distribution.mNumTrials - value.sum();
  return distribution.pmf(valueMat);
}

template <size_t M>
template <size_t D>
double MultinomialDistribution<M>::Traits<2, D>::pmf(const
    MultinomialDistribution<2>& distribution, const int& value) {
  Eigen::Matrix<int, 2, 1> valueMat;
  valueMat << value, distribution.mNumTrials - value;
  return distribution.pmf(valueMat);
}

template <size_t M>
template <size_t N, size_t D>
double MultinomialDistribution<M>::Traits<N, D>::logpmf(const
    MultinomialDistribution<N>& distribution, const
    Eigen::Matrix<int, N - 1, 1>& value) {
  Eigen::Matrix<int, M, 1> valueMat;
  valueMat << value, distribution.mNumTrials - value.sum();
  return distribution.logpmf(valueMat);
}

template <size_t M>
template <size_t D>
double MultinomialDistribution<M>::Traits<2, D>::logpmf(const
    MultinomialDistribution<2>& distribution, const int& value) {
  Eigen::Matrix<int, 2, 1> valueMat;
  valueMat << value, distribution.mNumTrials - value;
  return distribution.logpmf(valueMat);
}

template <size_t M>
double MultinomialDistribution<M>::pmf(const RandomVariable& value) const {
  if (value.sum() != (int)mNumTrials || (value.cwise() < 0).any())
    return 0.0;
  else
    return exp(logpmf(value));
}

template <size_t M>
double MultinomialDistribution<M>::pmf(const typename
    DiscreteDistribution<int, M - 1>::Domain& value) const {
  return Traits<M>::pmf(*this, value);
}

template <size_t M>
double MultinomialDistribution<M>::logpmf(const RandomVariable& value) const
    throw (BadArgumentException<RandomVariable>) {
  if (value.sum() != (int)mNumTrials || (value.cwise() < 0).any())
    throw BadArgumentException<RandomVariable>(value,
      "MultinomialDistribution<M>::logpmf(): sum of the input vector must be "
      "equal to the number of trials and contains positive values",
      __FILE__, __LINE__);
  const LogFactorialFunction logFactorialFunction;
  double sum = logFactorialFunction(mNumTrials);
  for (size_t i = 0; i < (size_t)mProbabilities.size(); ++i)
    sum += value(i) * log(mProbabilities(i)) -
      logFactorialFunction(value(i));
  return sum;
}

template <size_t M>
double MultinomialDistribution<M>::logpmf(const typename
    DiscreteDistribution<int, M - 1>::Domain& value) const {
  return Traits<M>::logpmf(*this, value);
}

template <size_t M>
typename MultinomialDistribution<M>::RandomVariable
    MultinomialDistribution<M>::getSample() const {
  const static Randomizer<double, M> randomizer;
  RandomVariable sampleVector =
    RandomVariable::Zero(mProbabilities.size());
  for (size_t i = 0; i < mNumTrials; ++i)
    sampleVector(randomizer.sampleCategorical(mProbabilities))++;
  return sampleVector;
}

template <size_t M>
typename MultinomialDistribution<M>::Mean MultinomialDistribution<M>::getMean()
    const {
  return mNumTrials * mProbabilities;
}

template <size_t M>
typename MultinomialDistribution<M>::Mode MultinomialDistribution<M>::getMode()
    const throw (InvalidOperationException) {
  Mode mode = (mProbabilities * (mNumTrials + 1)).template cast<int>();
  if (mode.sum() == (int)mNumTrials)
    return mode;
  else
    throw InvalidOperationException("MultinomialDistribution<M>::getMode(): "
      "invalid mode");
}

template <size_t M>
typename MultinomialDistribution<M>::Covariance
    MultinomialDistribution<M>::getCovariance() const {
  Covariance covariance(mProbabilities.size(), mProbabilities.size());
  for (size_t i = 0; i < (size_t)mProbabilities.size(); ++i) {
    covariance(i, i) = mNumTrials * mProbabilities(i) * (1 - mProbabilities(i));
    for (size_t j = i + 1; j < (size_t)mProbabilities.size(); ++j) {
      covariance(i, j) = -1.0 * mNumTrials * mProbabilities(i) *
        mProbabilities(j);
      covariance(j, i) = covariance(i, j);
    }
  }
  return covariance;
}
