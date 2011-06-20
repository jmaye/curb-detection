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

#include "statistics/UniInverseGamma.h"

#include <iostream>
#include <fstream>

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/


UniInverseGamma::UniInverseGamma(double f64Alpha, double f64Beta)
  throw (OutOfBoundException) :
  mf64Alpha(f64Alpha),
  mf64Beta(f64Beta) {
  if (mf64Alpha <= 0.0)
    throw OutOfBoundException("UniInverseGamma::UniInverseGamma(): mf64Alpha should be bigger than 0");
  if (mf64Beta <= 0.0)
    throw OutOfBoundException("UniInverseGamma::UniInverseGamma(): mf64Beta should be bigger than 0");
}

UniInverseGamma::UniInverseGamma(const UniInverseGamma& other)
  : mf64Alpha(other.mf64Alpha),
    mf64Beta(other.mf64Beta) {
}

UniInverseGamma& UniInverseGamma::operator = (const UniInverseGamma& other) {
  mf64Alpha = other.mf64Alpha;
  mf64Beta = other.mf64Beta;
  return *this;
}

UniInverseGamma::~UniInverseGamma() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void UniInverseGamma::read(std::istream& stream) {
}

void UniInverseGamma::write(std::ostream& stream) const {
}

void UniInverseGamma::read(std::ifstream& stream) {
}

void UniInverseGamma::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream, const UniInverseGamma& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, UniInverseGamma& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream, const UniInverseGamma& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, UniInverseGamma& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

double UniInverseGamma::getAlpha() const {
  return mf64Alpha;
}

double UniInverseGamma::getBeta() const {
  return mf64Beta;
}

void UniInverseGamma::setAlpha(double f64Alpha) throw (OutOfBoundException) {
  mf64Alpha = f64Alpha;
  if (mf64Alpha <= 0.0)
    throw OutOfBoundException("UniInverseGamma::setAlpha(): mf64Alpha should be bigger than 0");
}

void UniInverseGamma::setBeta(double f64Beta) throw (OutOfBoundException) {
  mf64Beta = f64Beta;
  if (mf64Beta <= 0.0)
    throw OutOfBoundException("UniInverseGamma::setBeta(): mf64Beta should be bigger than 0");
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double UniInverseGamma::pdf(double f64X) const throw (OutOfBoundException) {
  if (f64X < 0.0)
    throw OutOfBoundException("UniInverseGamma::pdf(): f64X should be bigger or equal to 0");
  return (pow(mf64Beta, mf64Alpha) / tgamma(mf64Alpha)) *
    pow(f64X, -mf64Alpha - 1.0) * exp(-mf64Beta / f64X);
}

double UniInverseGamma::logpdf(double f64X) const throw (OutOfBoundException) {
  if (f64X < 0.0)
    throw OutOfBoundException("UniInverseGamma::logpdf(): f64X should be bigger or equal to 0");
  return (mf64Alpha * log(mf64Beta)) - lgamma(mf64Alpha) -
    ((mf64Alpha + 1.0) * log(f64X)) - (mf64Beta / f64X);
}
