#include "statistics/UniGaussian.h"

#include <iostream>
#include <fstream>

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

UniGaussian::UniGaussian(double f64Mean, double f64Variance)
  throw (OutOfBoundException) :
  mf64Mean(f64Mean),
  mf64Variance(f64Variance) {
  if (mf64Variance <= 0)
    throw OutOfBoundException("UniGaussian::UniGaussian(): mf64Variance must be greater than 0");
}

UniGaussian::UniGaussian(const UniGaussian& other) :
  mf64Mean(other.mf64Mean),
  mf64Variance(other.mf64Variance) {
}

UniGaussian& UniGaussian::operator = (const UniGaussian& other) {
  mf64Mean = other.mf64Mean;
  mf64Variance = other.mf64Variance;
  return *this;
}

UniGaussian::~UniGaussian() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void UniGaussian::read(std::istream& stream) {
}

void UniGaussian::write(std::ostream& stream) const {
}

void UniGaussian::read(std::ifstream& stream) {
}

void UniGaussian::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream, const UniGaussian& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, UniGaussian& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream, const UniGaussian& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, UniGaussian& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

double UniGaussian::getMean() const {
  return mf64Mean;
}

double UniGaussian::getVariance() const {
  return mf64Variance;
}

void UniGaussian::setMean(double f64Mean) {
  mf64Mean = f64Mean;
}

void UniGaussian::setVariance(double f64Variance) throw (OutOfBoundException) {
  mf64Variance = f64Variance;
  if (mf64Variance <= 0) {
    throw OutOfBoundException("UniGaussian::setVariance(): mf64Variance must be greater than 0");
  }
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double UniGaussian::pdf(double f64X) const {
  return (1.0 / sqrt(2.0 * M_PI * mf64Variance)) *
    exp(-pow(f64X - mf64Mean, 2) / (2.0 * mf64Variance));
}

double UniGaussian::logpdf(double f64X) const {
  return -log(M_PI * mf64Variance) -
    (pow(f64X - mf64Mean, 2) / (2.0 * mf64Variance));
}

double UniGaussian::KLDivergence(const UniGaussian& other) const {
  double f64Mu1 = mf64Mean;
  double f64Mu2 = other.mf64Mean;
  double f64Var1 = mf64Variance;
  double f64Var2 = other.mf64Variance;
  return pow(f64Mu1 - f64Mu2, 2) / (2 * f64Var2) +
    1 / 2 * (f64Var1 / f64Var2 - 1 - log(f64Var1 / f64Var2));
}
