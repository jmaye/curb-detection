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

EstimatorBayes<NormalDistribution<1>, NormalDistribution<1> >::
    EstimatorBayes(double variance, const NormalDistribution<1>& prior) :
    mMeanDist(prior),
    mVariance(variance),
    mPrecision(1 / variance) {
}

EstimatorBayes<NormalDistribution<1>, ScaledInvChiSquareDistribution>::
    EstimatorBayes(double mean, const ScaledInvChiSquareDistribution& prior) :
    mVarianceDist(prior),
    mMean(mean) {
}

EstimatorBayes<NormalDistribution<1>, NormalScaledInvChiSquareDistribution>::
    EstimatorBayes(const NormalScaledInvChiSquareDistribution& prior) :
    mMeanVarianceDist(prior) {
}

EstimatorBayes<NormalDistribution<1>, NormalDistribution<1> >::EstimatorBayes(
    const EstimatorBayes& other) :
    mMeanDist(other.mMeanDist),
    mVariance(other.mVariance),
    mPrecision(other.mPrecision) {
}

EstimatorBayes<NormalDistribution<1>, ScaledInvChiSquareDistribution>::
    EstimatorBayes(const EstimatorBayes& other) :
    mVarianceDist(other.mVarianceDist),
    mMean(other.mMean) {
}

EstimatorBayes<NormalDistribution<1>, NormalScaledInvChiSquareDistribution>::
    EstimatorBayes(const EstimatorBayes& other) :
    mMeanVarianceDist(other.mMeanVarianceDist) {
}

EstimatorBayes<NormalDistribution<1>, NormalDistribution<1> >&
    EstimatorBayes<NormalDistribution<1>, NormalDistribution<1> >::operator =
    (const EstimatorBayes& other) {
  if (this != &other) {
    mMeanDist = other.mMeanDist;
    mVariance = other.mVariance;
    mPrecision = other.mPrecision;
  }
  return *this;
}

EstimatorBayes<NormalDistribution<1>, ScaledInvChiSquareDistribution>&
    EstimatorBayes<NormalDistribution<1>, ScaledInvChiSquareDistribution>::
    operator = (const EstimatorBayes& other) {
  if (this != &other) {
    mVarianceDist = other.mVarianceDist;
    mMean = other.mMean;
  }
  return *this;
}

EstimatorBayes<NormalDistribution<1>, NormalScaledInvChiSquareDistribution>&
    EstimatorBayes<NormalDistribution<1>, NormalScaledInvChiSquareDistribution>
    ::operator = (const EstimatorBayes& other) {
  if (this != &other) {
    mMeanVarianceDist = other.mMeanVarianceDist;
  }
  return *this;
}

EstimatorBayes<NormalDistribution<1>, NormalDistribution<1> >::
    ~EstimatorBayes() {
}

EstimatorBayes<NormalDistribution<1>, ScaledInvChiSquareDistribution>::
    ~EstimatorBayes() {
}

EstimatorBayes<NormalDistribution<1>, NormalScaledInvChiSquareDistribution>::
    ~EstimatorBayes() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

void EstimatorBayes<NormalDistribution<1>, NormalDistribution<1> >::
    read(std::istream& stream) {
}

void EstimatorBayes<NormalDistribution<1>, ScaledInvChiSquareDistribution>::
    read(std::istream& stream) {
}

void EstimatorBayes<NormalDistribution<1>,
    NormalScaledInvChiSquareDistribution>::read(std::istream& stream) {
}

void EstimatorBayes<NormalDistribution<1>, NormalDistribution<1> >::
    write(std::ostream& stream) const {
  stream << "Mean distribution: " << std::endl << mMeanDist << std::endl
    << "Mean mode: " << mMeanDist.getMode() << std::endl
    << "Mean variance: " << mMeanDist.getVariance() << std::endl
    << "Predictive distribution: " << std::endl << getPredDist() << std::endl
    << "Predictive mean: " << getPredDist().getMean() << std::endl
    << "Predictive variance: " << getPredDist().getVariance();
}

void EstimatorBayes<NormalDistribution<1>, ScaledInvChiSquareDistribution>::
    write(std::ostream& stream) const {
  stream << "Variance distribution: " << std::endl << mVarianceDist << std::endl
    << "Variance mode: " << mVarianceDist.getMode() << std::endl
    << "Variance variance: " << mVarianceDist.getVariance();
}

