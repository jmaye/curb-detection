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

#include <Eigen/LU>

#include "functions/LogGammaFunction.h"
#include "statistics/ChiSquareDistribution.h"
#include "statistics/NormalDistribution.h"
#include "exceptions/BadArgumentException.h"
#include "exceptions/InvalidOperationException.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
StudentDistribution<M>::StudentDistribution(double degrees, const Location&
    location, const Scale& scale):
    mLocation(location) {
  setDegrees(degrees);
  setScale(scale);
}

template <size_t M>
StudentDistribution<M>::StudentDistribution(const StudentDistribution& other) :
    mLocation(other.mLocation),
    mScale(other.mScale),
    mDegrees(other.mDegrees),
    mInverseScale(other.mInverseScale),
    mDeterminant(other.mDeterminant),
    mNormalizer(other.mNormalizer),
    mTransformation(other.mTransformation) {
}

template <size_t M>
StudentDistribution<M>& StudentDistribution<M>::operator = (const
    StudentDistribution& other) {
  if (this != &other) {
    mLocation = other.mLocation;
    mScale = other.mScale;
    mDegrees = other.mDegrees;
    mInverseScale = other.mInverseScale;
    mDeterminant = other.mDeterminant;
    mNormalizer = other.mNormalizer;
    mTransformation = other.mTransformation;
  }
  return *this;
}

template <size_t M>
StudentDistribution<M>::~StudentDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <size_t M>
void StudentDistribution<M>::read(std::istream& stream) {
}

template <size_t M>
void StudentDistribution<M>::write(std::ostream& stream) const {
  stream << "location: " << std::endl << mLocation << std::endl
    << "scale: " << std::endl << mScale << std::endl
    << "degrees: " << mDegrees;
}

template <size_t M>
void StudentDistribution<M>::read(std::ifstream& stream) {
}

template <size_t M>
void StudentDistribution<M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
void StudentDistribution<M>::setLocation(const Location& location) {
  mLocation = location;
}

template <size_t M>
const typename StudentDistribution<M>::Location&
    StudentDistribution<M>::getLocation() const {
  return mLocation;
}

template <size_t M>
void StudentDistribution<M>::setScale(const Scale& scale) {
  if (scale.transpose() != scale)
    throw BadArgumentException<Scale>(scale,
      "StudentDistribution<M>::setScale(): scale must be symmetric",
      __FILE__, __LINE__);
  mTransformation = scale.llt();
  if (!mTransformation.isPositiveDefinite())
    throw BadArgumentException<Scale>(scale,
      "StudentDistribution<M>::setScale(): scale must be positive "
      "definite",
      __FILE__, __LINE__);
  if ((scale.diagonal().cwise() < 0).any())
    throw BadArgumentException<Scale>(scale,
      "StudentDistribution<M>::setScale(): elements must be positive",
      __FILE__, __LINE__);
  mDeterminant = scale.determinant();
  scale.computeInverse(&mInverseScale);
  mScale = scale;
  computeNormalizer();
}

template <size_t M>
const typename StudentDistribution<M>::Scale& StudentDistribution<M>::getScale()
    const {
  return mScale;
}

template <size_t M>
void StudentDistribution<M>::setDegrees(double degrees) {
  if (degrees <= 0)
    throw BadArgumentException<double>(degrees,
      "StudentDistribution<M>::setDegrees(): degrees must be strictly positive",
      __FILE__, __LINE__);
  mDegrees = degrees;
  computeNormalizer();
}

template <size_t M>
double StudentDistribution<M>::getDegrees() const {
  return mDegrees;
}

template <size_t M>
const typename StudentDistribution<M>::Scale&
    StudentDistribution<M>::getInverseScale() const {
  return mInverseScale;
}

template <size_t M>
double StudentDistribution<M>::getDeterminant() const {
  return mDeterminant;
}

template <size_t M>
void StudentDistribution<M>::computeNormalizer() {
  const LogGammaFunction<double> logGammaFunction;
  mNormalizer = logGammaFunction(mDegrees * 0.5) + mLocation.size() * 0.5 *
    log(mDegrees * M_PI) + 0.5 * log(mDeterminant) - logGammaFunction(0.5 *
    (mDegrees + mLocation.size()));
}

template <size_t M>
double StudentDistribution<M>::getNormalizer() const {
  return mNormalizer;
}

template <size_t M>
const Eigen::LLT<typename StudentDistribution<M>::Scale>&
    StudentDistribution<M>::getTransformation() const {
  return mTransformation;
}

template <size_t M>
double StudentDistribution<M>::pdf(const RandomVariable& value) const {
  return exp(logpdf(value));
}

template <size_t M>
double StudentDistribution<M>::logpdf(const RandomVariable& value) const {
  return -0.5 * (mLocation.size() + mDegrees) * log(1.0 + 1.0 / mDegrees *
    mahalanobisDistance(value)) - mNormalizer;
}

template <size_t M>
typename StudentDistribution<M>::RandomVariable
    StudentDistribution<M>::getSample() const {
  static NormalDistribution<M> normalDist(mLocation, mScale);
  static ChiSquareDistribution chi2Dist;
  normalDist.setMean(mLocation);
  normalDist.setCovariance(mScale);
  chi2Dist.setDegrees(mDegrees);
  return normalDist.getSample() / sqrt(chi2Dist.getSample() / mDegrees);
}

template <size_t M>
double StudentDistribution<M>::mahalanobisDistance(const RandomVariable& value)
    const {
  return ((value - mLocation).transpose() * mInverseScale *
    (value - mLocation))(0, 0);
}

template <size_t M>
typename StudentDistribution<M>::Mean StudentDistribution<M>::getMean() const {
  if (mDegrees > 1)
    return mLocation;
  else
    throw InvalidOperationException("StudentDistribution<M>::getMean(): "
      "degrees must be bigger than 1");
}

template <size_t M>
typename StudentDistribution<M>::Mode StudentDistribution<M>::getMode() const {
  return mLocation;
}

template <size_t M>
typename StudentDistribution<M>::Covariance
    StudentDistribution<M>::getCovariance() const {
  if (mDegrees > 2)
    return mDegrees / (mDegrees - 2) * mScale;
  else
    throw InvalidOperationException("StudentDistribution<M>::getCovariance(): "
      "degrees must be bigger than 2");
}
