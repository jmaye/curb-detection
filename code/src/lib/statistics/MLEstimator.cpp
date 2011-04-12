#include "MLEstimator.h"

#include <iostream>
#include <fstream>

#include <math.h>

using namespace std;

MLEstimator::MLEstimator() : mu32PointsNbr(0),
                             mbStartRegular(false) {
}

MLEstimator::MLEstimator(const MLEstimator& other)
  : mu32PointsNbr(other.mu32PointsNbr),
    mbStartRegular(other.mbStartRegular) {
}

MLEstimator& MLEstimator::operator = (const MLEstimator& other) {
  mu32PointsNbr = other.mu32PointsNbr;
  mbStartRegular = other.mbStartRegular;
  return *this;
}

MLEstimator::~MLEstimator() {
}

void MLEstimator::read(istream& stream) {
}

void MLEstimator::write(ostream& stream) const {
}

void MLEstimator::read(ifstream& stream) {
}

void MLEstimator::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream,
  const MLEstimator& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream,
  MLEstimator& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream,
  const MLEstimator& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream,
  MLEstimator& obj) {
  obj.read(stream);
  return stream;
}

void MLEstimator::addDataPoint(UniGaussian& dist, double f64DataPoint) {
  mu32PointsNbr++;
  double f64Mean = dist.getMean();
  double f64Variance = dist.getVariance();
  f64Mean += 1.0 / (double)mu32PointsNbr * (f64DataPoint - f64Mean);
  if (mbStartRegular == false && f64Mean != f64DataPoint) {
    f64Variance =  1.0 / (double)(mu32PointsNbr) *
      (pow(f64DataPoint - f64Mean, 2));
    mbStartRegular = true;
  }
  if (mbStartRegular == true)
    f64Variance +=  1.0 / (double)(mu32PointsNbr) *
      (pow(f64DataPoint - f64Mean, 2) - f64Variance);
  dist.setMean(f64Mean);
  dist.setVariance(f64Variance);
}

uint32_t MLEstimator::getPointsNbr() const {
  return mu32PointsNbr;
}

void MLEstimator::setPointsNbr(uint32_t u32PointsNbr) {
  mu32PointsNbr = u32PointsNbr;
}
