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
EstimatorBayes<LinearRegression<M>, M>::EstimatorBayes(const
  Eigen::Matrix<double, M, 1>& mu , const Eigen::Matrix<double, M, M>& V,
  double nu, double sigma) :
  mPostCoeffDist(nu, mu, sigma * V),
  mPostVarianceDist(nu, sigma / nu),
  mPostPredDist(nu, mu, V, sigma / nu),
  mMu(mu),
  mV(V),
  mNu(nu),
  mSigma(sigma) {
}

template <size_t M>
EstimatorBayes<LinearRegression<M>, M>::EstimatorBayes(const
  EstimatorBayes<LinearRegression<M>, M>& other) :
  mPostCoeffDist(other.mPostCoeffDist),
  mPostVarianceDist(other.mPostVarianceDist),
  mPostPredDist(other.mPostPredDist) {
}

template <size_t M>
EstimatorBayes<LinearRegression<M>, M>&
  EstimatorBayes<LinearRegression<M>, M>::operator =
  (const EstimatorBayes<LinearRegression<M>, M>& other) {
  if (this != &other) {
    mPostCoeffDist = other.mPostCoeffDist;
    mPostVarianceDist = other.mPostVarianceDist;
    mPostPredDist = other.mPostPredDist;
  }
  return *this;
}

template <size_t M>
EstimatorBayes<LinearRegression<M>, M>::~EstimatorBayes() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorBayes<LinearRegression<M>, M>::read(std::istream& stream) {
}

template <size_t M>
void EstimatorBayes<LinearRegression<M>, M>::write(std::ostream& stream) const {
  stream << "posterior coefficients distribution: " << std::endl
    << mPostCoeffDist
    << std::endl << "posterior variance distribution: " << std::endl
    << mPostVarianceDist << std::endl
    << "posterior predictive distribution: " << std::endl << mPostPredDist;
}

template <size_t M>
void EstimatorBayes<LinearRegression<M>, M>::read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorBayes<LinearRegression<M>, M>::write(std::ofstream& stream)
  const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
const StudentDistribution<M>& EstimatorBayes<LinearRegression<M>, M>::
  getPostCoeffDist() const {
  return mPostCoeffDist;
}

template <size_t M>
const ScaledInvChiSquareDistribution&
EstimatorBayes<LinearRegression<M>, M>::getPostVarianceDist() const {
  return mPostVarianceDist;
}

template <size_t M>
const LinearRegressionPred<M>& EstimatorBayes<LinearRegression<M>, M>::
getPostPredDist() const {
  return mPostPredDist;
}

template <size_t M>
void EstimatorBayes<LinearRegression<M>, M>::addPoint(const Point& point) {
  Eigen::Matrix<double, M, 1> inputPoint(mMu.size());
  inputPoint(0) = 1.0;
  inputPoint.segment(1, mMu.size() - 1) = point.segment(0, mMu.size() - 1);
  const Eigen::Matrix<double, M, M> newV = (mV.inverse() + inputPoint *
    inputPoint.transpose()).inverse();
  const Eigen::Matrix<double, M, 1> newMu = newV * (mV.inverse() * mMu +
    inputPoint * point(mMu.size() - 1));
  const double newNu = mNu + 1;
  const double newSigma = mSigma + (point(mMu.size() - 1) *
    point(mMu.size() - 1) + (mMu.transpose() * mV.inverse() * mMu)(0) -
    (newMu.transpose() * newV.inverse() * newMu)(0));
  mMu = newMu;
  mV = newV;
  mNu = newNu;
  mSigma = newSigma;
  mPostVarianceDist.setDegrees(mNu);
  mPostVarianceDist.setScale(mSigma / mNu);
  mPostCoeffDist.setDegrees(mNu);
  mPostCoeffDist.setLocation(mMu);
  mPostCoeffDist.setScale(mSigma * mV / mNu);
  mPostPredDist.setDegrees(mNu);
  mPostPredDist.setCoefficients(mMu);
  mPostPredDist.setCoeffCovariance(mV);
  mPostPredDist.setRegressionVariance(mSigma / mNu);
}

template <size_t M>
void EstimatorBayes<LinearRegression<M>, M>::addPoints(const ConstPointIterator&
  itStart, const ConstPointIterator& itEnd) {
  for (ConstPointIterator it = itStart; it != itEnd; ++it)
    addPoint(*it);
}

template <size_t M>
void EstimatorBayes<LinearRegression<M>, M>::addPoints(const ConstPointIterator&
  itStart, const ConstPointIterator& itEnd, const
  Eigen::Matrix<double, Eigen::Dynamic, 1>& weights) {
}
