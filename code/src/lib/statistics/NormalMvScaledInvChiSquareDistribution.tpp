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
NormalScaledInvChiSquareDistribution<M>::NormalScaledInvChiSquareDistribution(
    Eigen::Matrix<double, M, 1> mu, Eigen::Matrix<double, M, M> kappa,
    double nu, double sigma) :
    mMu(mu),
    mKappa(kappa),
    mNu(nu),
    mSigma(sigma) {
}

template <size_t M>
NormalScaledInvChiSquareDistribution<M>::NormalScaledInvChiSquareDistribution(
    const NormalScaledInvChiSquareDistribution& other) :
    mMu(other.mMu),
    mKappa(other.mKappa),
    mNu(other.mNu),
    mSigma(other.mSigma) {
}

template <size_t M>
NormalScaledInvChiSquareDistribution<M>&
    NormalScaledInvChiSquareDistribution<M>::
    operator = (const NormalScaledInvChiSquareDistribution& other) {
  if (this != &other) {
    mMu = other.mMu;
    mKappa = other.mKappa;
    mNu = other.mNu;
    mSigma = other.mSigma;
  }
  return *this;
}

template <size_t M>
NormalScaledInvChiSquareDistribution<M>::
    ~NormalScaledInvChiSquareDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <size_t M>
void NormalScaledInvChiSquareDistribution<M>::read(std::istream& stream) {
}

template <size_t M>
void NormalScaledInvChiSquareDistribution<M>::write(std::ostream& stream)
    const {
  stream << "mu: " << std::endl << mMu << std::endl << "kappa: " << std::endl
    << mKappa << std::endl
    << "nu: " << mNu << std::endl << "sigma: " << mSigma;
}

template <size_t M>
void NormalScaledInvChiSquareDistribution<M>::read(std::ifstream& stream) {
}

template <size_t M>
void NormalScaledInvChiSquareDistribution<M>::write(std::ofstream& stream)
    const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
ScaledInvChiSquareDistribution NormalScaledInvChiSquareDistribution<M>::
    getVarianceDist() const {
  return ScaledInvChiSquareDistribution(mNu, mSigma);
}

template <size_t M>
StudentDistribution<M> NormalScaledInvChiSquareDistribution<M>::
    getMargMeanDist() const {
  return StudentDistribution<M>(mNu, mMu, mSigma * mKappa);
}

template <size_t M>
const Eigen::Matrix<double, M, 1>&
    NormalScaledInvChiSquareDistribution<M>::getMu() const {
  return mMu;
}

template <size_t M>
void NormalScaledInvChiSquareDistribution<M>::
    setMu(const Eigen::Matrix<double, M, 1>& mu) {
  mMu = mu;
}

template <size_t M>
const Eigen::Matrix<double, M, M>&
    NormalScaledInvChiSquareDistribution<M>::getKappa() const {
  return mKappa;
}

template <size_t M>
void NormalScaledInvChiSquareDistribution<M>::
    setKappa(const Eigen::Matrix<double, M, M>& kappa) {
  mKappa = kappa;
}

template <size_t M>
double NormalScaledInvChiSquareDistribution<M>::getNu() const {
  return mNu;
}

template <size_t M>
void NormalScaledInvChiSquareDistribution<M>::setNu(double nu) {
  mNu = nu;
}

template <size_t M>
double NormalScaledInvChiSquareDistribution<M>::getSigma() const {
  return mSigma;
}

template <size_t M>
void NormalScaledInvChiSquareDistribution<M>::setSigma(double sigma) {
  mSigma = sigma;
}

template <size_t M>
double NormalScaledInvChiSquareDistribution<M>::
    pdf(const RandomVariable& value) const {
  return getVarianceDist().pdf(std::get<1>(value)) *
    NormalDistribution<M>(mMu, std::get<1>(value) * mKappa).pdf(
    std::get<0>(value));
}

template <size_t M>
typename NormalScaledInvChiSquareDistribution<M>::Mode
    NormalScaledInvChiSquareDistribution<M>::getMode() const {
  const double variance = getVarianceDist().getMode();
  return Mode(NormalDistribution<M>(mMu, variance * mKappa).getMode(),
    variance);
}

template <size_t M>
typename NormalScaledInvChiSquareDistribution<M>::RandomVariable
    NormalScaledInvChiSquareDistribution<M>::getSample() const {
  const double variance = getVarianceDist().getSample();
  return RandomVariable(
    NormalDistribution<M>(mMu, variance * mKappa).getSample(), variance);
}
