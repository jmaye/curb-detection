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

ExponentialDistribution::ExponentialDistribution(double rate) {
  setRate(rate);
}

ExponentialDistribution::ExponentialDistribution(const
  ExponentialDistribution& other) :
  mRate(other.mRate){
}

ExponentialDistribution& ExponentialDistribution::operator =
  (const ExponentialDistribution& other) {
  if (this != &other) {
    mRate = other.mRate;
  }
  return *this;
}

ExponentialDistribution::~ExponentialDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void ExponentialDistribution::read(std::istream& stream) {
}

void ExponentialDistribution::write(std::ostream& stream) const {
  stream << "rate: " << mRate;
}

void ExponentialDistribution::read(std::ifstream& stream) {
}

void ExponentialDistribution::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void ExponentialDistribution::setRate(double rate)
  throw (BadArgumentException<double>) {
  if (rate <= 0)
    throw BadArgumentException<double>(rate,
      "ExponentialDistribution::setRate(): rate must be strictly positive",
      __FILE__, __LINE__);
  mRate = rate;
}

double ExponentialDistribution::getRate() const {
  return mRate;
}

double ExponentialDistribution::pdf(const double& value) const {
  if (value < 0)
    return 0.0;
  else
    return exp(logpdf(value));
}

double ExponentialDistribution::logpdf(const double& value) const {
  return log(mRate) - mRate * value;
}

double ExponentialDistribution::cdf(const double& value) const {
  if (value < 0)
    return 0.0;
  else
    return 1 - exp(-mRate * value);
}

double ExponentialDistribution::getSample() const {
  const static Randomizer<double> randomizer;
  return randomizer.sampleExponential(mRate);
}

double ExponentialDistribution::getMean() const {
  return 1.0 / mRate;
}

double ExponentialDistribution::getMedian() const {
  return getMean() * log(2);
}

double ExponentialDistribution::getMode() const {
  return 0;
}

double ExponentialDistribution::getVariance() const {
  return 1.0 / (mRate * mRate);
}

double ExponentialDistribution::KLDivergence(const ExponentialDistribution&
  other) const {
  return log(mRate) - log(other.mRate) + other.mRate / mRate - 1.0;
}
