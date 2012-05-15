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

#include "statistics/NormalDistribution.h"
#include "functions/LogGammaFunction.h"
#include "exceptions/BadArgumentException.h"
#include "exceptions/InvalidOperationException.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
WishartDistribution<M>::WishartDistribution(double degrees,
    const Scale& scale) {
  setDegrees(degrees);
  setScale(scale);
}

template <size_t M>
WishartDistribution<M>::WishartDistribution(const WishartDistribution& other) :
    mDegrees(other.mDegrees),
    mScale(other.mScale),
    mInverseScale(other.mInverseScale),
    mDeterminant(other.mDeterminant),
    mNormalizer(other.mNormalizer),
    mTransformation(other.mTransformation) {
}

template <size_t M>
WishartDistribution<M>& WishartDistribution<M>::operator = (const
    WishartDistribution& other) {
  if (this != &other) {
    mDegrees = other.mDegrees;
    mScale = other.mScale;
    mInverseScale = other.mInverseScale;
    mDeterminant = other.mDeterminant;
    mNormalizer = other.mNormalizer;
    mTransformation = other.mTransformation;
  }
  return *this;
}

template <size_t M>
WishartDistribution<M>::~WishartDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <size_t M>
void WishartDistribution<M>::read(std::istream& stream) {
}

template <size_t M>
void WishartDistribution<M>::write(std::ostream& stream) const {
  stream << "degrees: " << std::endl << mDegrees << std::endl
    << "scale: " << std::endl << mScale;
}

template <size_t M>
void WishartDistribution<M>::read(std::ifstream& stream) {
}

template <size_t M>
void WishartDistribution<M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
void WishartDistribution<M>::setDegrees(double degrees) {
  if (degrees < (size_t)mScale.rows())
    throw BadArgumentException<double>(degrees,
      "WishartDistribution<M>::setDegrees(): degrees must be strictly bigger "
      "than the dimension",
      __FILE__, __LINE__);
  mDegrees = degrees;
  computeNormalizer();
}

template <size_t M>
double WishartDistribution<M>::getDegrees() const {
  return mDegrees;
}

template <size_t M>
void WishartDistribution<M>::setScale(const Scale& scale) {
  mTransformation = scale.llt();
  if (!mTransformation.isPositiveDefinite())
    throw BadArgumentException<Scale>(scale,
      "WishartDistribution<M>::setScale(): scale must be positive definite",
      __FILE__, __LINE__);
  mDeterminant = scale.determinant();
  mInverseScale = scale.inverse();
  mScale = scale;
  computeNormalizer();
}

template <size_t M>
const typename WishartDistribution<M>::Scale&
    WishartDistribution<M>::getScale() const {
  return mScale;
}

template <size_t M>
const typename WishartDistribution<M>::Scale&
    WishartDistribution<M>::getInverseScale() const {
  return mInverseScale;
}

template <size_t M>
double WishartDistribution<M>::getDeterminant() const {
  return mDeterminant;
}

template <size_t M>
void WishartDistribution<M>::computeNormalizer() {
  LogGammaFunction<double> logGammaFunction((size_t)mScale.rows());
  mNormalizer = mDegrees * mScale.rows() * 0.5 * log(2) + mDegrees * 0.5 *
    log(mDeterminant) + logGammaFunction(0.5 * mDegrees);
}

template <size_t M>
double WishartDistribution<M>::getNormalizer() const {
  return mNormalizer;
}

template <size_t M>
const Eigen::LLT<typename WishartDistribution<M>::Scale>&
    WishartDistribution<M>::getTransformation() const {
  return mTransformation;
}

template <size_t M>
typename WishartDistribution<M>::Mean WishartDistribution<M>::getMean() const {
  return mDegrees * mScale;
}

template <size_t M>
typename WishartDistribution<M>::Mode WishartDistribution<M>::getMode() const {
  if (mDegrees >= mScale.rows() + 1)
    return (mDegrees - mScale.rows() - 1) * mScale;
  else
    throw InvalidOperationException("InvWishartDistribution<M>::getMode(): "
      "degrees of freedom must be bigger than dim + 1");
}

template <size_t M>
typename WishartDistribution<M>::Covariance
    WishartDistribution<M>::getCovariance() const {
  Covariance covariance = Covariance::Zero(mScale.rows(), mScale.cols());
  for (size_t i = 0; i < mScale.rows(); ++i)
    for (size_t j = 0; j < mScale.cols(); ++j)
      covariance(i, j) = mScale(i, j) * mScale(i, j) +
        mScale(i, i) * mScale(j, j);
  return covariance * mDegrees;
}

template <size_t M>
double WishartDistribution<M>::pdf(const RandomVariable& value) const {
  return exp(logpdf(value));
}

template <size_t M>
double WishartDistribution<M>::logpdf(const RandomVariable& value) const {
  if (!value.llt().isPositiveDefinite())
    throw BadArgumentException<RandomVariable>(value,
      "WishartDistribution<M>::pdf(): value must be positive definite",
      __FILE__, __LINE__);
  return (mDegrees - mScale.rows() - 1) * 0.5 * log(value.determinant())
    - 0.5 * (mInverseScale * value).trace() - mNormalizer;
}

template <size_t M>
typename WishartDistribution<M>::RandomVariable
    WishartDistribution<M>::getSample() const {
  static NormalDistribution<M> normalDist(
    NormalDistribution<M>::Mean::Zero(mScale.rows()), mScale);
  normalDist.setCovariance(mScale);
  RandomVariable sample = RandomVariable::Zero(mScale.rows(), mScale.rows());
  for (size_t i = 0; i < mDegrees; ++i) {
    typename NormalDistribution<M>::RandomVariable normSample =
      normalDist.getSample();
    sample += normSample * normSample.transpose();
  }
  return sample;
}
