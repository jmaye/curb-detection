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

#include <statistics/Randomizer.h>

#include <Eigen/Array>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename X, size_t M>
UniformDistribution<X, M>::UniformDistribution(const Eigen::Matrix<X, M, 1>&
  minSupport, const Eigen::Matrix<X, M, 1>& maxSupport) :
  mSupportArea(0.0) {
  setSupport(minSupport, maxSupport);
}

template <typename X, size_t M>
UniformDistribution<X, M>::UniformDistribution(const UniformDistribution<X, M>&
  other) :
  mMinSupport(other.mMinSupport),
  mMaxSupport(other.mMaxSupport),
  mSupportArea(other.mSupportArea) {
}

template <typename X, size_t M>
UniformDistribution<X, M>& UniformDistribution<X, M>::operator =
  (const UniformDistribution<X, M>& other) {
  if (this != &other) {
    mMaxSupport = other.mMaxSupport;
    mMinSupport = other.mMinSupport;
    mSupportArea = other.mSupportArea;
  }
  return *this;
}

template <typename X, size_t M>
UniformDistribution<X, M>::~UniformDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename X, size_t M>
void UniformDistribution<X, M>::read(std::istream& stream) {
}

template <typename X, size_t M>
void UniformDistribution<X, M>::write(std::ostream& stream) const {
  stream << "minimum support: " << std::endl << mMinSupport << std::endl
    << "maximum support: " << std::endl << mMaxSupport << std::endl
    << "support area: " << mSupportArea;
}

template <typename X, size_t M>
void UniformDistribution<X, M>::read(std::ifstream& stream) {
}

template <typename X, size_t M>
void UniformDistribution<X, M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename X, size_t M>
void UniformDistribution<X, M>::setSupport(const Eigen::Matrix<X, M, 1>&
  minSupport, const Eigen::Matrix<X, M, 1>& maxSupport)
  throw (BadArgumentException<Eigen::Matrix<X, M, 1> >) {
  if ((minSupport.cwise() >= maxSupport).any())
    throw BadArgumentException<Eigen::Matrix<X, M, 1> >(minSupport,
      "UniformDistribution<X, M>::setSupport(): minimum support must be "
      "smaller than maximum support",
      __FILE__, __LINE__);
  mMinSupport = minSupport;
  mMaxSupport = maxSupport;
  mSupportArea = 1;
  for (size_t i = 0; i < (size_t)mMinSupport.size(); ++i)
    mSupportArea *= mMaxSupport(i) - mMinSupport(i);
}

template <typename X, size_t M>
void UniformDistribution<X, M>::setMinSupport(const Eigen::Matrix<X, M, 1>&
  minSupport) {
  setSupport(minSupport, mMaxSupport);
}

template <typename X, size_t M>
const Eigen::Matrix<X, M, 1>& UniformDistribution<X, M>::getMinSupport() const {
  return mMinSupport;
}

template <typename X, size_t M>
void UniformDistribution<X, M>::setMaxSupport(const Eigen::Matrix<X, M, 1>&
  maxSupport) {
  setSupport(mMinSupport, maxSupport);
}

template <typename X, size_t M>
const Eigen::Matrix<X, M, 1>& UniformDistribution<X, M>::getMaxSupport() const {
  return mMaxSupport;
}

template <typename X, size_t M>
X UniformDistribution<X, M>::getSupportArea() const {
  return mSupportArea;
}

template <typename X, size_t M>
template <typename U, size_t D>
double UniformDistribution<X, M>::Traits<U, D>::pdf(const
  UniformDistribution<U, M>& distribution, const Eigen::Matrix<U, M, 1>&
  value) {
  return Traits<U>::pmf(distribution, value);
}

template <typename X, size_t M>
template <typename U, size_t D>
double UniformDistribution<X, M>::Traits<U, D>::pmf(const
  UniformDistribution<U, M>& distribution, const Eigen::Matrix<U, M, 1>&
  value) {
  U supportArea = 1;
  for (size_t i = 0; i < (size_t)distribution.mMinSupport.size(); ++i)
    supportArea *= distribution.mMaxSupport(i) -
      distribution.mMinSupport(i) + 1;
  if ((value.cwise() >= distribution.mMinSupport).all() &&
    (value.cwise() <=distribution. mMaxSupport).all())
    return 1.0 / supportArea;
  else
    return 0.0;
}

template <typename X, size_t M>
template <size_t D>
double UniformDistribution<X, M>::Traits<float, D>::pdf(const
  UniformDistribution<float, M>& distribution, const Eigen::Matrix<float, M, 1>&
  value) {
  if ((value.cwise() >= distribution.mMinSupport).all() &&
    (value.cwise() <= distribution.mMaxSupport).all())
    return 1.0 / distribution.mSupportArea;
  else
    return 0.0;
}

template <typename X, size_t M>
template <size_t D>
double UniformDistribution<X, M>::Traits<float, D>::pmf(const
  UniformDistribution<float, M>& distribution, const Eigen::Matrix<float, M, 1>&
  value) {
  return Traits<float>::pdf(distribution, value);
}

template <typename X, size_t M>
template <size_t D>
double UniformDistribution<X, M>::Traits<double, D>::pdf(const
  UniformDistribution<double, M>& distribution, const
  Eigen::Matrix<double, M, 1>& value) {
  if ((value.cwise() >= distribution.mMinSupport).all() &&
    (value.cwise() <= distribution.mMaxSupport).all())
    return 1.0 / distribution.mSupportArea;
  else
    return 0.0;
}

template <typename X, size_t M>
template <size_t D>
double UniformDistribution<X, M>::Traits<double, D>::pmf(const
  UniformDistribution<double, M>& distribution, const
  Eigen::Matrix<double, M, 1>& value) {
  return Traits<double>::pdf(distribution, value);
}

template <typename X, size_t M>
double UniformDistribution<X, M>::pdf(const Eigen::Matrix<X, M, 1>& value)
  const {
  return Traits<X>::pdf(*this, value);
}

template <typename X, size_t M>
double UniformDistribution<X, M>::pmf(const Eigen::Matrix<X, M, 1>& value)
  const {
  return Traits<X>::pmf(*this, value);
}

template <typename X, size_t M>
Eigen::Matrix<X, M, 1> UniformDistribution<X, M>::getSample() const {
  const static Randomizer<X> randomizer;
  Eigen::Matrix<X, M, 1> sample(mMinSupport.size());
  for (size_t i = 0; i < M; ++i)
    sample(i) = randomizer.sampleUniform(mMinSupport(i), mMaxSupport(i));
  return sample;
}
