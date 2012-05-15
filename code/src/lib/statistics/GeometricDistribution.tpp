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
#include "exceptions/BadArgumentException.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

GeometricDistribution::GeometricDistribution(double probability) {
  setProbability(probability);
}

GeometricDistribution::GeometricDistribution(const
    GeometricDistribution& other) :
    mProbability(other.mProbability) {
}

GeometricDistribution& GeometricDistribution::operator =
    (const GeometricDistribution& other) {
  if (this != &other) {
    mProbability = other.mProbability;
  }
  return *this;
}

GeometricDistribution::~GeometricDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void GeometricDistribution::read(std::istream& stream) {
}

void GeometricDistribution::write(std::ostream& stream) const {
  stream << "success probability: " << mProbability;
}

void GeometricDistribution::read(std::ifstream& stream) {
}

void GeometricDistribution::write(std::ofstream& stream) const {
}


/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void GeometricDistribution::setProbability(double probability) {
  if (probability <= 0.0 || probability > 1.0)
    throw BadArgumentException<double>(probability,
      "GeometricDistribution::setProbability(): success probability "
      "must be between 0 and 1",
      __FILE__, __LINE__);
  mProbability = probability;
}

double GeometricDistribution::getProbability() const {
  return mProbability;
}

double GeometricDistribution::pmf(const RandomVariable& value) const {
  if (value < 0)
    return 0.0;
  else
    return exp(logpmf(value));
}

double GeometricDistribution::logpmf(const RandomVariable& value) const {
  if (value < 0)
    throw BadArgumentException<RandomVariable>(value,
      "GeometricDistribution::logpmf(): value must be bigger than 0",
      __FILE__, __LINE__);
  else
    return value * log(1 - mProbability) + log(mProbability);
}

double GeometricDistribution::cdf(const RandomVariable& value) const {
  if (value < 0)
    return 0.0;
  else
    return 1 - pow(1 - mProbability, value + 1);
}

GeometricDistribution::RandomVariable GeometricDistribution::getSample() const {
  const static Randomizer<double> randomizer;
  return randomizer.sampleGeometric(mProbability);
}

GeometricDistribution::Mean GeometricDistribution::getMean() const {
  return (1.0 - mProbability) / mProbability;
}

GeometricDistribution::Mode GeometricDistribution::getMode() const {
  return 0;
}

GeometricDistribution::Variance GeometricDistribution::getVariance() const {
  return (1.0 - mProbability) / (mProbability *
    mProbability);
}
