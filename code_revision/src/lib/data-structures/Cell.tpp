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

Cell::Cell() {
}

Cell::Cell(const Cell& other) :
  mHeightEstimator(other.mHeightEstimator) {
}

Cell& Cell::operator = (const Cell& other) {
  if (this != &other) {
    mHeightEstimator = other.mHeightEstimator;
  }
  return *this;
}

Cell::~Cell() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Cell::read(std::istream& stream) {
}

void Cell::write(std::ostream& stream) const {
  stream << "height estimator: " << std::endl;
}

void Cell::read(std::ifstream& stream) {
}

void Cell::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void Cell::addPoint(double point) {
  mHeightEstimator.addPoint(point);
}

const EstimatorBayesImproper<NormalDistribution<1> >& Cell::getHeightEstimator()
  const {
  return mHeightEstimator;
}
