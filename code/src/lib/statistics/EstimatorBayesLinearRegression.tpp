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
EstimatorBayes<LinearRegression<M>, NormalScaledInvChiSquareDistribution<M> >::
    EstimatorBayes(const NormalScaledInvChiSquareDistribution<M>& prior) :
    mCoeffVarianceDist(prior) {
}

template <size_t M>
EstimatorBayes<LinearRegression<M>, NormalScaledInvChiSquareDistribution<M> >::
    EstimatorBayes(const EstimatorBayes& other) :
    mCoeffVarianceDist(other.mCoeffVarianceDist) {
}

template <size_t M>
EstimatorBayes<LinearRegression<M>, NormalScaledInvChiSquareDistribution<M> >&
    EstimatorBayes<LinearRegression<M>,
    NormalScaledInvChiSquareDistribution<M> >::operator = (const EstimatorBayes&
    other) {
  if (this != &other) {
    mCoeffVarianceDist = other.mCoeffVarianceDist;
  }
  return *this;
}

template <size_t M>
EstimatorBayes<LinearRegression<M>, NormalScaledInvChiSquareDistribution<M> >::
    ~EstimatorBayes() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorBayes<LinearRegression<M>,
    NormalScaledInvChiSquareDistribution<M> >::read(std::istream& stream) {
}

template <size_t M>
void EstimatorBayes<LinearRegression<M>,
    NormalScaledInvChiSquareDistribution<M> >::write(std::ostream& stream)
    const {
  stream << "Coefficients and variance distribution: " << std::endl
    << mCoeffVarianceDist << std::endl
    << "Coefficients mode: " << std::endl
    << std::get<0>(mCoeffVarianceDist.getMode()) << std::endl
    << "Variance mode: "
    << std::get<1>(mCoeffVarianceDist.getMode());
}

template <size_t M>
void EstimatorBayes<LinearRegression<M>,
    NormalScaledInvChiSquareDistribution<M> >::read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorBayes<LinearRegression<M>,
    NormalScaledInvChiSquareDistribution<M> >::write(std::ofstream& stream)
    const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
const NormalScaledInvChiSquareDistribution<M>&
    EstimatorBayes<LinearRegression<M>,
    NormalScaledInvChiSquareDistribution<M> >::getDist() const {
  return mCoeffVarianceDist;
}

template <size_t M>
LinearRegressionPred<M>
    EstimatorBayes<LinearRegression<M>,
    NormalScaledInvChiSquareDistribution<M> >::getPredDist() const {
  return LinearRegressionPred<M>(mCoeffVarianceDist.getNu() -
    mCoeffVarianceDist.getMu().size(),
    mCoeffVarianceDist.getMu(), mCoeffVarianceDist.getKappa(),
    mCoeffVarianceDist.getSigma());
}

template <size_t M>
void EstimatorBayes<LinearRegression<M>,
    NormalScaledInvChiSquareDistribution<M> >::addPoint(const Point& point) {
  auto mu = mCoeffVarianceDist.getMu();
  auto kappa = mCoeffVarianceDist.getKappa();
  auto nu = mCoeffVarianceDist.getNu();
  auto sigma = mCoeffVarianceDist.getSigma();
  auto x = (Eigen::Matrix<double, M, 1>() << 1.0,
    point.segment(0, mu.size() - 1)).finished();
  auto y = point.template end<1>();
  mCoeffVarianceDist.setKappa((outerProduct<double, M>(x) + kappa.inverse()).
    inverse());
  mCoeffVarianceDist.setMu(mCoeffVarianceDist.getKappa() *
    (kappa.inverse() * mu + x * y));
  mCoeffVarianceDist.setNu(nu + 1);
  mCoeffVarianceDist.setSigma(nu / (nu + 1) * sigma +
    (outerProduct<double, 1>(y)(0) +
    (mu.transpose() * kappa.inverse() * mu)(0) -
    (mCoeffVarianceDist.getMu().transpose() *
    mCoeffVarianceDist.getKappa().inverse() * mCoeffVarianceDist.getMu())(0)) /
    (nu + 1));
}

template <size_t M>
void EstimatorBayes<LinearRegression<M>,
    NormalScaledInvChiSquareDistribution<M> >::addPoints(const
    ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  for (auto it = itStart; it != itEnd; ++it)
    addPoint(*it);
}

template <size_t M>
void EstimatorBayes<LinearRegression<M>,
    NormalScaledInvChiSquareDistribution<M> >::addPoints(const Container&
    points) {
  addPoints(points.begin(), points.end());
}
