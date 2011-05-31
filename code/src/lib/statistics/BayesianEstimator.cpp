#include "statistics/BayesianEstimator.h"

#include <iostream>
#include <fstream>

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

BayesianEstimator::BayesianEstimator() {
}

BayesianEstimator::BayesianEstimator(const BayesianEstimator& other) {
}

BayesianEstimator&
  BayesianEstimator::operator = (const BayesianEstimator& other) {
  return *this;
}

BayesianEstimator::~BayesianEstimator() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void BayesianEstimator::read(std::istream& stream) {
}

void BayesianEstimator::write(std::ostream& stream) const {
}

void BayesianEstimator::read(std::ifstream& stream) {
}

void BayesianEstimator::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream, const BayesianEstimator& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, BayesianEstimator& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream,
  const BayesianEstimator& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, BayesianEstimator& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

uint32_t BayesianEstimator::getPointsNbr() const {
  return mu32PointsNbr;
}

void BayesianEstimator::setPointsNbr(uint32_t u32PointsNbr) {
  mu32PointsNbr = u32PointsNbr;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void BayesianEstimator::addDataPoint(UniGaussian& dist, UniGaussian& meanPrior,
  UniInverseGamma& variancePrior, double f64DataPoint) {
  mu32PointsNbr++;
  double f64AlphaOld = variancePrior.getAlpha();
  double f64BetaOld = variancePrior.getBeta();
  double f64LambdaOld = meanPrior.getMean();
  double f64NuOld = meanPrior.getVariance();

  double f64AlphaNew = f64AlphaOld + 1/2;
  double f64BetaNew = f64BetaOld + (f64NuOld *
    pow(f64DataPoint - f64LambdaOld, 2)) / (2 * (f64NuOld + 1));
  double f64LambdaNew = (f64NuOld * f64LambdaOld + f64DataPoint) /
    (f64NuOld + 1);
  double f64NuNew = f64NuOld + 1;

  meanPrior.setMean(f64LambdaNew);
  meanPrior.setVariance(f64NuNew);
  variancePrior.setAlpha(f64AlphaNew);
  variancePrior.setBeta(f64BetaNew);
  dist.setMean(f64LambdaNew);
  dist.setVariance(f64BetaNew / (f64AlphaNew - 1));
}
