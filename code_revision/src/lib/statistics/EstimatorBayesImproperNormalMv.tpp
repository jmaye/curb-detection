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

#include <Eigen/QR>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
EstimatorBayesImproper<NormalDistribution<M>, M>::EstimatorBayesImproper() :
  mNumPoints(0),
  mValid(false) {
}

template <size_t M>
EstimatorBayesImproper<NormalDistribution<M>, M>::EstimatorBayesImproper(const
  EstimatorBayesImproper<NormalDistribution<M>, M>& other) :
  mPostMeanDist(other.mPostMeanDist),
  mPostCovarianceDist(other.mPostCovarianceDist),
  mPostPredDist(other.mPostPredDist),
  mSampleMean(other.mSampleMean),
  mSampleCovariance(other.mSampleCovariance),
  mNumPoints(other.mNumPoints),
  mValid(other.mValid) {
}

template <size_t M>
EstimatorBayesImproper<NormalDistribution<M>, M>&
  EstimatorBayesImproper<NormalDistribution<M>, M>::operator =
  (const EstimatorBayesImproper<NormalDistribution<M>, M>& other) {
  if (this != &other) {
    mPostMeanDist = other.mPostMeanDist;
    mPostCovarianceDist = other.mPostCovarianceDist;
    mPostPredDist = other.mPostPredDist;
    mSampleMean = other.mSampleMean;
    mSampleCovariance = other.mSampleCovariance;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
  }
  return *this;
}

template <size_t M>
EstimatorBayesImproper<NormalDistribution<M>, M>::~EstimatorBayesImproper() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M>, M>::read(std::istream&
  stream) {
}

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M>, M>::write(std::ostream&
  stream) const {
  stream << "posterior mean distribution: " << std::endl << mPostMeanDist
    << std::endl << "posterior covariance distribution: " << std::endl
    << mPostCovarianceDist
    << std::endl << "posterior predictive distribution: " << std::endl
    << mPostPredDist << std::endl
    << "sample mean: " << mSampleMean.transpose() << std::endl
    << "sample covariance: " << std::endl << mSampleCovariance << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M>, M>::read(std::ifstream&
  stream) {
}

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M>, M>::write(std::ofstream&
  stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
const StudentDistribution<M>& EstimatorBayesImproper<NormalDistribution<M>, M>::
getPostMeanDist() const {
  return mPostMeanDist;
}

template <size_t M>
const InvWishartDistribution<M>&
EstimatorBayesImproper<NormalDistribution<M>, M>::getPostCovarianceDist()
  const {
  return mPostCovarianceDist;
}

template <size_t M>
const StudentDistribution<M>& EstimatorBayesImproper<NormalDistribution<M>, M>::
getPostPredDist() const {
  return mPostPredDist;
}

template <size_t M>
const Eigen::Matrix<double, M, 1>&
EstimatorBayesImproper<NormalDistribution<M>, M>::getSampleMean() const {
  return mSampleMean;
}

template <size_t M>
const Eigen::Matrix<double, M, M>&
EstimatorBayesImproper<NormalDistribution<M>, M>::getSampleCovariance() const {
  return mSampleCovariance;
}

template <size_t M>
size_t EstimatorBayesImproper<NormalDistribution<M>, M>::getNumPoints() const {
  return mNumPoints;
}

template <size_t M>
bool EstimatorBayesImproper<NormalDistribution<M>, M>::getValid() const {
  return mValid;
}

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M>, M>::reset() {
  mNumPoints = 0;
  mValid = false;
}

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M>, M>::addPoint(const
  Eigen::Matrix<double, M, 1>& point) {
  if (mNumPoints == 0) {
    mSampleMean = Eigen::Matrix<double, M, 1>::Zero(point.size());
    mSampleCovariance = Eigen::Matrix<double, M, M>::Zero(point.size(),
      point.size());
  }
  mNumPoints++;
  mSampleMean += 1.0 / mNumPoints * (point - mSampleMean);
  if (mNumPoints > 1)
    mSampleCovariance += 1.0 / (mNumPoints - 1) * ((point - mSampleMean) *
      (point - mSampleMean).transpose() - mSampleCovariance);
  Eigen::QR<Eigen::Matrix<double, M, M> > qrDecomp = mSampleCovariance.qr();
  if (qrDecomp.rank() == mSampleMean.size()) {
    mPostMeanDist.setDegrees(mNumPoints - mSampleMean.size());
    mPostMeanDist.setLocation(mSampleMean);
    mPostMeanDist.setScale(mSampleCovariance / mNumPoints);
    mPostCovarianceDist.setDegrees(mNumPoints - 1);
    mPostCovarianceDist.setScale(mSampleCovariance);
    mPostPredDist.setDegrees(mNumPoints - mSampleMean.size());
    mPostPredDist.setLocation(mSampleMean);
    mPostPredDist.setScale(mSampleCovariance * (1 + 1.0 / mNumPoints));
    mValid = true;
  }
  else
    mValid = false;
}

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M>, M>::addPoints(const
  std::vector<Eigen::Matrix<double, M, 1> >& points) {
  for (size_t i = 0; i < points.size(); ++i)
    addPoint(points[i]);
}
