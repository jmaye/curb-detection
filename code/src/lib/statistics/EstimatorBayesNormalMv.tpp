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

#include "utils/OuterProduct.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::
    EstimatorBayes(const Eigen::Matrix<double, M, M>& covariance, const
    NormalDistribution<M>& prior) :
    mMeanDist(prior),
    mCovariance(covariance),
    mPrecision(covariance.inverse()) {
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >::
    EstimatorBayes(const Eigen::Matrix<double, M, 1>& mean, const
    InvWishartDistribution<M>& prior) :
    mCovarianceDist(prior),
    mMean(mean) {
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >::
    EstimatorBayes(const NormalInvWishartDistribution<M>& prior) :
    mMeanCovarianceDist(prior) {
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::EstimatorBayes(
    const EstimatorBayes& other) :
    mMeanDist(other.mMeanDist),
    mCovariance(other.mCovariance),
    mPrecision(other.mPrecision) {
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >::
    EstimatorBayes(const EstimatorBayes& other) :
    mCovarianceDist(other.mCovarianceDist),
    mMean(other.mMean) {
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >::
    EstimatorBayes(const EstimatorBayes& other) :
    mMeanCovarianceDist(other.mMeanCovarianceDist) {
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >&
    EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::operator =
    (const EstimatorBayes& other) {
  if (this != &other) {
    mMeanDist = other.mMeanDist;
    mCovariance = other.mCovariance;
    mPrecision = other.mPrecision;
  }
  return *this;
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >&
    EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >::
    operator = (const EstimatorBayes& other) {
  if (this != &other) {
    mCovarianceDist = other.mCovarianceDist;
    mMean = other.mMean;
  }
  return *this;
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >&
    EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >
    ::operator = (const EstimatorBayes& other) {
  if (this != &other) {
    mMeanCovarianceDist = other.mMeanCovarianceDist;
  }
  return *this;
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::
    ~EstimatorBayes() {
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >::
    ~EstimatorBayes() {
}

template <size_t M>
EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >::
    ~EstimatorBayes() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::
    read(std::istream& stream) {
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >::
    read(std::istream& stream) {
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >::
    read(std::istream& stream) {
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::
    write(std::ostream& stream) const {
  stream << "Mean distribution: " << std::endl << mMeanDist << std::endl
    << "Mean mode: " << std::endl << mMeanDist.getMode() << std::endl
    << "Mean covariance: " << std::endl << mMeanDist.getCovariance()
    << std::endl
    << "Predictive distribution: " << std::endl << getPredDist() << std::endl
    << "Predictive mean: " << std::endl << getPredDist().getMean() << std::endl
    << "Predictive covariance: " << std::endl << getPredDist().getCovariance();
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >::
    write(std::ostream& stream) const {
  stream << "Covariance distribution: " << std::endl << mCovarianceDist
    << std::endl
    << "Covariance mode: " << std::endl << mCovarianceDist.getMode()
    << std::endl
    << "Covariance covariance: " << std::endl
    << mCovarianceDist.getCovariance();
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >::
    write(std::ostream& stream) const {
  stream << "Mean and covariance distribution: " << std::endl
    << mMeanCovarianceDist << std::endl
    << "Mean and covariance mode: " << std::endl
    << std::get<0>(mMeanCovarianceDist.getMode()) << std::endl
    << std::get<1>(mMeanCovarianceDist.getMode())
    << std::endl << "Predictive distribution: " << std::endl << getPredDist()
    << std::endl
    << "Predictive mean: " << std::endl << getPredDist().getMean() << std::endl
    << "Predictive covariance: " << std::endl << getPredDist().getCovariance();
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::
    read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >::
    read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >::
    read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::
    write(std::ofstream& stream) const {
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >::
    write(std::ofstream& stream) const {
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >::
    write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
const NormalDistribution<M>&
    EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::getDist()
    const {
  return mMeanDist;
}

template <size_t M>
const InvWishartDistribution<M>&
    EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >::getDist()
    const {
  return mCovarianceDist;
}

template <size_t M>
const NormalInvWishartDistribution<M>&
    EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >::
    getDist() const {
  return mMeanCovarianceDist;
}

template <size_t M>
NormalDistribution<M>
    EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::
    getPredDist() const {
  return NormalDistribution<M>(mMeanDist.getMean(), mMeanDist.getCovariance() +
    mCovariance);
}

template <size_t M>
StudentDistribution<M>
    EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >::
    getPredDist() const {
  const size_t dim = mMeanCovarianceDist.getMu().size();
  return StudentDistribution<M>(mMeanCovarianceDist.getNu() - dim + 1,
    mMeanCovarianceDist.getMu(), (mMeanCovarianceDist.getKappa() + 1) /
    mMeanCovarianceDist.getKappa() /
    (mMeanCovarianceDist.getNu() - dim + 1) *
    mMeanCovarianceDist.getSigma());
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::
    addPoint(const Point& point) {
  const Eigen::Matrix<double, M, 1> mean =
    (mMeanDist.getPrecision() + mPrecision).inverse() *
    (mMeanDist.getPrecision() * mMeanDist.getMean() + mPrecision * point);
  const Eigen::Matrix<double, M, M> covariance =
    (mMeanDist.getPrecision() + mPrecision).inverse();
  mMeanDist.setMean(mean);
  mMeanDist.setCovariance(covariance);
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >::
    addPoint(const Point& point) {
  const double degrees = mCovarianceDist.getDegrees() + 1;
  const Eigen::Matrix<double, M, M> scale = mCovarianceDist.getScale() +
    outerProduct<double, M>(point - mMean);
  mCovarianceDist.setDegrees(degrees);
  mCovarianceDist.setScale(scale);
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> >::
    addPoint(const Point& point) {
  auto mu = mMeanCovarianceDist.getMu();
  const double kappa = mMeanCovarianceDist.getKappa();
  const double nu = mMeanCovarianceDist.getNu();
  auto sigma = mMeanCovarianceDist.getSigma();
  mMeanCovarianceDist.setMu((kappa * mu + point) / (kappa + 1));
  mMeanCovarianceDist.setKappa(kappa + 1);
  mMeanCovarianceDist.setNu(nu + 1);
  mMeanCovarianceDist.setSigma(sigma + kappa / (kappa + 1) *
    outerProduct<double, M>(point - mu));
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> >::
    addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd) {
  for (auto it = itStart; it != itEnd; ++it)
    addPoint(*it);
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> >::
    addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd) {
  for (auto it = itStart; it != itEnd; ++it)
    addPoint(*it);
}

template <size_t M>
void EstimatorBayes<NormalDistribution<M>,
    NormalInvWishartDistribution<M> >::
    addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd) {
  for (auto it = itStart; it != itEnd; ++it)
    addPoint(*it);
}
