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

#include "base/Timestamp.h"

#include <Eigen/Array>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename T, size_t M>
Randomizer<T, M>::Randomizer(const T& seed) :
  mSeed(seed) {
}

template <typename T, size_t M>
Randomizer<T, M>::Randomizer(const Randomizer<T, M>& other) :
  mSeed(other.mSeed) {
}

template <typename T, size_t M>
Randomizer<T, M>& Randomizer<T, M>::operator = (const Randomizer<T, M>& other) {
  if (this != &other) {
    mSeed = other.mSeed;
  }
  return *this;
}

template <typename T, size_t M>
Randomizer<T, M>::~Randomizer() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename T, size_t M>
void Randomizer<T, M>::read(std::istream& stream) {
}

template <typename T, size_t M>
void Randomizer<T, M>::write(std::ostream& stream) const {
  stream << "seed: " << mSeed;
}

template <typename T, size_t M>
void Randomizer<T, M>::read(std::ifstream& stream) {
}

template <typename T, size_t M>
void Randomizer<T, M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename T, size_t M>
void Randomizer<T, M>::setSeed(const T& seed) {
  mSeed = seed;
  srandom(seed);
}

template <typename T, size_t M>
T Randomizer<T, M>::getSeed() {
  static bool seeded = false;
  if (!seeded) {
    double time = Timestamp::now();
    T seed = (time - floor(time)) * 1e6;
    srandom(seed);
    seeded = true;
  }
  return random();
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

template <typename T, size_t M>
T Randomizer<T, M>::sampleUniform(const T& minSupport, const T& maxSupport)
  const throw (BadArgumentException<T>) {
  if (minSupport >= maxSupport)
    throw BadArgumentException<T>(minSupport,
      "Randomizer<T, M>::sampleUniform(): minimum support must be smaller "
      "than maximum support",
      __FILE__, __LINE__);
  return minSupport + Traits<T>::round(random() / (double)RAND_MAX *
    (maxSupport - minSupport));
}

template <typename T, size_t M>
T Randomizer<T, M>::sampleNormal(const T& mean, const T& variance) const
  throw (BadArgumentException<T>) {
  if (variance <= 0)
    throw BadArgumentException<T>(variance,
      "Randomizer<T, M>::sampleNormal(): variance must be strictly positive",
      __FILE__, __LINE__);
  double u, v, s;
  do {
    u = 2.0 * sampleUniform() - 1.0;
    v = 2.0 * sampleUniform() - 1.0;
    s = u * u + v * v;
  }
  while (s >= 1.0 || s == 0.0);

  return Traits<T>::round(mean + sqrt(variance) * u * sqrt(-2.0 * log(s) / s));
}

template <typename T, size_t M>
Eigen::Matrix<size_t, M, 1> Randomizer<T, M>::sampleCategorical(const
  Eigen::Matrix<double, M, 1>& successProbabilities) const
  throw (BadArgumentException<Eigen::Matrix<double, M, 1> >) {
  if (fabs(successProbabilities.sum() - 1.0) >
    std::numeric_limits<double>::epsilon() ||
    (successProbabilities.cwise() < 0).any() == true)
    throw BadArgumentException<Eigen::Matrix<double, M, 1> >(
      successProbabilities,
      "Randomizer<T, M>::sampleCategorical: success probabilities must sum "
      "to 1 and probabilities bigger or equal to 0",
      __FILE__, __LINE__);
  Eigen::Matrix<double, Eigen::Dynamic, 1> cumProbabilities =
    Eigen::Matrix<double, Eigen::Dynamic, 1>::Zero(successProbabilities.size()
      + 1);
  double sum = 0.0;
  for (size_t i = 1; i < (size_t)successProbabilities.size() + 1; ++i) {
    sum += successProbabilities(i - 1);
    cumProbabilities(i) += sum;
  }
  double u = sampleUniform();
  Eigen::Matrix<size_t, M, 1> sample =
    Eigen::Matrix<size_t, M, 1>::Zero(successProbabilities.size());
  for (size_t i = 1; i < (size_t)cumProbabilities.size(); ++i) {
    if (u > cumProbabilities(i - 1) && u <= cumProbabilities(i)) {
      sample(i - 1)++;
      return sample;
    }
  }
  sample(successProbabilities.size() - 1)++;
  return sample;
}

template <typename T, size_t M>
size_t Randomizer<T, M>::samplePoisson(double mean) const
  throw (BadArgumentException<double>) {
  if (mean <= 0)
    throw BadArgumentException<double>(mean,
      "Randomizer<T, M>::samplePoisson(): mean must be strictly positive",
      __FILE__, __LINE__);
  double l = exp(-mean);
  size_t k = 0;
  double p = 1.0;
  do {
    k++;
    p *= sampleUniform();
  }
  while (p > l);
  return k - 1;
}

template <typename T, size_t M>
double Randomizer<T, M>::sampleExponential(double rate) const
  throw (BadArgumentException<double>) {
  if (rate <= 0)
    throw BadArgumentException<double>(rate,
      "Randomizer<T, M>::sampleExponential(): rate must be strictly positive",
      __FILE__, __LINE__);
  double u;
  do {
    u = sampleUniform();
  }
  while (u == 0);
  return -log(u) / rate;
}

template <typename T, size_t M>
size_t Randomizer<T, M>::sampleGeometric(double successProbability) const
  throw (BadArgumentException<double>) {
  if (successProbability <= 0.0 || successProbability > 1.0)
    throw BadArgumentException<double>(successProbability,
      "Randomizer<T, M>::sampleGeometric(): success probability must be "
      "between 0 and 1",
      __FILE__, __LINE__);
  double u;
  do {
    u = sampleUniform();
  }
  while (u == 0);
  return floor(log(u) / log(1 - successProbability));
}

template <typename T, size_t M>
double Randomizer<T, M>::sampleGamma(double shape, double invScale) const
  throw (BadArgumentException<double>) {
  if (shape <= 0)
    throw BadArgumentException<double>(shape,
      "Randomizer<T, M>::sampleGamma(): shape must be strictly positive",
      __FILE__, __LINE__);
  if (invScale <= 0)
    throw BadArgumentException<double>(invScale,
      "Randomizer<T, M>::sampleGamma(): inverse scale must be strictly "
      "positive",
      __FILE__, __LINE__);
  size_t integralPart = floor(shape);
  double fractionalPart = shape - integralPart;
  double y = 0;
  for (size_t i = 0; i < integralPart; ++i)
    y += sampleExponential(1.0);
  double b = (M_E + fractionalPart) / M_E;
  double z = 0;
  if (fabs(fractionalPart - 0) > std::numeric_limits<double>::epsilon())
    while (true) {
      double p = b * sampleUniform();
      if (p > 1) {
        z = -log((b - p) / fractionalPart);
        if (sampleUniform() > pow(z, fractionalPart - 1))
          continue;
        else
          break;
      }
      else {
        z = pow(p, 1.0 / fractionalPart);
        if (sampleUniform() > exp(-z))
          continue;
        else
          break;
      }
    }
  return (y + z) / invScale;
}

template <typename T, size_t M>
template <typename U, size_t D>
U Randomizer<T, M>::Traits<U, D>::round(double value) {
  return (U)::round(value);
}

template <typename T, size_t M>
template <size_t D>
float Randomizer<T, M>::Traits<float, D>::round(float value) {
  return value;
}

template <typename T, size_t M>
template <size_t D>
double Randomizer<T, M>::Traits<double, D>::round(double value) {
  return value;
}
