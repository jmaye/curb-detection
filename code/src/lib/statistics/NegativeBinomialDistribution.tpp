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

#include "statistics/GammaDistribution.h"
#include "statistics/PoissonDistribution.h"
#include "functions/IncompleteBetaFunction.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

NegativeBinomialDistribution::NegativeBinomialDistribution(size_t numTrials,
    double probability) :
    NegativeMultinomialDistribution<2>(numTrials) {
  setProbability(probability);
}

NegativeBinomialDistribution::NegativeBinomialDistribution(const
    NegativeBinomialDistribution& other) :
    NegativeMultinomialDistribution<2>(other) {
}

NegativeBinomialDistribution& NegativeBinomialDistribution::operator =
    (const NegativeBinomialDistribution& other) {
  if (this != &other) {
    NegativeMultinomialDistribution<2>::operator=(other);
  }
  return *this;
}

NegativeBinomialDistribution::~NegativeBinomialDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void NegativeBinomialDistribution::read(std::istream& stream) {
}

void NegativeBinomialDistribution::write(std::ostream& stream) const {
  stream << "success probability: "
    << mProbabilities(0) << std::endl
    << "trials number: " << mNumTrials;
}

void NegativeBinomialDistribution::read(std::ifstream& stream) {
}

void NegativeBinomialDistribution::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void NegativeBinomialDistribution::setProbability(double probability) {
  setProbabilities(Eigen::Matrix<double, 2, 1>(probability, 1.0 - probability));
}

double NegativeBinomialDistribution::getProbability() const {
  return mProbabilities(0);
}

double NegativeBinomialDistribution::getMean() const {
  return NegativeMultinomialDistribution<2>::getMean()(0);
}

int NegativeBinomialDistribution::getMode() const {
  if (mNumTrials > 1)
    return mProbabilities(0) * (mNumTrials - 1) / mProbabilities(1);
  else
    return 0.0;
}

double NegativeBinomialDistribution::getVariance() const {
  return NegativeMultinomialDistribution<2>::getCovariance()(0, 0);
}

Eigen::Matrix<int, 2, 1> NegativeBinomialDistribution::getSample() const {
  static GammaDistribution<double> gammaDist;
  static PoissonDistribution poissonDist;
  gammaDist.setShape(mNumTrials);
  gammaDist.setInvScale(mProbabilities(1) / mProbabilities(0));
  poissonDist.setMean(gammaDist.getSample());
  Eigen::Matrix<int, 2, 1> sample;
  sample(0) = poissonDist.getSample();
  sample(1) = mNumTrials;
  return sample;
}

double NegativeBinomialDistribution::cmf(const int& value) const {
  const IncompleteBetaFunction<double> incBetaFunction(value + 1, mNumTrials);
  if (value < 0)
    return 0;
  else 
    return 1.0 - incBetaFunction(mProbabilities(0));
}
