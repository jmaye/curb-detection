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

#include "statistics/Randomizer.h"

#include <Eigen/Array>

#include <limits>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/
template <size_t M>
CategoricalDistribution<M>::CategoricalDistribution(const
  Eigen::Matrix<double, M, 1>& successProbabilities) {
  setSuccessProbabilities(successProbabilities);
}

template <size_t M>
CategoricalDistribution<M>::CategoricalDistribution(const
  CategoricalDistribution<M>& other) :
  mSuccessProbabilities(other.mSuccessProbabilities) {
}

template <size_t M>
CategoricalDistribution<M>& CategoricalDistribution<M>::operator = (const
  CategoricalDistribution<M>& other) {
  if (this != &other) {
    mSuccessProbabilities = other.mSuccessProbabilities;
  }
  return *this;
}

template <size_t M>
CategoricalDistribution<M>::~CategoricalDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <size_t M>
void CategoricalDistribution<M>::read(std::istream& stream) {
}

template <size_t M>
void CategoricalDistribution<M>::write(std::ostream& stream) const {
  stream << "success probabilities: " << mSuccessProbabilities.transpose();
}

template <size_t M>
void CategoricalDistribution<M>::read(std::ifstream& stream) {
}

template <size_t M>
void CategoricalDistribution<M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
void CategoricalDistribution<M>::setSuccessProbabilities(const
  Eigen::Matrix<double, M, 1>& successProbabilities) throw
  (BadArgumentException<Eigen::Matrix<double, M, 1> >) {
  if (fabs(successProbabilities.sum() - 1.0) >
    std::numeric_limits<double>::epsilon() ||
    (successProbabilities.cwise() < 0).any() == true)
    throw BadArgumentException<Eigen::Matrix<double, M, 1> >(successProbabilities,
      "CategoricalDistribution::setSuccessProbabilities(): success "
      "probabilities must sum to 1 and probabilities bigger or equal to 0",
      __FILE__, __LINE__);
  mSuccessProbabilities = successProbabilities;
}

template <size_t M>
const Eigen::Matrix<double, M, 1>&
  CategoricalDistribution<M>::getSuccessProbabilities() const {
  return mSuccessProbabilities;
}

template <size_t M>
template <size_t N, size_t D>
double CategoricalDistribution<M>::Traits<N, D>::pmf(const
  CategoricalDistribution<N>& distribution, const
  Eigen::Matrix<size_t, N - 1, 1>& value) {
  Eigen::Matrix<size_t, M, 1> valueMat;
  if ((value.cwise() == 1).any() == true)
    valueMat << 0, value;
  else
    valueMat << 1, value;
  return distribution.pmf(valueMat);
}

template <size_t M>
template <size_t D>
double CategoricalDistribution<M>::Traits<2, D>::pmf(const
  CategoricalDistribution<2>& distribution, const size_t& value) {
  Eigen::Matrix<size_t, 2, 1> valueMat;
  if (value)
    valueMat << 0, value;
  else
    valueMat << 1, value;
  return distribution.pmf(valueMat);
}

template <size_t M>
template <size_t N, size_t D>
double CategoricalDistribution<M>::Traits<N, D>::logpmf(const
  CategoricalDistribution<N>& distribution, const
  Eigen::Matrix<size_t, N - 1, 1>& value) {
  Eigen::Matrix<size_t, M, 1> valueMat;
  if ((value.cwise() == 1).any() == true)
    valueMat << 0, value;
  else
    valueMat << 1, value;
  return distribution.logpmf(valueMat);
}

template <size_t M>
template <size_t D>
double CategoricalDistribution<M>::Traits<2, D>::logpmf(const
  CategoricalDistribution<2>& distribution, const size_t& value) {
  Eigen::Matrix<size_t, 2, 1> valueMat;
  if (value)
    valueMat << 0, value;
  else
    valueMat << 1, value;
  return distribution.logpmf(valueMat);
}

template <size_t M>
double CategoricalDistribution<M>::pmf(const typename
  DiscreteDistribution<size_t, M - 1>::Domain& value) const {
  return Traits<M>::pmf(*this, value);
}

template <size_t M>
double CategoricalDistribution<M>::pmf(const Eigen::Matrix<size_t, M, 1>& value)
  const {
  if (value.sum() != 1)
    return 0.0;
  else
    return exp(logpmf(value));
}

template <size_t M>
double CategoricalDistribution<M>::logpmf(const Eigen::Matrix<size_t, M, 1>&
  value) const throw (BadArgumentException<Eigen::Matrix<size_t, M, 1> >) {
  if (value.sum() != 1)
    throw BadArgumentException<Eigen::Matrix<size_t, M, 1> >(value,
      "CategoricalDistribution<M>::logpmf(): 1-of-K encoding required",
      __FILE__, __LINE__);
  double sum = 0.0;
  for (size_t i = 0; i < (size_t)mSuccessProbabilities.size(); ++i)
    sum += value(i) * log(mSuccessProbabilities(i));
  return sum;
}

template <size_t M>
double CategoricalDistribution<M>::logpmf(const typename
  DiscreteDistribution<size_t, M - 1>::Domain& value) const {
  return Traits<M>::logpmf(*this, value);
}

template <size_t M>
Eigen::Matrix<size_t, M, 1> CategoricalDistribution<M>::getSample() const {
  const static Randomizer<double, M> randomizer;
  return randomizer.sampleCategorical(mSuccessProbabilities);
}

template <size_t M>
Eigen::Matrix<double, M, 1> CategoricalDistribution<M>::getMean() const {
  return mSuccessProbabilities;
}

template <size_t M>
Eigen::Matrix<double, M, M> CategoricalDistribution<M>::getCovariance() const {
  Eigen::Matrix<double, M, M> covariance(mSuccessProbabilities.size(),
    mSuccessProbabilities.size());
  for (size_t i = 0; i < (size_t)mSuccessProbabilities.size(); ++i) {
    covariance(i, i) = mSuccessProbabilities(i) * (1 -
      mSuccessProbabilities(i));
    for (size_t j = i + 1; j < (size_t)mSuccessProbabilities.size(); ++j) {
      covariance(i, j) = -mSuccessProbabilities(i) * mSuccessProbabilities(j);
      covariance(j, i) = covariance(i, j);
    }
  }
  return covariance;
}
