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

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename X>
GammaFunction<X>::GammaFunction(size_t dim) :
  mDim(dim) {
}

GammaFunction<size_t>::GammaFunction() {
}

template <typename X>
GammaFunction<X>::GammaFunction(const GammaFunction<X>& other) :
  mDim(other.mDim) {
}

template <typename X>
GammaFunction<X>& GammaFunction<X>::operator = (const GammaFunction<X>& other) {
  if (this != &other) {
    mDim = other.mDim;
  }
  return *this;
}

template <typename X>
GammaFunction<X>::~GammaFunction() {
}

GammaFunction<size_t>::~GammaFunction() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename X>
void GammaFunction<X>::read(std::istream& stream) {
}

template <typename X>
void GammaFunction<X>::write(std::ostream& stream) const {
  stream << "dimension: " << mDim;
}

template <typename X>
void GammaFunction<X>::read(std::ifstream& stream) {
}

template <typename X>
void GammaFunction<X>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename X>
double GammaFunction<X>::getValue(const X& argument) const {
  double prod = 1.0;
  for (size_t i = 0; i < mDim; ++i) {
    prod *= tgamma(argument - 0.5 * i);
  }
  return prod * pow(M_PI, mDim * (mDim - 1) * 0.25);
}

size_t GammaFunction<size_t>::getValue(const size_t& argument) const
  throw (BadArgumentException<size_t>) {
  if (argument)
    return FactorialFunction::getValue(argument - 1);
  else throw BadArgumentException<size_t>(argument,
    "GammaFunction<size_t>::getValue(): argument must be strictly positive",
    __FILE__, __LINE__);
}

template <typename X>
size_t GammaFunction<X>::getDim() const {
  return mDim;
}

template <typename X>
void GammaFunction<X>::setDim(size_t dim) {
  mDim = dim;
}
