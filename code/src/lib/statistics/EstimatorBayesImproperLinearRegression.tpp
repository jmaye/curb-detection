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
EstimatorBayesImproper<LinearRegression<M> >::EstimatorBayesImproper() :
    mNumPoints(0),
    mValid(false) {
}

template <size_t M>
EstimatorBayesImproper<LinearRegression<M> >::EstimatorBayesImproper(const
    EstimatorBayesImproper& other) :
    mCoeffVarianceDist(other.mCoeffVarianceDist),
    mNumPoints(other.mNumPoints),
    mValid(other.mValid) {
}

template <size_t M>
EstimatorBayesImproper<LinearRegression<M> >&
    EstimatorBayesImproper<LinearRegression<M> >::operator =
    (const EstimatorBayesImproper& other) {
  if (this != &other) {
    mCoeffVarianceDist = other.mCoeffVarianceDist;
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
  stream << "Coefficients and variance distribution: " << std::endl
    << mCoeffVarianceDist << std::endl
    << "Coefficients mode: " << std::endl
    << std::get<0>(mCoeffVarianceDist.getMode()) << std::endl
    << "Variance mode: "
    << std::get<1>(mCoeffVarianceDist.getMode()) << std::endl
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
const NormalScaledInvChiSquareDistribution<M>&
    EstimatorBayesImproper<LinearRegression<M> >::getDist() const {
  return mCoeffVarianceDist;
}

template <size_t M>
LinearRegressionPred<M>
    EstimatorBayesImproper<LinearRegression<M> >::getPredDist() const {
  return LinearRegressionPred<M>(mNumPoints - mCoeffVarianceDist.getMu().size(),
    mCoeffVarianceDist.getMu(), mCoeffVarianceDist.getKappa(),
    mCoeffVarianceDist.getSigma());
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
  reset();
  mNumPoints = itEnd - itStart;
  size_t dim;
  if (mNumPoints != 0)
    dim = itStart->size();
  else
    return;
  if (mNumPoints < dim)
    return;
  Eigen::Matrix<double, Eigen::Dynamic, 1> targets(mNumPoints);
  Eigen::Matrix<double, Eigen::Dynamic, M> designMatrix(mNumPoints, (int)dim);
  for (auto it = itStart; it != itEnd; ++it) {
    const size_t row = it - itStart;
    targets(row) = (*it)(dim - 1);
    designMatrix(row, 0) = 1.0;
    designMatrix.row(row).segment(1, dim - 1) = (*it).segment(0, dim - 1);
  }
  try {
    const Eigen::Matrix<double, M, M> covariance =
      (designMatrix.transpose() * designMatrix).inverse();
    const Eigen::Matrix<double, M, 1> sampleCoeffs =
      covariance * designMatrix.transpose() * targets;
    for (size_t i = 0; i < dim; ++i)
      if (std::isnan(sampleCoeffs(i)))
        return;
    const double variance = ((targets - designMatrix * sampleCoeffs).transpose()
      * (targets - designMatrix * sampleCoeffs))(0) / (mNumPoints - dim);
    mValid = true;
    mCoeffVarianceDist.setMu(sampleCoeffs);
    mCoeffVarianceDist.setKappa(covariance);
    mCoeffVarianceDist.setNu(mNumPoints - dim);
    mCoeffVarianceDist.setSigma(variance);
  }
  catch (...) {
    mValid = false;
  }
}

template <size_t M>
void EstimatorBayesImproper<LinearRegression<M> >::addPoints(const Container&
    points) {
  addPoints(points.begin(), points.end());
}