void EstimatorBayes<NormalDistribution<1>,
    NormalScaledInvChiSquareDistribution>::write(std::ostream& stream) const {
  stream << "Mean and variance distribution: " << std::endl << mMeanVarianceDist
    << std::endl << "Mean and variance mode: " << std::endl <<
      std::get<0>(mMeanVarianceDist.getMode()) << std::endl
    << std::get<1>(mMeanVarianceDist.getMode())
    << std::endl << "Predictive distribution: " << std::endl << getPredDist() <<
    std::endl << "Predictive mean: " << getPredDist().getMean() << std::endl
    << "Predictive variance: " << getPredDist().getVariance();
}

void EstimatorBayes<NormalDistribution<1>, NormalDistribution<1> >::
    read(std::ifstream& stream) {
}

void EstimatorBayes<NormalDistribution<1>, ScaledInvChiSquareDistribution>::
    read(std::ifstream& stream) {
}

void EstimatorBayes<NormalDistribution<1>,
    NormalScaledInvChiSquareDistribution>::read(std::ifstream& stream) {
}

void EstimatorBayes<NormalDistribution<1>, NormalDistribution<1> >::
    write(std::ofstream& stream) const {
}

void EstimatorBayes<NormalDistribution<1>, ScaledInvChiSquareDistribution>::
    write(std::ofstream& stream) const {
}

void EstimatorBayes<NormalDistribution<1>,
    NormalScaledInvChiSquareDistribution>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

const NormalDistribution<1>&
    EstimatorBayes<NormalDistribution<1>, NormalDistribution<1> >::getDist()
    const {
  return mMeanDist;
}

const ScaledInvChiSquareDistribution&
    EstimatorBayes<NormalDistribution<1>, ScaledInvChiSquareDistribution>::
    getDist() const {
  return mVarianceDist;
}

const NormalScaledInvChiSquareDistribution&
    EstimatorBayes<NormalDistribution<1>,
    NormalScaledInvChiSquareDistribution>::getDist() const {
  return mMeanVarianceDist;
}

NormalDistribution<1>
    EstimatorBayes<NormalDistribution<1>, NormalDistribution<1> >::
    getPredDist() const {
  return NormalDistribution<1>(mMeanDist.getMean(), mMeanDist.getVariance() +
    mVariance);
}

StudentDistribution<1>
    EstimatorBayes<NormalDistribution<1>,
    NormalScaledInvChiSquareDistribution>::getPredDist() const {
  return StudentDistribution<1>(mMeanVarianceDist.getNu(),
    mMeanVarianceDist.getMu(), mMeanVarianceDist.getSigma() *
    (mMeanVarianceDist.getKappa() + 1) / mMeanVarianceDist.getKappa());
}

void EstimatorBayes<NormalDistribution<1>, NormalDistribution<1> >::
    addPoint(const Point& point) {
  const double mean = (mMeanDist.getPrecision() * mMeanDist.getMean() +
    mPrecision * point) / (mMeanDist.getPrecision() + mPrecision);
  const double variance = 1.0 / (mMeanDist.getPrecision() +
    mPrecision);
  mMeanDist.setMean(mean);
  mMeanDist.setVariance(variance);
}

void EstimatorBayes<NormalDistribution<1>, ScaledInvChiSquareDistribution>::
    addPoint(const Point& point) {
  const double degrees = mVarianceDist.getDegrees() + 1;
  const double scale = (mVarianceDist.getDegrees() * mVarianceDist.getScale() +
    (point - mMean) * (point - mMean)) / degrees;
  mVarianceDist.setDegrees(degrees);
  mVarianceDist.setScale(scale);
}

void EstimatorBayes<NormalDistribution<1>,
    NormalScaledInvChiSquareDistribution>::addPoint(const Point& point) {
  const double mu = mMeanVarianceDist.getMu();
  const double kappa = mMeanVarianceDist.getKappa();
  const double nu = mMeanVarianceDist.getNu();
  const double sigma = mMeanVarianceDist.getSigma();
  mMeanVarianceDist.setMu((kappa * mu + point) / (kappa + 1));
  mMeanVarianceDist.setKappa(kappa + 1);
  mMeanVarianceDist.setNu(nu + 1);
  mMeanVarianceDist.setSigma(sigma * nu / (nu + 1) + kappa / (kappa + 1) *
    (point - mu) * (point - mu) / (nu + 1));
}

void EstimatorBayes<NormalDistribution<1>, NormalDistribution<1> >::
    addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd) {
  for (auto it = itStart; it != itEnd; ++it)
    addPoint(*it);
}

void EstimatorBayes<NormalDistribution<1>, ScaledInvChiSquareDistribution>::
    addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd) {
  for (auto it = itStart; it != itEnd; ++it)
    addPoint(*it);
}

void EstimatorBayes<NormalDistribution<1>,
    NormalScaledInvChiSquareDistribution>::
    addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd) {
  for (auto it = itStart; it != itEnd; ++it)
    addPoint(*it);
}
