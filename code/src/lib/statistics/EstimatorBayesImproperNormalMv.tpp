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
EstimatorBayesImproper<NormalDistribution<M> >::EstimatorBayesImproper() :
    mNumPoints(0),
    mValid(false) {
}

template <size_t M>
EstimatorBayesImproper<NormalDistribution<M> >::EstimatorBayesImproper(const
    EstimatorBayesImproper& other) :
    mMeanCovarianceDist(other.mMeanCovarianceDist),
    mNumPoints(other.mNumPoints),
    mValid(other.mValid),
    mValuesSum(other.mValuesSum),
    mSquaredValuesSum(other.mSquaredValuesSum) {
}

template <size_t M>
EstimatorBayesImproper<NormalDistribution<M> >&
    EstimatorBayesImproper<NormalDistribution<M> >::operator =
    (const EstimatorBayesImproper& other) {
  if (this != &other) {
    mMeanCovarianceDist = other.mMeanCovarianceDist;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
    mValuesSum = other.mValuesSum;
    mSquaredValuesSum = other.mSquaredValuesSum;
  }
  return *this;
}

template <size_t M>
EstimatorBayesImproper<NormalDistribution<M> >::~EstimatorBayesImproper() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M> >::read(std::istream&
    stream) {
}

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M> >::write(std::ostream&
    stream) const {
  stream << "Mean and covariance distribution: " << std::endl
    << mMeanCovarianceDist << std::endl
    << "Mean and covariance mode: " << std::endl
    << std::get<0>(mMeanCovarianceDist.getMode()) << std::endl
    << std::get<1>(mMeanCovarianceDist.getMode())
    << std::endl << "Predictive distribution: " << std::endl << getPredDist()
    << std::endl
    << "Predictive mean: " << std::endl << getPredDist().getMean() << std::endl
    << "Predictive covariance: " << std::endl << getPredDist().getCovariance()
    << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M> >::read(std::ifstream&
    stream) {
}

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M> >::write(std::ofstream&
    stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
const NormalInvWishartDistribution<M>&
    EstimatorBayesImproper<NormalDistribution<M> >::getDist() const {
  return mMeanCovarianceDist;
}

template <size_t M>
StudentDistribution<M>
    EstimatorBayesImproper<NormalDistribution<M> >::getPredDist() const {
  const size_t dim = mMeanCovarianceDist.getMu().size();
  return StudentDistribution<M>(mMeanCovarianceDist.getNu() - dim + 1,
    mMeanCovarianceDist.getMu(), (mMeanCovarianceDist.getKappa() + 1) /
    mMeanCovarianceDist.getKappa() /
    (mMeanCovarianceDist.getNu() - dim + 1) *
    mMeanCovarianceDist.getSigma());
}

template <size_t M>
size_t EstimatorBayesImproper<NormalDistribution<M> >::getNumPoints() const {
  return mNumPoints;
}

template <size_t M>
bool EstimatorBayesImproper<NormalDistribution<M> >::getValid() const {
  return mValid;
}

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M> >::reset() {
  mNumPoints = 0;
  mValid = false;
}

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M> >::addPoint(const Point&
    point) {
  if (mNumPoints == 0) {
    mValuesSum = Eigen::Matrix<double, M, 1>::Zero(point.size());
    mSquaredValuesSum = Eigen::Matrix<double, M, M>::Zero(point.size(),
      point.size());
  }
  mNumPoints++;
  mValuesSum += point;
  mSquaredValuesSum += OuterProduct::compute<double, M>(point);
  try {
    mValid = true;
    const Eigen::Matrix<double, M, 1> mean = mValuesSum / mNumPoints;
    const Eigen::Matrix<double, M, M> covariance =
      mSquaredValuesSum / (mNumPoints - point.size()) -
      OuterProduct::compute<double, M>(mValuesSum) * 2 /
      ((mNumPoints - point.size()) * mNumPoints) +
      OuterProduct::compute<double, M>(mean) * ((double)mNumPoints /
      (mNumPoints - point.size()));
    mMeanCovarianceDist.setMu(mean);
    mMeanCovarianceDist.setKappa(mNumPoints);
    mMeanCovarianceDist.setNu(mNumPoints - 1);
    mMeanCovarianceDist.setSigma((mNumPoints - 1) * covariance);
  }
  catch (...) {
    mValid = false;
  }
}

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M> >::addPoints(const
    ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  for (auto it = itStart; it != itEnd; ++it)
    addPoint(*it);
}

template <size_t M>
void EstimatorBayesImproper<NormalDistribution<M> >::addPoints(const
    Container& points) {
  addPoints(points.begin(), points.end());
}
