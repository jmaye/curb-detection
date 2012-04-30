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

CauchyDistribution::CauchyDistribution(double location, double scale) :
    mLocation(location) {
  setScale(scale);
}

CauchyDistribution::CauchyDistribution(const CauchyDistribution& other) :
    mLocation(other.mLocation),
    mScale(other.mScale) {
}

CauchyDistribution& CauchyDistribution::operator = (const CauchyDistribution&
    other) {
  if (this != &other) {
    mLocation = other.mLocation;
    mScale = other.mScale;
  }
  return *this;
}

CauchyDistribution::~CauchyDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void CauchyDistribution::read(std::istream& stream) {
}

void CauchyDistribution::write(std::ostream& stream) const {
  stream << "location: " << mLocation << std::endl << "scale: " << mScale;
}

void CauchyDistribution::read(std::ifstream& stream) {
}

void CauchyDistribution::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void CauchyDistribution::setLocation(double location) {
  mLocation = location;
}

double CauchyDistribution::getLocation() const {
  return mLocation;
}

void CauchyDistribution::setScale(double scale)
    throw (BadArgumentException<double>) {
  if (scale <= 0)
    throw BadArgumentException<double>(scale,
      "CauchyDistribution::setScale(): scale must be strictly positive",
      __FILE__, __LINE__);
  mScale = scale;
}

double CauchyDistribution::getScale() const {
  return mScale;
}

double CauchyDistribution::pdf(const RandomVariable& value) const {
  return exp(logpdf(value));
}

double CauchyDistribution::logpdf(const RandomVariable& value) const {
  return -(log(M_PI) + log(mScale) + log(1 + ((value - mLocation) / mScale) *
    ((value - mLocation) / mScale)));
}

double CauchyDistribution::cdf(const RandomVariable& value) const {
  return atan((value - mLocation) / mScale) / M_PI + 0.5;
}

CauchyDistribution::RandomVariable CauchyDistribution::getSample() const {
  const static Randomizer<double> randomizer;
  return mLocation + mScale * tan(M_PI * (randomizer.sampleUniform() - 0.5));
}

CauchyDistribution::Mean CauchyDistribution::getMean() const
    throw (InvalidOperationException) {
  throw InvalidOperationException("CauchyDistribution::getMean(): "
    "mean undefined");
}

CauchyDistribution::Median CauchyDistribution::getMedian() const {
  return mLocation;
}

CauchyDistribution::Mode CauchyDistribution::getMode() const {
  return mLocation;
}

CauchyDistribution::Variance CauchyDistribution::getVariance() const
    throw (InvalidOperationException) {
  throw InvalidOperationException("CauchyDistribution::getVariance(): "
    "variance undefined");
}
