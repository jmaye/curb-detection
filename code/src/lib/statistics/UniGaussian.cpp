#include "UniGaussian.h"

#include <iostream>
#include <fstream>

#include <math.h>

using namespace std;

UniGaussian::UniGaussian(double f64Mean, double f64Variance)
  : mf64Mean(f64Mean),
    mf64Variance(f64Variance) {
}

UniGaussian::~UniGaussian() {
}

void UniGaussian::read(istream& stream) {
}

void UniGaussian::write(ostream& stream) const {
}

void UniGaussian::read(ifstream& stream) {
}

void UniGaussian::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream,
  const UniGaussian& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream,
  UniGaussian& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream,
  const UniGaussian& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream,
  UniGaussian& obj) {
  obj.read(stream);
  return stream;
}

double UniGaussian::pdf(double f64X) const {
  return (1 / sqrt(2 * M_PI * mf64Variance)) *
    exp(-pow(f64X - mf64Mean, 2) / (2 * mf64Variance));
}

void UniGaussian::addDataPoint(double f64Z) {
}

double UniGaussian::getMean() const {
}

double UniGaussian::getVariance() const {
}

void UniGaussian::setMean(double f64Mean) {
  mf64Mean = f64Mean;
}

void UniGaussian::setVariance(double f64Variance) {
  mf64Variance = f64Variance;
}
