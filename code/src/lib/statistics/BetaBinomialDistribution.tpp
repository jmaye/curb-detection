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

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

BetaBinomialDistribution::BetaBinomialDistribution(size_t numTrials, double
    alpha, double beta) :
    DCMDistribution<2>(numTrials, Eigen::Matrix<double, 2, 1>(alpha, beta)) {
}

BetaBinomialDistribution::BetaBinomialDistribution(const
    BetaBinomialDistribution& other) :
    DCMDistribution<2>(other) {
}

BetaBinomialDistribution& BetaBinomialDistribution::operator =
    (const BetaBinomialDistribution& other) {
  if (this != &other) {
    DCMDistribution<2>::operator=(other);
  }
  return *this;
}

BetaBinomialDistribution::~BetaBinomialDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void BetaBinomialDistribution::read(std::istream& stream) {
}

void BetaBinomialDistribution::write(std::ostream& stream) const {
  stream << "alpha: " << mAlpha(0) << std::endl << "beta: " << mAlpha(1) <<
    std::endl << "trials number: " << mNumTrials;
}

void BetaBinomialDistribution::read(std::ifstream& stream) {
}

void BetaBinomialDistribution::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void BetaBinomialDistribution::setAlpha(double alpha) {
  DCMDistribution<2>::setAlpha(Eigen::Matrix<double, 2, 1>(alpha, getBeta()));
}

double BetaBinomialDistribution::getAlpha() const {
  return mAlpha(0);
}

void BetaBinomialDistribution::setBeta(double beta) {
  DCMDistribution<2>::setAlpha(Eigen::Matrix<double, 2, 1>(getAlpha(), beta));
}

double BetaBinomialDistribution::getBeta() const {
  return mAlpha(1);
}

double BetaBinomialDistribution::getMean() const {
  return DCMDistribution<2>::getMean()(0);
}

int BetaBinomialDistribution::getMode() const {
  return DCMDistribution<2>::getMode()(0);
}

double BetaBinomialDistribution::getVariance() const {
  return DCMDistribution<2>::getCovariance()(0, 0);
}
