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

EstimatorML<PoissonDistribution>::EstimatorML() :
    mNumPoints(0),
    mValid(false) {
}

EstimatorML<PoissonDistribution>::EstimatorML(const EstimatorML& other) :
    mDistribution(other.mDistribution),
    mNumPoints(other.mNumPoints),
    mValid(other.mValid) {
}

EstimatorML<PoissonDistribution>&
    EstimatorML<PoissonDistribution>::operator = (const EstimatorML& other) {
  if (this != &other) {
    mDistribution = other.mDistribution;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
  }
  return *this;
}

EstimatorML<PoissonDistribution>::~EstimatorML() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

void EstimatorML<PoissonDistribution>::read(std::istream& stream) {
}

void EstimatorML<PoissonDistribution>::write(std::ostream& stream) const {
  stream << "distribution: " << std::endl << mDistribution << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

void EstimatorML<PoissonDistribution>::read(std::ifstream& stream) {
}

void EstimatorML<PoissonDistribution>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

size_t EstimatorML<PoissonDistribution>::getNumPoints() const {
  return mNumPoints;
}

bool EstimatorML<PoissonDistribution>::getValid() const {
  return mValid;
}

const PoissonDistribution&
    EstimatorML<PoissonDistribution>::getDistribution() const {
  return mDistribution;
}

void EstimatorML<PoissonDistribution>::reset() {
  mNumPoints = 0;
  mValid = false;
}

void EstimatorML<PoissonDistribution>::addPoint(const Point& point) {
  mNumPoints++;
  try {
    mValid = true;
    double mean;
    if (mNumPoints == 1)
      mean = point;
    else
      mean = mDistribution.getMean();
    mean += (point - mean) / mNumPoints;
    mDistribution.setMean(mean);
  }
  catch (...) {
    mValid = false;
  }
}

void EstimatorML<PoissonDistribution>::addPoints(const
    ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  for (auto it = itStart; it != itEnd; ++it)
    addPoint(*it);
}

void EstimatorML<PoissonDistribution>::addPoints(const Container& points) {
  addPoints(points.begin(), points.end());
}
