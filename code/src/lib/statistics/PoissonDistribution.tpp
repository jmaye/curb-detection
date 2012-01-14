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

#include "functions/LogFactorialFunction.h"
#include "functions/FactorialFunction.h"
#include "statistics/Randomizer.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

PoissonDistribution::PoissonDistribution(double mean) {
  setMean(mean);
}

PoissonDistribution::PoissonDistribution(const PoissonDistribution& other) : 
  mMean(other.mMean) {
}

PoissonDistribution& PoissonDistribution::operator = (const
  PoissonDistribution& other) {
  if (this != &other) {
    mMean = other.mMean;
  }
  return *this;
}

PoissonDistribution::~PoissonDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void PoissonDistribution::read(std::istream& stream) {
}

void PoissonDistribution::write(std::ostream& stream) const {
  stream << "mean: " << mMean;
}

void PoissonDistribution::read(std::ifstream& stream) {
}

void PoissonDistribution::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void PoissonDistribution::setMean(double mean)
  throw (BadArgumentException<double>) {
  if (mean <= 0)
    throw BadArgumentException<double>(mean,
      "PoissonDistribution::setMean(): mean must be strictly positive",
      __FILE__, __LINE__);
  mMean = mean;
}

double PoissonDistribution::getMean() const {
  return mMean;
}

double PoissonDistribution::pmf(const size_t& value) const {
  return exp(logpmf(value));
}

double PoissonDistribution::logpmf(const size_t& value) const {
  const LogFactorialFunction lfactorial;
  return value * log(mMean) - mMean - lfactorial(value);
}

double PoissonDistribution::cdf(const size_t& value) const {
  const FactorialFunction factorial;
  double sum = 0.0;
  for (size_t i = 0; i <= value; ++i)
    sum += pow(mMean, i) / factorial(i);
  return exp(-mMean) * sum;
}

size_t PoissonDistribution::getSample() const {
  const static Randomizer<double> randomizer;
  return randomizer.samplePoisson(mMean);
}

double PoissonDistribution::getMedian() const {
  return floor(mMean + 1.0/ 3.0 - 0.02 / mMean);
}

double PoissonDistribution::getMode() const {
  return ceil(mMean) - 1.0;
}

double PoissonDistribution::getVariance() const {
  return mMean;
}

double PoissonDistribution::KLDivergence(const PoissonDistribution& other)
  const {
  return mMean - other.mMean + other.mMean * log(other.mMean / mMean);
}
