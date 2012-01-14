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

#include <Eigen/Array>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
EstimatorBayes<MultinomialDistribution<M>, M>::EstimatorBayes(size_t numTrials,
  const Eigen::Matrix<double, M, 1>& alpha) :
  mNumTrials(numTrials),
  mPostSuccessDist(alpha),
  mPostPredDist(numTrials, alpha),
  mAlpha(alpha) {
}

template <size_t M>
EstimatorBayes<MultinomialDistribution<M>, M>::EstimatorBayes(const
  EstimatorBayes<MultinomialDistribution<M>, M>& other) :
  mNumTrials(other.mNumTrials),
  mPostSuccessDist(other.mPostSuccessDist),
  mPostPredDist(other.mPostPredDist),
  mAlpha(other.mAlpha) {
}

template <size_t M>
EstimatorBayes<MultinomialDistribution<M>, M>&
  EstimatorBayes<MultinomialDistribution<M>, M>::operator =
  (const EstimatorBayes<MultinomialDistribution<M>, M>& other) {
  if (this != &other) {
    mNumTrials = other.mNumTrials;
    mPostSuccessDist = other.mPostSuccessDist;
    mPostPredDist = other.mPostPredDist;
    mAlpha = other.mAlpha;
  }
  return *this;
}

template <size_t M>
EstimatorBayes<MultinomialDistribution<M>, M>::~EstimatorBayes() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorBayes<MultinomialDistribution<M>, M>::read(std::istream& stream) {
}

template <size_t M>
void EstimatorBayes<MultinomialDistribution<M>, M>::write(std::ostream& stream) 
const {
  stream << "trials number: " << mNumTrials << std::endl
    << "posterior success probablities distribution: " << std::endl
    << mPostSuccessDist << std::endl
    << "posterior predictive distribution: " << std::endl << mPostPredDist;
}

template <size_t M>
void EstimatorBayes<MultinomialDistribution<M>, M>::read(std::ifstream&
  stream) {
}

template <size_t M>
void EstimatorBayes<MultinomialDistribution<M>, M>::write(std::ofstream& stream)
  const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
size_t EstimatorBayes<MultinomialDistribution<M>, M>::getNumTrials() const {
  return mNumTrials;
}

template <size_t M>
const DirichletDistribution<M>& EstimatorBayes<MultinomialDistribution<M>, M>::
getPostSuccessDist() const {
  return mPostSuccessDist;
}

template <size_t M>
const DCMDistribution<M>& EstimatorBayes<MultinomialDistribution<M>, M>::
getPostPredDist() const {
  return mPostPredDist;
}

template <size_t M>
void EstimatorBayes<MultinomialDistribution<M>, M>::addPoint(const Point&
  point) {
  for (size_t i = 0; i < (size_t)mAlpha.size(); ++i)
    mAlpha(i) += point(i);
  mPostSuccessDist.setAlpha(mAlpha);
  mPostPredDist.setAlpha(mAlpha);
}

template <size_t M>
void EstimatorBayes<MultinomialDistribution<M>, M>::addPoints(const
  ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  for (ConstPointIterator it = itStart; it != itEnd; ++it)
    addPoint(*it);
}
