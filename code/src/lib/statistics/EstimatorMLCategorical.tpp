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
EstimatorML<CategoricalDistribution<M> >::EstimatorML() :
    mNumPoints(0),
    mValid(false) {
}

template <size_t M>
EstimatorML<CategoricalDistribution<M> >::EstimatorML(const EstimatorML&
    other) :
    mDistribution(other.mDistribution),
    mNumPoints(other.mNumPoints),
    mValid(other.mValid) {
}

template <size_t M>
EstimatorML<CategoricalDistribution<M> >&
    EstimatorML<CategoricalDistribution<M> >::operator = (const EstimatorML&
    other) {
  if (this != &other) {
    mDistribution = other.mDistribution;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
  }
  return *this;
}

template <size_t M>
EstimatorML<CategoricalDistribution<M> >::~EstimatorML() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorML<CategoricalDistribution<M> >::read(std::istream& stream) {
}

template <size_t M>
void EstimatorML<CategoricalDistribution<M> >::write(std::ostream& stream)
    const {
  stream << "distribution: " << std::endl << mDistribution << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

template <size_t M>
void EstimatorML<CategoricalDistribution<M> >::read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorML<CategoricalDistribution<M> >::write(std::ofstream& stream)
    const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
size_t EstimatorML<CategoricalDistribution<M> >::getNumPoints() const {
  return mNumPoints;
}

template <size_t M>
bool EstimatorML<CategoricalDistribution<M> >::getValid() const {
  return mValid;
}

template <size_t M>
const CategoricalDistribution<M>&
    EstimatorML<CategoricalDistribution<M> >::getDistribution() const {
  return mDistribution;
}

template <size_t M>
void EstimatorML<CategoricalDistribution<M> >::reset() {
  mNumPoints = 0;
  mValid = false;
}

template <size_t M>
void EstimatorML<CategoricalDistribution<M> >::addPoint(const Point& point) {
  mNumPoints++;
  try {
    mValid = true;
    if (mNumPoints == 1)
      mDistribution.setProbabilities(point.template cast<double>());
    else
      mDistribution.setProbabilities(mDistribution.getProbabilities() +
        (point.template cast<double>() - mDistribution.getProbabilities()) /
        mNumPoints);
  }
  catch (...) {
    mValid = false;
  }
}

template <size_t M>
void EstimatorML<CategoricalDistribution<M> >::addPoints(const
    ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  for (auto it = itStart; it != itEnd; ++it)
    addPoint(*it);
}

template <size_t M>
void EstimatorML<CategoricalDistribution<M> >::addPoints(const Container&
    points) {
  addPoints(points.begin(), points.end());
}
