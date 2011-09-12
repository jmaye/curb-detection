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

EstimatorML<NormalDistribution<1> >::EstimatorML() :
  mMean(0),
  mVariance(0),
  mNumPoints(0),
  mValid(false) {
}

EstimatorML<NormalDistribution<1> >::EstimatorML(const
  EstimatorML<NormalDistribution<1> >& other) :
  mMean(other.mMean),
  mVariance(other.mVariance),
  mNumPoints(other.mNumPoints),
  mValid(other.mValid) {
}

EstimatorML<NormalDistribution<1> >&
  EstimatorML<NormalDistribution<1> >::operator =
  (const EstimatorML<NormalDistribution<1> >& other) {
  if (this != &other) {
    mMean = other.mMean;
    mVariance = other.mVariance;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
  }
  return *this;
}

EstimatorML<NormalDistribution<1> >::~EstimatorML() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

void EstimatorML<NormalDistribution<1> >::read(std::istream& stream) {
}

void EstimatorML<NormalDistribution<1> >::write(std::ostream& stream)
  const {
  stream << "mean: " << mMean << std::endl
    << "variance: " << mVariance << std::endl
    << "valid: " << mValid;
}

void EstimatorML<NormalDistribution<1> >::read(std::ifstream& stream) {
}

void EstimatorML<NormalDistribution<1> >::write(std::ofstream& stream)
  const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

size_t EstimatorML<NormalDistribution<1> >::getNumPoints() const {
  return mNumPoints;
}

bool EstimatorML<NormalDistribution<1> >::getValid() const {
  return mValid;
}

double EstimatorML<NormalDistribution<1> >::getMean() const {
  return mMean;
}

double EstimatorML<NormalDistribution<1> >::getVariance() const {
  return mVariance;
}

void EstimatorML<NormalDistribution<1> >::reset() {
  mNumPoints = 0;
  mValid = false;
  mMean = 0;
  mVariance = 0;
}

void EstimatorML<NormalDistribution<1> >::addPoint(double point) {
  mNumPoints++;
  mMean += 1.0 / mNumPoints * (point - mMean);
  mVariance += 1.0 / mNumPoints * ((point - mMean) * (point - mMean) -
    mVariance);
  if (mVariance != 0.0)
    mValid = true;
  else
    mValid = false;
}

void EstimatorML<NormalDistribution<1> >::addPoints(const std::vector<double>&
  points) {
  for (std::vector<double>::const_iterator it = points.begin();
    it != points.end(); ++it)
    addPoint(*it);
}
