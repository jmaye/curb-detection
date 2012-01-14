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

EstimatorBayes<NormalDistribution<1> >::EstimatorBayes(double mu, double kappa,
  double nu, double sigma) :
  mPostMeanDist(nu, mu, sigma / kappa / nu),
  mPostVarianceDist(nu, sigma / nu),
  mPostPredDist(nu, mu, sigma * (kappa + 1) / kappa / nu),
  mMu(mu),
  mKappa(kappa),
  mNu(nu),
  mSigma(sigma) {
}

EstimatorBayes<NormalDistribution<1> >::EstimatorBayes(const
  EstimatorBayes<NormalDistribution<1> >& other) :
  mPostMeanDist(other.mPostMeanDist),
  mPostVarianceDist(other.mPostVarianceDist),
  mPostPredDist(other.mPostPredDist),
  mMu(other.mMu),
  mKappa(other.mKappa),
  mNu(other.mNu),
  mSigma(other.mSigma) {
}

EstimatorBayes<NormalDistribution<1> >&
  EstimatorBayes<NormalDistribution<1> >::operator =
  (const EstimatorBayes<NormalDistribution<1> >& other) {
  if (this != &other) {
    mPostMeanDist = other.mPostMeanDist;
    mPostVarianceDist = other.mPostVarianceDist;
    mPostPredDist = other.mPostPredDist;
    mMu = other.mMu;
    mKappa = other.mKappa;
    mNu = other.mNu;
    mSigma = other.mSigma;
  }
  return *this;
}

EstimatorBayes<NormalDistribution<1> >::~EstimatorBayes() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

void EstimatorBayes<NormalDistribution<1> >::read(std::istream& stream) {
}

void EstimatorBayes<NormalDistribution<1> >::write(std::ostream& stream) const {
  stream << "posterior mean distribution: " << std::endl << mPostMeanDist
    << std::endl << "posterior variance distribution: " << std::endl
    << mPostVarianceDist
    << std::endl << "posterior predictive distribution: " << std::endl
    << mPostPredDist;
}

void EstimatorBayes<NormalDistribution<1> >::read(std::ifstream& stream) {
}

void EstimatorBayes<NormalDistribution<1> >::write(std::ofstream& stream)
  const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

const StudentDistribution<1>& EstimatorBayes<NormalDistribution<1> >::
getPostMeanDist() const {
  return mPostMeanDist;
}

const ScaledInvChiSquareDistribution&
EstimatorBayes<NormalDistribution<1> >::getPostVarianceDist() const {
  return mPostVarianceDist;
}

const StudentDistribution<1>& EstimatorBayes<NormalDistribution<1> >::
getPostPredDist() const {
  return mPostPredDist;
}

void EstimatorBayes<NormalDistribution<1> >::addPoint(const Point& point) {
  const double newMu = (mKappa * mMu + point) / (mKappa + 1);
  const double newKappa = mKappa + 1;
  const double newNu = mNu + 1;
  const double newSigma = mSigma + (mKappa / (mKappa + 1)) * (point - mMu) *
    (point - mMu);
  mMu = newMu;
  mKappa = newKappa;
  mNu = newNu;
  mSigma = newSigma;
  mPostMeanDist.setDegrees(mNu);
  mPostMeanDist.setLocation(mMu);
  mPostMeanDist.setScale(mSigma / mKappa / mNu);
  mPostVarianceDist.setDegrees(mNu);
  mPostVarianceDist.setScale(mSigma / mNu);
  mPostPredDist.setDegrees(mNu);
  mPostPredDist.setLocation(mMu);
  mPostPredDist.setScale(mSigma * (mKappa + 1) / mKappa / mNu);
}

void EstimatorBayes<NormalDistribution<1> >::addPoints(const ConstPointIterator&
  itStart, const ConstPointIterator& itEnd) {
  for (ConstPointIterator it = itStart; it != itEnd; ++it)
    addPoint(*it);
}
