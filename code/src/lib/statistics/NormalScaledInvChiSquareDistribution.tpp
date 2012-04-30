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

NormalScaledInvChiSquareDistribution::NormalScaledInvChiSquareDistribution(
    double mu, double kappa, double nu, double sigma) :
    mMu(mu),
    mKappa(kappa),
    mNu(nu),
    mSigma(sigma) {
}

NormalScaledInvChiSquareDistribution::NormalScaledInvChiSquareDistribution(
    const NormalScaledInvChiSquareDistribution& other) :
    mMu(other.mMu),
    mKappa(other.mKappa),
    mNu(other.mNu),
    mSigma(other.mSigma) {
}

NormalScaledInvChiSquareDistribution& NormalScaledInvChiSquareDistribution::
    operator = (const NormalScaledInvChiSquareDistribution& other) {
  if (this != &other) {
    mMu = other.mMu;
    mKappa = other.mKappa;
    mNu = other.mNu;
    mSigma = other.mSigma;
  }
  return *this;
}

NormalScaledInvChiSquareDistribution::~NormalScaledInvChiSquareDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void NormalScaledInvChiSquareDistribution::read(std::istream& stream) {
}

void NormalScaledInvChiSquareDistribution::write(std::ostream& stream) const {
  stream << "mu: " << mMu << std::endl << "kappa: " << mKappa << std::endl
    << "nu: " << mNu << std::endl << "sigma: " << mSigma;
}

void NormalScaledInvChiSquareDistribution::read(std::ifstream& stream) {
}

void NormalScaledInvChiSquareDistribution::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

ScaledInvChiSquareDistribution NormalScaledInvChiSquareDistribution::
    getVarianceDist() const {
  return ScaledInvChiSquareDistribution(mNu, mSigma);
}

StudentDistribution<1> NormalScaledInvChiSquareDistribution::
    getMargMeanDist() const {
  return StudentDistribution<1>(mNu, mMu, mSigma / mKappa);
}

double NormalScaledInvChiSquareDistribution::getMu() const {
  return mMu;
}

void NormalScaledInvChiSquareDistribution::setMu(double mu) {
  mMu = mu;
}

double NormalScaledInvChiSquareDistribution::getKappa() const {
  return mKappa;
}

void NormalScaledInvChiSquareDistribution::setKappa(double kappa) {
  mKappa = kappa;
}

double NormalScaledInvChiSquareDistribution::getNu() const {
  return mNu;
}

void NormalScaledInvChiSquareDistribution::setNu(double nu) {
  mNu = nu;
}

double NormalScaledInvChiSquareDistribution::getSigma() const {
  return mSigma;
}

void NormalScaledInvChiSquareDistribution::setSigma(double sigma) {
  mSigma = sigma;
}

double NormalScaledInvChiSquareDistribution::
    pdf(const RandomVariable& value) const {
  return getVarianceDist().pdf(std::get<1>(value)) *
    NormalDistribution<1>(mMu, std::get<1>(value) / mKappa).pdf(
    std::get<0>(value));
}

NormalScaledInvChiSquareDistribution::Mode
    NormalScaledInvChiSquareDistribution::getMode() const {
  const double variance = getVarianceDist().getMode();
  return Mode(NormalDistribution<1>(mMu, variance / mKappa).getMode(),
    variance);
}

NormalScaledInvChiSquareDistribution::RandomVariable
    NormalScaledInvChiSquareDistribution::getSample() const {
  const double variance = getVarianceDist().getSample();
  return RandomVariable(
    NormalDistribution<1>(mMu, variance / mKappa).getSample(), variance);
}
