#include "statistics/MLEstimator.h"

#include <iostream>
#include <fstream>

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

MLEstimator::MLEstimator() :
  mu32PointsNbr(0),
  mbStartRegular(false) {
}

MLEstimator::MLEstimator(const MLEstimator& other) :
  mu32PointsNbr(other.mu32PointsNbr),
  mbStartRegular(other.mbStartRegular) {
}

MLEstimator& MLEstimator::operator = (const MLEstimator& other) {
  mu32PointsNbr = other.mu32PointsNbr;
  mbStartRegular = other.mbStartRegular;
  return *this;
}

MLEstimator::~MLEstimator() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void MLEstimator::read(std::istream& stream) {
}

void MLEstimator::write(std::ostream& stream) const {
}

void MLEstimator::read(std::ifstream& stream) {
}

void MLEstimator::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream, const MLEstimator& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, MLEstimator& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream, const MLEstimator& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, MLEstimator& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

uint32_t MLEstimator::getPointsNbr() const {
  return mu32PointsNbr;
}

void MLEstimator::setPointsNbr(uint32_t u32PointsNbr) {
  mu32PointsNbr = u32PointsNbr;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

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
