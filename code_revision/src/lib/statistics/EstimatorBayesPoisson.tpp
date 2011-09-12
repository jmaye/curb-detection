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

EstimatorBayes<PoissonDistribution>::EstimatorBayes(double alpha, double beta) :
  mPostMeanDist(alpha, beta),
  mPostPredDist(alpha, 1.0 / (beta + 1)),
  mAlpha(alpha),
  mBeta(beta) {
}

EstimatorBayes<PoissonDistribution>::EstimatorBayes(const
  EstimatorBayes<PoissonDistribution>& other) :
  mPostMeanDist(other.mPostMeanDist),
  mPostPredDist(other.mPostPredDist),
  mAlpha(other.mAlpha),
  mBeta(other.mBeta) {
}

EstimatorBayes<PoissonDistribution>&
  EstimatorBayes<PoissonDistribution>::operator =
  (const EstimatorBayes<PoissonDistribution>& other) {
  if (this != &other) {
    mPostMeanDist = other.mPostMeanDist;
    mPostPredDist = other.mPostPredDist;
    mAlpha = other.mAlpha;
    mBeta = other.mBeta;
  }
  return *this;
}

EstimatorBayes<PoissonDistribution>::~EstimatorBayes() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

void EstimatorBayes<PoissonDistribution>::read(std::istream& stream) {
}

void EstimatorBayes<PoissonDistribution>::write(std::ostream& stream) const {
  stream << "posterior mean distribution: " << std::endl << mPostMeanDist
    << std::endl << "posterior predictive distribution: " << std::endl
    << mPostPredDist;
}

void EstimatorBayes<PoissonDistribution>::read(std::ifstream& stream) {
}

void EstimatorBayes<PoissonDistribution>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

const GammaDistribution<double>& EstimatorBayes<PoissonDistribution>::
getPostMeanDist() const {
  return mPostMeanDist;
}

const NegativeBinomialDistribution& EstimatorBayes<PoissonDistribution>::
getPostPredDist() const {
  return mPostPredDist;
}

void EstimatorBayes<PoissonDistribution>::addPoint(const Point& point) {
  mAlpha += point;
  mBeta += 1;
  mPostMeanDist.setShape(mAlpha);
  mPostMeanDist.setInvScale(mBeta);
  mPostPredDist.setSuccessProbability(1.0 / (mBeta + 1));
  mPostPredDist.setNumTrials(mAlpha);
}

void EstimatorBayes<PoissonDistribution>::addPoints(const ConstPointIterator&
  itStart, const ConstPointIterator& itEnd) {
  for (ConstPointIterator it = itStart; it != itEnd; ++it)
    addPoint(*it);
}
