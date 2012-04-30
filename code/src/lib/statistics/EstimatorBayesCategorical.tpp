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
EstimatorBayes<CategoricalDistribution<M>, DirichletDistribution<M> >::
    EstimatorBayes(const DirichletDistribution<M>& prior) :
    mProbDist(prior) {
}

template <size_t M>
EstimatorBayes<CategoricalDistribution<M>, DirichletDistribution<M> >::
    EstimatorBayes(const EstimatorBayes& other) :
    mProbDist(other.mProbDist) {
}

template <size_t M>
EstimatorBayes<CategoricalDistribution<M>, DirichletDistribution<M> >&
    EstimatorBayes<CategoricalDistribution<M>, DirichletDistribution<M> >::
    operator = (const EstimatorBayes& other) {
  if (this != &other) {
    mProbDist = other.mProbDist;
  }
  return *this;
}

template <size_t M>
EstimatorBayes<CategoricalDistribution<M>, DirichletDistribution<M> >::
    ~EstimatorBayes() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorBayes<CategoricalDistribution<M>, DirichletDistribution<M> >::
    read(std::istream& stream) {
}

template <size_t M>
void EstimatorBayes<CategoricalDistribution<M>, DirichletDistribution<M> >::
    write(std::ostream& stream) const {
  stream << "Probabilities distribution: " << std::endl << mProbDist
    << std::endl <<
    "Probabilities mode: " << std::endl << mProbDist.getMode() << std::endl <<
    "Predictive distribution: " << std::endl << getPredDist() << std::endl <<
    "Predictive mean: " << std::endl << getPredDist().getMean();
}

template <size_t M>
void EstimatorBayes<CategoricalDistribution<M>, DirichletDistribution<M> >::
    read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorBayes<CategoricalDistribution<M>, DirichletDistribution<M> >::
    write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
const DirichletDistribution<M>&
    EstimatorBayes<CategoricalDistribution<M>, DirichletDistribution<M> >::
    getDist() const {
  return mProbDist;
}

template <size_t M>
DCMDistribution<M>
    EstimatorBayes<CategoricalDistribution<M>, DirichletDistribution<M> >::
    getPredDist() const {
  return DCMDistribution<M>(1, mProbDist.getAlpha());
}

template <size_t M>
void EstimatorBayes<CategoricalDistribution<M>, DirichletDistribution<M> >::
    addPoint(const Point& point) {
  mProbDist.setAlpha(mProbDist.getAlpha() + point.template cast<double>());
}

template <size_t M>
void EstimatorBayes<CategoricalDistribution<M>, DirichletDistribution<M> >::
    addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd) {
  for (auto it = itStart; it != itEnd; ++it)
    addPoint(*it);
}

template <size_t M>
void EstimatorBayes<CategoricalDistribution<M>, DirichletDistribution<M> >::
    addPoints(const Container& points) {
  addPoints(points.begin(), points.end());
}
