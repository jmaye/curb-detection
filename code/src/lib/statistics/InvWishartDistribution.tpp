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
#include "statistics/NormalDistribution.h"
#include "statistics/WishartDistribution.h"
#include "exceptions/BadArgumentException.h"
#include "exceptions/InvalidOperationException.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
InvWishartDistribution<M>::InvWishartDistribution(double degrees, const
    Scale& scale) {
  setDegrees(degrees);
  setScale(scale);
}

template <size_t M>
InvWishartDistribution<M>::InvWishartDistribution(const
    InvWishartDistribution& other) :
    mDegrees(other.mDegrees),
    mScale(other.mScale),
    mInverseScale(other.mInverseScale),
    mDeterminant(other.mDeterminant),
    mNormalizer(other.mNormalizer),
    mTransformation(other.mTransformation) {
}

template <size_t M>
InvWishartDistribution<M>& InvWishartDistribution<M>::operator = (const
    InvWishartDistribution& other) {
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
InvWishartDistribution<M>::~InvWishartDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <size_t M>
void InvWishartDistribution<M>::read(std::istream& stream) {
}

template <size_t M>
void InvWishartDistribution<M>::write(std::ostream& stream) const {
  stream << "degrees: " << std::endl << mDegrees << std::endl
    << "scale: " << std::endl << mScale;
}

template <size_t M>
void InvWishartDistribution<M>::read(std::ifstream& stream) {
}

template <size_t M>
void InvWishartDistribution<M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
void InvWishartDistribution<M>::setDegrees(double degrees) {
  if (degrees < (size_t)mScale.rows())
    throw BadArgumentException<double>(degrees,
      "InvWishartDistribution<M>::setDegrees(): degrees must be strictly "
      "bigger than the dimension",
      __FILE__, __LINE__);
  mDegrees = degrees;
  computeNormalizer();
}

template <size_t M>
double InvWishartDistribution<M>::getDegrees() const {
  return mDegrees;
}

template <size_t M>
void InvWishartDistribution<M>::setScale(const Scale& scale) {
  mTransformation = scale.llt();
  if (!mTransformation.isPositiveDefinite())
    throw BadArgumentException<Scale>(scale,
      "InvWishartDistribution<M>::setScale(): scale must be positive definite",
      __FILE__, __LINE__);
  mDeterminant = scale.determinant();
  mScale = scale;
  mInverseScale = scale.inverse();
  computeNormalizer();
}

template <size_t M>
const typename InvWishartDistribution<M>::Scale&
    InvWishartDistribution<M>::getScale() const {
  return mScale;
}

template <size_t M>
double InvWishartDistribution<M>::getDeterminant() const {
  return mDeterminant;
}

template <size_t M>
void InvWishartDistribution<M>::computeNormalizer() {
  const LogGammaFunction<double> logGammaFunction(mScale.rows());
  mNormalizer = mDegrees * mScale.rows() * 0.5 * log(2) - mDegrees * 0.5 *
    log(mDeterminant) + logGammaFunction(0.5 * mDegrees);
}

template <size_t M>
double InvWishartDistribution<M>::getNormalizer() const {
  return mNormalizer;
}

template <size_t M>
const Eigen::LLT<typename InvWishartDistribution<M>::Scale>&
    InvWishartDistribution<M>::getTransformation() const {
  return mTransformation;
}

template <size_t M>
typename InvWishartDistribution<M>::Mean InvWishartDistribution<M>::getMean()
  const {
  if (mDegrees > mScale.rows() + 1)
    return mScale / (mDegrees - mScale.rows() - 1);
  else
    throw InvalidOperationException("InvWishartDistribution<M>::getMean(): "
      "degrees of freedom must be bigger than dim + 1");
}

template <size_t M>
typename InvWishartDistribution<M>::Mode
    InvWishartDistribution<M>::getMode() const {
  return mScale / (mDegrees + mScale.rows() + 1);
}

template <size_t M>
typename InvWishartDistribution<M>::Covariance
    InvWishartDistribution<M>::getCovariance() const {
  const double denominator = (mDegrees - mScale.rows()) *
    (mDegrees - mScale.rows() - 1) * (mDegrees - mScale.rows() - 1) *
    (mDegrees - mScale.rows() - 3);
  if (denominator) {
    Covariance covariance = Covariance::Zero(mScale.rows(), mScale.cols());
    for (size_t i = 0; i < (size_t)mScale.rows(); ++i)
      for (size_t j = 0; j < (size_t)mScale.cols(); ++j)
        covariance(i, j) = (mDegrees - mScale.rows() + 1) * mScale(i, j) *
          mScale(i, j) + (mDegrees - mScale.rows() - 1) * mScale(i, i) *
          mScale(j, j);
    return covariance / denominator;
  }
  else
    throw InvalidOperationException(
      "InvWishartDistribution<M>::getCovariance(): invalid covariance");
}

template <size_t M>
double InvWishartDistribution<M>::pdf(const RandomVariable& value) const {
  return exp(logpdf(value));
}

template <size_t M>
double InvWishartDistribution<M>::logpdf(const RandomVariable& value) const {
  if (!value.llt().isPositiveDefinite())
    throw BadArgumentException<RandomVariable>(value,
      "InvWishartDistribution<M>::pdf(): value must be positive definite",
      __FILE__, __LINE__);
  return -(mDegrees + mScale.rows() + 1) * 0.5 * log(value.determinant())
    - 0.5 * (mScale * value.inverse()).trace() - mNormalizer;
}

template <size_t M>
typename InvWishartDistribution<M>::RandomVariable
    InvWishartDistribution<M>::getSample() const {
  return WishartDistribution<M>(mDegrees, mInverseScale).getSample().
    inverse();
}
