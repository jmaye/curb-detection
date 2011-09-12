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

EstimatorML<ExponentialDistribution>::EstimatorML() :
  mRate(0.0),
  mMean(0.0),
  mNumPoints(0),
  mValid(false) {
}

EstimatorML<ExponentialDistribution>::EstimatorML(const
  EstimatorML<ExponentialDistribution>& other) :
  mRate(other.mRate),
  mMean(other.mMean),
  mNumPoints(other.mNumPoints),
  mValid(other.mValid) {
}

EstimatorML<ExponentialDistribution>&
  EstimatorML<ExponentialDistribution>::operator =
  (const EstimatorML<ExponentialDistribution>& other) {
  if (this != &other) {
    mRate = other.mRate;
    mMean = other.mMean;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
  }
  return *this;
}

EstimatorML<ExponentialDistribution>::~EstimatorML() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

void EstimatorML<ExponentialDistribution>::read(std::istream& stream) {
}

void EstimatorML<ExponentialDistribution>::write(std::ostream& stream)
  const {
  stream << "rate: " << mRate << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

void EstimatorML<ExponentialDistribution>::read(std::ifstream& stream) {
}

void EstimatorML<ExponentialDistribution>::write(std::ofstream& stream)
  const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

size_t EstimatorML<ExponentialDistribution>::getNumPoints() const {
  return mNumPoints;
}

bool EstimatorML<ExponentialDistribution>::getValid() const {
  return mValid;
}

double EstimatorML<ExponentialDistribution>::getRate() const {
  return mRate;
}

void EstimatorML<ExponentialDistribution>::reset() {
  mNumPoints = 0;
  mValid = false;
  mRate = 0;
  mMean = 0;
}

void EstimatorML<ExponentialDistribution>::addPoint(const Point& point) {
  mNumPoints++;
  if (mNumPoints == 1)
    mMean = point;
  else
    mMean += 1.0 / mNumPoints * (point - mMean);
  if (mMean != 0) {
    mRate = 1.0 / mMean;
    mValid = true;
  }
  else
    mValid = false;
}

void EstimatorML<ExponentialDistribution>::addPoints(const
  ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  for (ConstPointIterator it = itStart; it != itEnd; ++it)
    addPoint(*it);
}
