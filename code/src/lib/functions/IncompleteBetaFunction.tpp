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

#include <gsl/gsl_sf_gamma.h>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename X>
IncompleteBetaFunction<X>::IncompleteBetaFunction(double alpha, double beta) :
    mAlpha(alpha),
    mBeta(beta) {
}

template <typename X>
IncompleteBetaFunction<X>::IncompleteBetaFunction(const IncompleteBetaFunction&
    other) :
    mAlpha(other.mAlpha),
    mBeta(other.mBeta) {
}

template <typename X>
IncompleteBetaFunction<X>& IncompleteBetaFunction<X>::operator = (const
    IncompleteBetaFunction& other) {
  if (this != &other) {
    mAlpha = other.mAlpha;
    mBeta = other.mBeta;
  }
  return *this;
}

template <typename X>
IncompleteBetaFunction<X>::~IncompleteBetaFunction() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename X>
void IncompleteBetaFunction<X>::read(std::istream& stream) {
}

template <typename X>
void IncompleteBetaFunction<X>::write(std::ostream& stream) const {
  stream << "alpha: " << mAlpha << std::endl << "beta: " << mBeta;
}

template <typename X>
void IncompleteBetaFunction<X>::read(std::ifstream& stream) {
}

template <typename X>
void IncompleteBetaFunction<X>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename X>
double IncompleteBetaFunction<X>::getValue(const VariableType& argument) const {
  return gsl_sf_beta_inc(mAlpha, mBeta, argument);
}

template <typename X>
double IncompleteBetaFunction<X>::getAlpha() const {
  return mAlpha;
}

template <typename X>
void IncompleteBetaFunction<X>::setAlpha(double alpha) {
  mAlpha = alpha;
}

template <typename X>
double IncompleteBetaFunction<X>::getBeta() const {
  return mBeta;
}

template <typename X>
void IncompleteBetaFunction<X>::setBeta(double beta) {
  mBeta = beta;
}
