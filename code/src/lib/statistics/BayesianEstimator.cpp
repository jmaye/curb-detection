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

  double f64AlphaNew = f64AlphaOld + 1.0 / 2.0;
  double f64BetaNew = f64BetaOld + (f64NuOld *
    pow(f64DataPoint - f64LambdaOld, 2.0)) / (2.0 * (f64NuOld + 1.0));
  double f64LambdaNew = (f64NuOld * f64LambdaOld + f64DataPoint) /
    (f64NuOld + 1);
  double f64NuNew = f64NuOld + 1.0;

  meanPrior.setMean(f64LambdaNew);
  meanPrior.setVariance(f64NuNew);
  variancePrior.setAlpha(f64AlphaNew);
  variancePrior.setBeta(f64BetaNew);
  dist.setMean(f64LambdaNew);
  dist.setVariance(f64BetaNew / (f64AlphaNew - 1.0));
}
