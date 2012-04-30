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

ScaledInvChiSquareDistribution::ScaledInvChiSquareDistribution(double degrees,
    double scale) :
    InvGammaDistribution<>(0.5 * degrees, 0.5 * degrees * scale) {
}

ScaledInvChiSquareDistribution::ScaledInvChiSquareDistribution(const
    ScaledInvChiSquareDistribution& other) :
    InvGammaDistribution<>(other) {
}

ScaledInvChiSquareDistribution& ScaledInvChiSquareDistribution::operator =
    (const ScaledInvChiSquareDistribution& other) {
  if (this != &other) {
    InvGammaDistribution<>::operator=(other);
  }
  return *this;
}

ScaledInvChiSquareDistribution::~ScaledInvChiSquareDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void ScaledInvChiSquareDistribution::read(std::istream& stream) {
}

void ScaledInvChiSquareDistribution::write(std::ostream& stream) const {
  stream << "scale: " << getScale() << std::endl
    << "degrees: " << getDegrees();
}

void ScaledInvChiSquareDistribution::read(std::ifstream& stream) {
}

void ScaledInvChiSquareDistribution::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void ScaledInvChiSquareDistribution::setScale(double scale) {
  InvGammaDistribution<>::setScale(0.5 * getDegrees() * scale);
}

double ScaledInvChiSquareDistribution::getScale() const {
  return InvGammaDistribution<>::getScale() * 2.0 / (double)getDegrees();
}

void ScaledInvChiSquareDistribution::setDegrees(double degrees) {
  InvGammaDistribution<>::setScale(0.5 * degrees * getScale());
  setShape(degrees * 0.5);
}

double ScaledInvChiSquareDistribution::getDegrees() const {
  return getShape() * 2;
}
