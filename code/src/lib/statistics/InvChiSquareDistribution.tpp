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

InvChiSquareDistribution::InvChiSquareDistribution(double degrees) :
    InvGammaDistribution<>(0.5 * degrees, 0.5) {
}

InvChiSquareDistribution::InvChiSquareDistribution(const
    InvChiSquareDistribution& other) :
    InvGammaDistribution<>(other) {
}

InvChiSquareDistribution& InvChiSquareDistribution::operator =
    (const InvChiSquareDistribution& other) {
  if (this != &other) {
    InvGammaDistribution<>::operator=(other);
  }
  return *this;
}

InvChiSquareDistribution::~InvChiSquareDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void InvChiSquareDistribution::read(std::istream& stream) {
}

void InvChiSquareDistribution::write(std::ostream& stream) const {
  stream << "degrees: " << getDegrees();
}

void InvChiSquareDistribution::read(std::ifstream& stream) {
}

void InvChiSquareDistribution::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void InvChiSquareDistribution::setDegrees(double degrees) {
  setShape(degrees * 0.5);
}

double InvChiSquareDistribution::getDegrees() const {
  return getShape() * 2;
}
