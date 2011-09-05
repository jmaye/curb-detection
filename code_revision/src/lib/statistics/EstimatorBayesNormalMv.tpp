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
EstimatorBayes<NormalDistribution<M>, M>::EstimatorBayes(const
  Eigen::Matrix<double, M, 1>& mu, double kappa, double nu, const
  Eigen::Matrix<double, M, M>& sigma) :
  mPostMeanDist(nu - mu.size() + 1, mu, sigma / kappa / (nu - mu.size() + 1)),
  mPostCovarianceDist(nu, sigma / nu),
  mPostPredDist(nu - mu.size() + 1, mu, sigma * (kappa + 1) / kappa /
    (nu - mu.size() + 1)),
  mMu(mu),
  mKappa(kappa),
  mNu(nu),
  mSigma(sigma){
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, M>::EstimatorBayes(const
  EstimatorBayes<NormalDistribution<M>, M>& other) :
  mPostMeanDist(other.mPostMeanDist),
  mPostCovarianceDist(other.mPostCovarianceDist),
  mPostPredDist(other.mPostPredDist),
  mMu(other.mMu),
  mKappa(other.mKappa),
  mNu(other.mNu),
  mSigma(other.mSigma) {
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, M>&
  EstimatorBayes<NormalDistribution<M>, M>::operator =
  (const EstimatorBayes<NormalDistribution<M>, M>& other) {
  if (this != &other) {
    mPostMeanDist = other.mPostMeanDist;
    mPostCovarianceDist = other.mPostCovarianceDist;
    mPostPredDist = other.mPostPredDist;
    mMu = other.mMu;
    mKappa = other.mKappa;
    mNu = other.mNu;
    mSigma = other.mSigma;
  }
  return *this;
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, M>::~EstimatorBayes() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, M>::read(std::istream& stream) {
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, M>::write(std::ostream& stream) 
const {
  stream << "posterior mean distribution: " << std::endl << mPostMeanDist
    << std::endl << "posterior covariance distribution: " << std::endl
    << mPostCovarianceDist
    << std::endl << "posterior predictive distribution: " << std::endl
    << mPostPredDist;
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, M>::read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, M>::write(std::ofstream& stream)
  const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
const StudentDistribution<M>& EstimatorBayes<NormalDistribution<M>, M>::
getPostMeanDist() const {
  return mPostMeanDist;
}

template <size_t M>
const InvWishartDistribution<M>&
EstimatorBayes<NormalDistribution<M>, M>::getPostCovarianceDist() const {
  return mPostCovarianceDist;
}

template <size_t M>
const StudentDistribution<M>& EstimatorBayes<NormalDistribution<M>, M>::
getPostPredDist() const {
  return mPostPredDist;
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, M>::addPoint(const
  Eigen::Matrix<double, M, 1>& point) {
  Eigen::Matrix<double, M, 1> newMu = (mKappa * mMu + point) / (mKappa + 1);
  double newKappa = mKappa + 1;
  double newNu = mNu + 1;
  Eigen::Matrix<double, M, M> newSigma = mSigma + (mKappa / (mKappa + 1)) *
    (point - mMu) * (point - mMu).transpose();
  mMu = newMu;
  mKappa = newKappa;
  mNu = newNu;
  mSigma = newSigma;
  for (size_t i = 0; i < (size_t)mMu.size(); ++i)
    for (size_t j = i + 1; j < (size_t)mMu.size(); ++j)
      mSigma(i, j) = mSigma(j, i);
  mPostMeanDist.setDegrees(mNu - mMu.size() + 1);
  mPostMeanDist.setLocation(mMu);
  mPostMeanDist.setScale(mSigma / mKappa / (mNu - mMu.size() + 1));
  mPostCovarianceDist.setDegrees(mNu);
  mPostCovarianceDist.setScale(mSigma / mNu);
  mPostPredDist.setDegrees(mNu - mMu.size() + 1);
  mPostPredDist.setLocation(mMu);
  mPostPredDist.setScale(mSigma * (mKappa + 1) / mKappa /
    (mNu - mMu.size() + 1));
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, M>::addPoints(const
  std::vector<Eigen::Matrix<double, M, 1> >& points) {
  for (size_t i = 0; i < points.size(); ++i)
    addPoint(points[i]);
}
