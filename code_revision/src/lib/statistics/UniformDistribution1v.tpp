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

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename X>
UniformDistribution<X>::UniformDistribution(const X& minSupport,
  const X& maxSupport) {
  setSupport(minSupport, maxSupport);
}

template <typename X>
UniformDistribution<X>::UniformDistribution(const UniformDistribution<X>&
  other) :
  mMinSupport(other.mMinSupport),
  mMaxSupport(other.mMaxSupport) {
}

template <typename X>
UniformDistribution<X>& UniformDistribution<X>::operator =
  (const UniformDistribution<X>& other) {
  if (this != &other) {
    mMaxSupport = other.mMaxSupport;
    mMinSupport = other.mMinSupport;
  }
  return *this;
}

template <typename X>
UniformDistribution<X>::~UniformDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename X>
void UniformDistribution<X>::read(std::istream& stream) {
}

template <typename X>
void UniformDistribution<X>::write(std::ostream& stream) const {
  stream << "minimum support: " << mMinSupport << std::endl
    << "maximum support: " << mMaxSupport;
}

template <typename X>
void UniformDistribution<X>::read(std::ifstream& stream) {
}

template <typename X>
void UniformDistribution<X>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename X>
void UniformDistribution<X>::setSupport(const X& minSupport, const X&
  maxSupport) throw (BadArgumentException<X>) {
  if (minSupport >= maxSupport)
    throw BadArgumentException<X>(minSupport,
      "UniformDistribution<X>::setSupport(): minimum support must be smaller "
      "than maximum support",
      __FILE__, __LINE__);
  mMinSupport = minSupport;
  mMaxSupport = maxSupport;
}

template <typename X>
void UniformDistribution<X>::setMinSupport(const X& minSupport) {
  setSupport(minSupport, mMaxSupport);
}

template <typename X>
const X& UniformDistribution<X>::getMinSupport() const {
  return mMinSupport;
}

template <typename X>
void UniformDistribution<X>::setMaxSupport(const X& maxSupport) {
  setSupport(mMinSupport, maxSupport);
}

template <typename X>
const X& UniformDistribution<X>::getMaxSupport() const {
  return mMaxSupport;
}

template <typename X>
template <typename U, size_t D>
double UniformDistribution<X>::Traits<U, D>::pdf(const UniformDistribution<U>&
  distribution, U value) {
  return Traits<U>::pmf(distribution, value);
}

template <typename X>
template <typename U, size_t D>
double UniformDistribution<X>::Traits<U, D>::pmf(const UniformDistribution<U>&
  distribution, U value) {
  if (value >= distribution.mMinSupport && value <= distribution.mMaxSupport)
    return 1.0 / (distribution.mMaxSupport - distribution.mMinSupport + 1);
  else
    return 0.0;
}

template <typename X>
template <typename U, size_t D>
double UniformDistribution<X>::Traits<U, D>::getVariance(const
  UniformDistribution<U>& distribution) {
  return ((distribution.mMaxSupport - distribution.mMinSupport + 1) *
    (distribution.mMaxSupport - distribution.mMinSupport + 1) - 1) / 12.0 - 1.0;
}

template <typename X>
template <size_t D>
double UniformDistribution<X>::Traits<float, D>::pdf(const
  UniformDistribution<float>& distribution, float value) {
  if (value >= distribution.mMinSupport && value <= distribution.mMaxSupport)
    return 1.0 / (distribution.mMaxSupport - distribution.mMinSupport);
  else
    return 0.0;
}

template <typename X>
template <size_t D>
double UniformDistribution<X>::Traits<float, D>::pmf(const
  UniformDistribution<float>& distribution, float value) {
  return Traits<float>::pdf(distribution, value);
}

template <typename X>
template <size_t D>
double UniformDistribution<X>::Traits<float, D>::getVariance(const
  UniformDistribution<float>& distribution) {
  return ((distribution.mMaxSupport - distribution.mMinSupport) *
    (distribution.mMaxSupport - distribution.mMinSupport)) / 12.0;
}

template <typename X>
template <size_t D>
double UniformDistribution<X>::Traits<double, D>::pdf(const
  UniformDistribution<double>& distribution, double value) {
  if (value >= distribution.mMinSupport && value <= distribution.mMaxSupport)
    return 1.0 / (distribution.mMaxSupport - distribution.mMinSupport);
  else
    return 0.0;
}

template <typename X>
template <size_t D>
double UniformDistribution<X>::Traits<double, D>::pmf(const
  UniformDistribution<double>& distribution, double value) {
  return Traits<double>::pdf(distribution, value);
}

template <typename X>
template <size_t D>
double UniformDistribution<X>::Traits<double, D>::getVariance(const
  UniformDistribution<double>& distribution) {
  return ((distribution.mMaxSupport - distribution.mMinSupport) *
    (distribution.mMaxSupport - distribution.mMinSupport)) / 12.0;
}

template <typename X>
double UniformDistribution<X>::pdf(const X& value) const {
  return Traits<X>::pdf(*this, value);
}

template <typename X>
double UniformDistribution<X>::pmf(const X& value) const {
  return Traits<X>::pmf(*this, value);
}

template <typename X>
X UniformDistribution<X>::getSample() const {
  static Randomizer<X> randomizer;
  return randomizer.sampleUniform(mMinSupport, mMaxSupport);
}

template <typename X>
double UniformDistribution<X>::getMean() const {
  return 0.5 * (mMaxSupport - mMinSupport);
}

template <typename X>
double UniformDistribution<X>::getMedian() const {
  return 0.5 * (mMaxSupport - mMinSupport);
}

template <typename X>
double UniformDistribution<X>::getMode() const {
  return mMinSupport;
}

template <typename X>
double UniformDistribution<X>::getVariance() const {
  return Traits<X>::getVariance(*this);
}
