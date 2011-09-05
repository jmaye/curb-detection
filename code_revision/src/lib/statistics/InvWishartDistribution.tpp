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

#include "functions/LogGammaFunction.h"

#include <Eigen/LU>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
InvWishartDistribution<M>::InvWishartDistribution(double degrees, const
  Eigen::Matrix<double, M, M>& scale) :
  mDegrees(degrees),
  mScale(scale) {
  setDegrees(degrees);
  setScale(scale);
}

template <size_t M>
InvWishartDistribution<M>::InvWishartDistribution(const
  InvWishartDistribution<M>& other) :
  mDegrees(other.mDegrees),
  mScale(other.mScale),
  mDeterminant(other.mDeterminant),
  mNormalizer(other.mNormalizer),
  mTransformation(other.mTransformation) {
}

template <size_t M>
InvWishartDistribution<M>& InvWishartDistribution<M>::operator = (const
  InvWishartDistribution<M>& other) {
  if (this != &other) {
    mDegrees = other.mDegrees;
    mScale = other.mScale;
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
void InvWishartDistribution<M>::setDegrees(double degrees)
  throw (BadArgumentException<double>) {
  if (degrees < (size_t)mScale.rows())
    throw BadArgumentException<double>(degrees,
      "InvWishartDistribution<M>::setDegrees(): degrees must be strictly "
      "bigger than the dimension",
      __FILE__, __LINE__);
  mDegrees = degrees;
}

template <size_t M>
double InvWishartDistribution<M>::getDegrees() const {
  return mDegrees;
}

template <size_t M>
void InvWishartDistribution<M>::setScale(const Eigen::Matrix<double, M, M>&
  scale) throw (BadArgumentException<Eigen::Matrix<double, M, M> >) {
  mTransformation = scale.llt();
  if (mTransformation.isPositiveDefinite() == false)
    throw BadArgumentException<Eigen::Matrix<double, M, M> >(scale,
      "InvWishartDistribution<M>::setScale(): scale must be positive definite",
      __FILE__, __LINE__);
  mDeterminant = scale.determinant();
  LogGammaFunction<double> logGammaFunction(mScale.rows());
  mNormalizer = mDegrees * mScale.rows() * 0.5 * log(2) - mDegrees * 0.5 *
    log(mDeterminant) + logGammaFunction(0.5 * mDegrees);
  mScale = scale;
}

template <size_t M>
const Eigen::Matrix<double, M, M>& InvWishartDistribution<M>::getScale() const {
  return mScale;
}

template <size_t M>
double InvWishartDistribution<M>::getDeterminant() const {
  return mDeterminant;
}

template <size_t M>
double InvWishartDistribution<M>::getNormalizer() const {
  return mNormalizer;
}

template <size_t M>
const Eigen::LLT<Eigen::Matrix<double, M, M> >&
  InvWishartDistribution<M>::getTransformation() const {
  return mTransformation;
}

template <size_t M>
Eigen::Matrix<double, M, M> InvWishartDistribution<M>::getMean() const {
  return mScale / (mDegrees - mScale.rows() - 1);
}

template <size_t M>
Eigen::Matrix<double, M, M> InvWishartDistribution<M>::getMode() const {
  return mScale / (mDegrees + mScale.rows() + 1);
}

template <size_t M>
double InvWishartDistribution<M>::pdf(const Eigen::Matrix<double, M, M>& value)
  const {
  return exp(logpdf(value));
}

template <size_t M>
double InvWishartDistribution<M>::logpdf(const Eigen::Matrix<double, M, M>&
  value) const throw (BadArgumentException<Eigen::Matrix<double, M, M> >) {
  if (value.llt().isPositiveDefinite() == false)
    throw BadArgumentException<Eigen::Matrix<double, M, M> >(value,
      "InvWishartDistribution<M>::pdf(): value must be positive definite",
      __FILE__, __LINE__);
  return -(mDegrees + mScale.rows() + 1) * 0.5 * log(value.determinant())
    - 0.5 * (mScale * value.inverse()).trace() - mNormalizer;
}

template <size_t M>
Eigen::Matrix<double, M, M> InvWishartDistribution<M>::getSample() const {
  static NormalDistribution<M> normalDist(
    Eigen::Matrix<double, M, 1>::Zero(mScale.rows()), mScale);
  normalDist.setCovariance(mScale);
  Eigen::Matrix<double, M, M> sample =
    Eigen::Matrix<double, M, M>::Zero(mScale.rows(), mScale.rows());
  for (size_t i = 0; i < mDegrees; ++i) {
    Eigen::Matrix<double, M, 1> normSample = normalDist.getSample();
    sample += normSample * normSample.transpose();
  }
  return sample.inverse();
}
