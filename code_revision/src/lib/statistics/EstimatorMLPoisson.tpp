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
  mMean(0.0),
  mNumPoints(0),
  mValid(false) {
}

EstimatorML<PoissonDistribution>::EstimatorML(const
  EstimatorML<PoissonDistribution>& other) :
  mMean(other.mMean),
  mNumPoints(other.mNumPoints),
  mValid(other.mValid) {
}

EstimatorML<PoissonDistribution>&
  EstimatorML<PoissonDistribution>::operator =
  (const EstimatorML<PoissonDistribution>& other) {
  if (this != &other) {
    mMean = other.mMean;
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
  stream << "mean " << mMean << std::endl
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

double EstimatorML<PoissonDistribution>::getMean() const {
  return mMean;
}

void EstimatorML<PoissonDistribution>::reset() {
  mNumPoints = 0;
  mValid = false;
  mMean = 0;
}

void EstimatorML<PoissonDistribution>::addPoint(const Point& point) {
  mNumPoints++;
  if (mNumPoints == 1) {
    mMean = point;
    mValid = true;
  }
  else
    mMean += 1.0 / mNumPoints * (point - mMean);
}

void EstimatorML<PoissonDistribution>::addPoints(const
  ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  for (ConstPointIterator it = itStart; it != itEnd; ++it)
    addPoint(*it);
}
