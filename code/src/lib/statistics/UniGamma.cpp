#include "UniGamma.h"

#include <iostream>
#include <fstream>

#include <math.h>

using namespace std;

UniGamma::UniGamma(double f64Alpha, double f64Beta)
  throw (OutOfBoundException) : mf64Alpha(f64Alpha),
                                mf64Beta(f64Beta) {
  if (mf64Alpha <= 0)
    throw OutOfBoundException("UniGamma::UniGamma(): mf64Alpha should be bigger than 0");
  if (mf64Beta <= 0)
    throw OutOfBoundException("UniGamma::UniGamma(): mf64Beta should be bigger than 0");
}

UniGamma::UniGamma(const UniGamma& other)
  : mf64Alpha(other.mf64Alpha),
    mf64Beta(other.mf64Beta) {
}

UniGamma& UniGamma::operator = (const UniGamma& other) {
  mf64Alpha = other.mf64Alpha;
  mf64Beta = other.mf64Beta;
  return *this;
}

UniGamma::~UniGamma() {
}

void UniGamma::read(istream& stream) {
}

void UniGamma::write(ostream& stream) const {
}

void UniGamma::read(ifstream& stream) {
}

void UniGamma::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream,
  const UniGamma& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream,
  UniGamma& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream,
  const UniGamma& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream,
  UniGamma& obj) {
  obj.read(stream);
  return stream;
}

double UniGamma::pdf(double f64X) const throw (OutOfBoundException) {
  if (f64X < 0)
    throw OutOfBoundException("UniGamma::pdf(): f64X should be bigger or equal to 0");
  return (pow(mf64Beta, mf64Alpha) / tgamma(mf64Alpha)) *
    pow(f64X, mf64Alpha - 1) * exp(-mf64Beta * f64X);
}

double UniGamma::logpdf(double f64X) const throw (OutOfBoundException) {
  if (f64X < 0)
    throw OutOfBoundException("UniGamma::logpdf(): f64X should be bigger or equal to 0");
  return (mf64Alpha * log(mf64Beta)) - lgamma(mf64Alpha) +
    ((mf64Alpha - 1) * log(f64X)) - (mf64Beta * f64X);
}

double UniGamma::getAlpha() const {
  return mf64Alpha;
}

double UniGamma::getBeta() const {
  return mf64Beta;
}

void UniGamma::setAlpha(double f64Alpha) throw (OutOfBoundException) {
  mf64Alpha = f64Alpha;
  if (mf64Alpha <= 0)
    throw OutOfBoundException("UniInverseGamma::setAlpha(): mf64Alpha should be bigger than 0");
}

void UniGamma::setBeta(double f64Beta) throw (OutOfBoundException) {
  mf64Beta = f64Beta;
  if (mf64Beta <= 0)
    throw OutOfBoundException("UniInverseGamma::setBeta(): mf64Beta should be bigger than 0");
}
