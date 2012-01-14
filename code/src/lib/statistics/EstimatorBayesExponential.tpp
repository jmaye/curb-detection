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

EstimatorBayes<ExponentialDistribution>::EstimatorBayes(double alpha, double
  beta) :
  mPostRateDist(alpha, beta),
  mPostPredDist(alpha, 1.0 / (beta + 1)),
  mAlpha(alpha),
  mBeta(beta) {
}

EstimatorBayes<ExponentialDistribution>::EstimatorBayes(const
  EstimatorBayes<ExponentialDistribution>& other) :
  mPostRateDist(other.mPostRateDist),
  mPostPredDist(other.mPostPredDist),
  mAlpha(other.mAlpha),
  mBeta(other.mBeta) {
}

EstimatorBayes<ExponentialDistribution>&
  EstimatorBayes<ExponentialDistribution>::operator =
  (const EstimatorBayes<ExponentialDistribution>& other) {
  if (this != &other) {
    mPostRateDist = other.mPostRateDist;
    mPostPredDist = other.mPostPredDist;
    mAlpha = other.mAlpha;
    mBeta = other.mBeta;
  }
  return *this;
}

EstimatorBayes<ExponentialDistribution>::~EstimatorBayes() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

void EstimatorBayes<ExponentialDistribution>::read(std::istream& stream) {
}

void EstimatorBayes<ExponentialDistribution>::write(std::ostream& stream)
  const {
  stream << "posterior rate distribution: " << std::endl << mPostRateDist
    << std::endl << "posterior predictive distribution: " << std::endl
    << mPostPredDist;
}

void EstimatorBayes<ExponentialDistribution>::read(std::ifstream& stream) {
}

void EstimatorBayes<ExponentialDistribution>::write(std::ofstream& stream)
  const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

const GammaDistribution<double>& EstimatorBayes<ExponentialDistribution>::
getPostRateDist() const {
  return mPostRateDist;
}

const NegativeBinomialDistribution& EstimatorBayes<ExponentialDistribution>::
getPostPredDist() const {
  return mPostPredDist;
}

void EstimatorBayes<ExponentialDistribution>::addPoint(const Point& point) {
  mAlpha += 1;
  mBeta += point;
  mPostRateDist.setShape(mAlpha);
  mPostRateDist.setInvScale(mBeta);
  // TODO: POST PRED DIST CHECK
  mPostPredDist.setSuccessProbability(1.0 / (mBeta + 1));
  mPostPredDist.setNumTrials(mAlpha);
}

void EstimatorBayes<ExponentialDistribution>::addPoints(const
  ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  for (ConstPointIterator it = itStart; it != itEnd; ++it)
    addPoint(*it);
}
