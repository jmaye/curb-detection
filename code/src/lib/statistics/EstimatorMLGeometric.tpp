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

EstimatorML<GeometricDistribution>::EstimatorML() :
    mNumPoints(0),
    mValid(false) {
}

EstimatorML<GeometricDistribution>::EstimatorML(const EstimatorML& other) :
    mDistribution(other.mDistribution),
    mNumPoints(other.mNumPoints),
    mValid(other.mValid) {
}

EstimatorML<GeometricDistribution>&
    EstimatorML<GeometricDistribution>::operator = (const EstimatorML& other) {
  if (this != &other) {
    mDistribution = other.mDistribution;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
  }
  return *this;
}

EstimatorML<GeometricDistribution>::~EstimatorML() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

void EstimatorML<GeometricDistribution>::read(std::istream& stream) {
}

void EstimatorML<GeometricDistribution>::write(std::ostream& stream) const {
  stream << "distribution: " << std::endl << mDistribution << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

void EstimatorML<GeometricDistribution>::read(std::ifstream& stream) {
}

void EstimatorML<GeometricDistribution>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

size_t EstimatorML<GeometricDistribution>::getNumPoints() const {
  return mNumPoints;
}

bool EstimatorML<GeometricDistribution>::getValid() const {
  return mValid;
}

const GeometricDistribution&
    EstimatorML<GeometricDistribution>::getDistribution() const {
  return mDistribution;
}

void EstimatorML<GeometricDistribution>::reset() {
  mNumPoints = 0;
  mValid = false;
}

void EstimatorML<GeometricDistribution>::addPoint(const Point& point) {
  mNumPoints++;
  try {
    mValid = true;
    double mean;
    if (mNumPoints == 1)
      mean = point;
    else
      mean = mDistribution.getMean();
    mean += (point - mean) / mNumPoints;
    mDistribution.setProbability(1.0 / (1 + mean));
  }
  catch (...) {
    mValid = false;
  }
}

void EstimatorML<GeometricDistribution>::addPoints(const
    ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  for (auto it = itStart; it != itEnd; ++it)
    addPoint(*it);
}

void EstimatorML<GeometricDistribution>::addPoints(const Container& points) {
  addPoints(points.begin(), points.end());
}
