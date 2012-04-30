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

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ExponentialDistribution::ExponentialDistribution(double rate) :
    GammaDistribution<size_t>(1, rate) {
}

ExponentialDistribution::ExponentialDistribution(const
    ExponentialDistribution& other) :
    GammaDistribution<size_t>(other) {
}

ExponentialDistribution& ExponentialDistribution::operator =
    (const ExponentialDistribution& other) {
  if (this != &other) {
    GammaDistribution<size_t>::operator=(other);
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
  stream << "rate: " << getInvScale();
}

void ExponentialDistribution::read(std::ifstream& stream) {
}

void ExponentialDistribution::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void ExponentialDistribution::setRate(double rate) {
  setInvScale(rate);
}

double ExponentialDistribution::getRate() const {
  return getInvScale();
}

ExponentialDistribution::Median ExponentialDistribution::getMedian() const {
  return getMean() * log(2);
}
