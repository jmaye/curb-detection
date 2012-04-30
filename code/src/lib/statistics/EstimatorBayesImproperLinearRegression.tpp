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
EstimatorBayesImproper<LinearRegression<M> >::EstimatorBayesImproper() :
    mNumPoints(0),
    mValid(false) {
}

template <size_t M>
EstimatorBayesImproper<LinearRegression<M> >::EstimatorBayesImproper(const
    EstimatorBayesImproper& other) :
    mPostCoeffDist(other.mPostCoeffDist),
    mPostVarianceDist(other.mPostVarianceDist),
    mPostPredDist(other.mPostPredDist),
    mSampleCoeff(other.mSampleCoeff),
    mSampleCoeffCovariance(other.mSampleCoeffCovariance),
    mSampleRegressionVariance(other.mSampleRegressionVariance),
    mNumPoints(other.mNumPoints),
    mValid(other.mValid) {
}

template <size_t M>
EstimatorBayesImproper<LinearRegression<M> >&
    EstimatorBayesImproper<LinearRegression<M> >::operator =
    (const EstimatorBayesImproper& other) {
  if (this != &other) {
    mPostCoeffDist = other.mPostCoeffDist;
    mPostVarianceDist = other.mPostVarianceDist;
    mPostPredDist = other.mPostPredDist;
    mSampleCoeff = other.mSampleCoeff;
    mSampleCoeffCovariance = other.mSampleCoeffCovariance;
    mSampleRegressionVariance = other.mSampleRegressionVariance;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
  }
  return *this;
}

template <size_t M>
EstimatorBayesImproper<LinearRegression<M> >::~EstimatorBayesImproper() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorBayesImproper<LinearRegression<M> >::read(std::istream& stream) {
}

template <size_t M>
void EstimatorBayesImproper<LinearRegression<M> >::write(std::ostream& stream)
    const {
  stream << "posterior coefficients distribution: " << std::endl
    << mPostCoeffDist
    << std::endl << "posterior variance distribution: " << std::endl
    << mPostVarianceDist << std::endl
    << "posterior predictive distribution: " << std::endl << mPostPredDist
    << std::endl
    << "sample coefficients: " << mSampleCoeff.transpose() << std::endl
    << "sample coefficients covariance: " << std::endl
    << mSampleCoeffCovariance << std::endl
    << "sample regression variance: " << mSampleRegressionVariance << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

template <size_t M>
void EstimatorBayesImproper<LinearRegression<M> >::read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorBayesImproper<LinearRegression<M> >::write(std::ofstream& stream)
    const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
const StudentDistribution<M>&
    EstimatorBayesImproper<LinearRegression<M> >::getPostCoeffDist() const {
  return mPostCoeffDist;
}

template <size_t M>
const ScaledInvChiSquareDistribution&
    EstimatorBayesImproper<LinearRegression<M> >::getPostVarianceDist() const {
  return mPostVarianceDist;
}

template <size_t M>
const LinearRegressionPred<M>&
    EstimatorBayesImproper<LinearRegression<M> >::getPostPredDist() const {
  return mPostPredDist;
}

template <size_t M>
const Eigen::Matrix<double, M, 1>&
    EstimatorBayesImproper<LinearRegression<M> >::getSampleCoeff() const {
  return mSampleCoeff;
}

template <size_t M>
const Eigen::Matrix<double, M, M>&
    EstimatorBayesImproper<LinearRegression<M> >::getSampleCoeffCovariance()
    const {
  return mSampleCoeffCovariance;
}

template <size_t M>
double EstimatorBayesImproper<LinearRegression<M> >::
    getSampleRegressionVariance() const {
  return mSampleRegressionVariance;
}

template <size_t M>
size_t EstimatorBayesImproper<LinearRegression<M> >::getNumPoints() const {
  return mNumPoints;
}

template <size_t M>
bool EstimatorBayesImproper<LinearRegression<M> >::getValid() const {
  return mValid;
}

template <size_t M>
void EstimatorBayesImproper<LinearRegression<M> >::reset() {
  mNumPoints = 0;
  mValid = false;
}

template <size_t M>
void EstimatorBayesImproper<LinearRegression<M> >::addPoints(const
    ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  Eigen::Matrix<double, Eigen::Dynamic, 1> weights =
    Eigen::Matrix<double, Eigen::Dynamic, 1>::Ones(itEnd - itStart);
  return addPoints(itStart, itEnd, weights);
}

template <size_t M>
void EstimatorBayesImproper<LinearRegression<M> >::addPoints(const
    ConstPointIterator& itStart, const ConstPointIterator& itEnd, const
    Eigen::Matrix<double, Eigen::Dynamic, 1>& weights) {
  reset();
  mNumPoints = itEnd - itStart;
  size_t dim;
  if (mNumPoints != 0)
    dim = itStart->size();
  else
    return;
  if (mNumPoints <= dim)
    return;
  if ((size_t)weights.size() != mNumPoints)
    return;
  Eigen::Matrix<double, Eigen::Dynamic, 1> targets(mNumPoints);
  Eigen::Matrix<double, Eigen::Dynamic, M> designMatrix(mNumPoints, (int)dim);
  for (ConstPointIterator it = itStart; it != itEnd; ++it) {
    const size_t row = it - itStart;
    targets(row) = (*it)(dim - 1);
    designMatrix(row, 0) = 1.0;
    designMatrix.row(row).segment(1, dim - 1) = (*it).segment(0, dim - 1);
  }
  const Eigen::QR<Eigen::Matrix<double, Eigen::Dynamic, M> > qrDecomp =
    (weights.asDiagonal() * designMatrix).qr();
  if ((size_t)qrDecomp.rank() == dim) {
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> coeff;
    qrDecomp.solve(weights.asDiagonal() * targets, &coeff);
    mSampleCoeff = coeff;
    mSampleRegressionVariance = ((targets - designMatrix *
      mSampleCoeff).transpose() * weights.asDiagonal() * (targets -
      designMatrix * mSampleCoeff))(0) / (mNumPoints - dim);
    const Eigen::Matrix<double, M, M> invR = qrDecomp.matrixR().inverse();
    mSampleCoeffCovariance = invR * invR.transpose();
    mPostVarianceDist.setDegrees(mNumPoints - dim);
    mPostVarianceDist.setScale(mSampleRegressionVariance);
    mPostCoeffDist.setDegrees(mNumPoints - dim);
    mPostCoeffDist.setLocation(mSampleCoeff);
    mPostCoeffDist.setScale(mSampleRegressionVariance * mSampleCoeffCovariance);
    mPostPredDist.setDegrees(mNumPoints - dim);
    mPostPredDist.setCoefficients(mSampleCoeff);
    mPostPredDist.setCoeffCovariance(mSampleCoeffCovariance);
    mPostPredDist.setRegressionVariance(mSampleRegressionVariance);
    mValid = true;
  }
  else
    mValid = false;
}

template <size_t M>
void EstimatorBayesImproper<LinearRegression<M> >::addPoints(const Container&
    points) {
  addPoints(points.begin(), points.end());
}
