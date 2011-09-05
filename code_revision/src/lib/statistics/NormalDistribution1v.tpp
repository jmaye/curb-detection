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

NormalDistribution<1>::NormalDistribution(double mean, double variance) :
  mMean(mean) {
  setVariance(variance);
}

NormalDistribution<1>::NormalDistribution(const NormalDistribution<1>& other) :
  mMean(other.mMean),
  mVariance(other.mVariance),
  mPrecision(other.mPrecision),
  mStandardDeviation(other.mStandardDeviation),
  mNormalizer(other.mNormalizer) {
}

NormalDistribution<1>& NormalDistribution<1>::operator =
  (const NormalDistribution<1>& other) {
  if (this != &other) {
    mMean = other.mMean;
    mVariance = other.mVariance;
    mPrecision = other.mPrecision;
    mStandardDeviation = other.mStandardDeviation;
    mNormalizer = other.mNormalizer;
  }
  return *this;
}

NormalDistribution<1>::~NormalDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void NormalDistribution<1>::read(std::istream& stream) {
}

void NormalDistribution<1>::write(std::ostream& stream) const {
  stream << "mean: " << mMean << std::endl
    << "variance: " << mVariance;
}

void NormalDistribution<1>::read(std::ifstream& stream) {
}

void NormalDistribution<1>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void NormalDistribution<1>::setMean(double mean) {
  mMean = mean;
}

double NormalDistribution<1>::getMean() const {
  return mMean;
}

void NormalDistribution<1>::setVariance(double variance)
  throw (BadArgumentException<double>) {
  mVariance = variance;
  if (mVariance <= 0.0)
    throw BadArgumentException<double>(variance,
      "NormalDistribution::setVariance(): variance must be strictly bigger "
      "than 0",
      __FILE__, __LINE__);
  mPrecision = 1.0 / variance;
  mStandardDeviation = sqrt(variance);
  mNormalizer = 0.5 * log(2.0 * M_PI * mVariance);
}

double NormalDistribution<1>::getVariance() const {
  return mVariance;
}

double NormalDistribution<1>::getPrecision() const {
  return mPrecision;
}

double NormalDistribution<1>::getStandardDeviation() const {
  return mStandardDeviation;
}

double NormalDistribution<1>::getNormalizer() const {
  return mNormalizer;
}

double NormalDistribution<1>::pdf(const double& value) const {
  return exp(logpdf(value));
}

double NormalDistribution<1>::logpdf(const double& value) const {
  return -0.5 * mahalanobisDistance(value) - mNormalizer;
}

double NormalDistribution<1>::cdf(const double& value) const {
  return 0.5 * (1.0 + erf((value - mMean) / sqrt(2 * mVariance)));
}

double NormalDistribution<1>::getSample() const {
  static Randomizer<double> randomizer;
  return randomizer.sampleNormal(mMean, mVariance);
}

double NormalDistribution<1>::KLDivergence(const NormalDistribution<1>& other)
  const {
  return 0.5 * (log(other.mVariance * mPrecision) +
    other.mPrecision * mVariance - 1.0 +
    (mMean - other.mMean) * other.mPrecision * (mMean - other.mMean));
}

double NormalDistribution<1>::mahalanobisDistance(const double& value) const {
  return (value - mMean) * mPrecision * (value - mMean);
}

double NormalDistribution<1>::getMedian() const {
  return mMean;
}

double NormalDistribution<1>::getMode() const {
  return mMean;
}
