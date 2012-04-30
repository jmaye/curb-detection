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

template <size_t M>
EstimatorML<MultinomialDistribution<M> >::EstimatorML() :
    mNumPoints(0),
    mValid(false) {
}

template <size_t M>
EstimatorML<MultinomialDistribution<M> >::EstimatorML(const EstimatorML&
    other) :
    mDistribution(other.mDistribution),
    mNumPoints(other.mNumPoints),
    mValid(other.mValid) {
}

template <size_t M>
EstimatorML<MultinomialDistribution<M> >&
    EstimatorML<MultinomialDistribution<M> >::operator = (const EstimatorML&
    other) {
  if (this != &other) {
    mDistribution = other.mDistribution;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
  }
  return *this;
}

template <size_t M>
EstimatorML<MultinomialDistribution<M> >::~EstimatorML() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorML<MultinomialDistribution<M> >::read(std::istream& stream) {
}

template <size_t M>
void EstimatorML<MultinomialDistribution<M> >::write(std::ostream& stream)
    const {
  stream << "distribution: " << std::endl << mDistribution << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

template <size_t M>
void EstimatorML<MultinomialDistribution<M> >::read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorML<MultinomialDistribution<M> >::write(std::ofstream& stream)
    const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
size_t EstimatorML<MultinomialDistribution<M> >::getNumPoints() const {
  return mNumPoints;
}

template <size_t M>
bool EstimatorML<MultinomialDistribution<M> >::getValid() const {
  return mValid;
}

template <size_t M>
const MultinomialDistribution<M>&
    EstimatorML<MultinomialDistribution<M> >::getDistribution() const {
  return mDistribution;
}

template <size_t M>
void EstimatorML<MultinomialDistribution<M> >::reset() {
  mNumPoints = 0;
  mValid = false;
}

template <size_t M>
void EstimatorML<MultinomialDistribution<M> >::addPoint(const Point& point) {
  const size_t numTrials = point.sum();
  mNumPoints++;
  try {
    mDistribution.setNumTrials(numTrials);
    mValid = true;
    if (mNumPoints == 1)
      mDistribution.setProbabilities(point.template cast<double>() / numTrials);
    else
      mDistribution.setProbabilities(mDistribution.getProbabilities() +
        (point.template cast<double>() /
        numTrials - mDistribution.getProbabilities()) / mNumPoints);
  }
  catch (...) {
    mValid = false;
  }
}

template <size_t M>
void EstimatorML<MultinomialDistribution<M> >::addPoints(const
    ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  for (auto it = itStart; it != itEnd; ++it)
    addPoint(*it);
}

template <size_t M>
void EstimatorML<MultinomialDistribution<M> >::addPoints(const Container&
    points) {
  addPoints(points.begin(), points.end());
}
