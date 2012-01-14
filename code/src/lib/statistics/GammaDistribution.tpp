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

#include "statistics/Randomizer.h"

#include "functions/LogGammaFunction.h"
#include "functions/GammaFunction.h"

#include <gsl/gsl_sf_gamma.h>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename T>
GammaDistribution<T>::GammaDistribution(const T& shape, double invScale) {
  setShape(shape);
  setInvScale(invScale);
}

template <typename T>
GammaDistribution<T>::GammaDistribution(const GammaDistribution<T>& other) :
  mShape(other.mShape),
  mInvScale(other.mInvScale),
  mNormalizer(other.mNormalizer) {
}

template <typename T>
GammaDistribution<T>& GammaDistribution<T>::operator =
  (const GammaDistribution<T>& other) {
  if (this != &other) {
    mShape = other.mShape;
    mInvScale = other.mInvScale;
    mNormalizer = other.mNormalizer;
  }
  return *this;
}

template <typename T>
GammaDistribution<T>::~GammaDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename T>
void GammaDistribution<T>::read(std::istream& stream) {
}

template <typename T>
void GammaDistribution<T>::write(std::ostream& stream) const {
  stream << "shape: " << mShape << std::endl
    << "inverse scale: " << mInvScale;
}

template <typename T>
void GammaDistribution<T>::read(std::ifstream& stream) {
}

template <typename T>
void GammaDistribution<T>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename T>
void GammaDistribution<T>::setShape(const T& shape)
  throw (BadArgumentException<T>) {
  if (shape <= 0)
    throw BadArgumentException<T>(shape,
      "GammaDistribution::setShape(): shape must be strictly positive",
      __FILE__, __LINE__);
  mShape = shape;
  LogGammaFunction<T> logGammaFunction;
  mNormalizer = logGammaFunction(mShape) - mShape * log(mInvScale);
}

template <typename T>
const T& GammaDistribution<T>::getShape() const {
  return mShape;
}

template <typename T>
void GammaDistribution<T>::setInvScale(double invScale)
  throw (BadArgumentException<double>) {
  if (invScale <= 0)
    throw BadArgumentException<double>(invScale,
      "GammaDistribution::setScale(): inverse scale must be strictly positive",
      __FILE__, __LINE__);
  mInvScale = invScale;
  LogGammaFunction<T> logGammaFunction;
  mNormalizer = logGammaFunction(mShape) - mShape * log(mInvScale);
}

template <typename T>
double GammaDistribution<T>::getInvScale() const {
  return mInvScale;
}

template <typename T>
double GammaDistribution<T>::getNormalizer() const {
  return mNormalizer;
}

template <typename T>
double GammaDistribution<T>::pdf(const double& value) const {
  if (value <= 0)
    return 0.0;
  else
    return exp(logpdf(value));
}

template <typename T>
double GammaDistribution<T>::logpdf(const double& value) const {
  return (mShape - 1) * log(value) - value * mInvScale - mNormalizer;
}

template <typename T>
double GammaDistribution<T>::cdf(const double& value) const {
  if (value <= 0)
    return 0.0;
  else {
    GammaFunction<T> gammaFunction;
    return gsl_sf_gamma_inc(mShape, value * mInvScale) / gammaFunction(mShape);
  }
}

template <typename T>
double GammaDistribution<T>::getSample() const {
  static Randomizer<double> randomizer;
  return randomizer.sampleGamma(mShape, mInvScale);
}

template <typename T>
double GammaDistribution<T>::getMean() const {
  return mShape / mInvScale;
}

template <typename T>
double GammaDistribution<T>::getMode() const {
  if (mShape >= 1)
    return (mShape - 1) / mInvScale;
  return 0;
}

template <typename T>
double GammaDistribution<T>::getVariance() const {
  return mShape / (mInvScale * mInvScale);
}
