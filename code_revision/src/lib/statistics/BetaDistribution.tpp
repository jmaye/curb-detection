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

BetaDistribution::BetaDistribution(double alpha, double beta) :
  DirichletDistribution<2>() {
  DirichletDistribution<2>::setAlpha(Eigen::Matrix<double, 2, 1>(alpha, beta));
}

BetaDistribution::BetaDistribution(const BetaDistribution& other) :
  DirichletDistribution<2>(other) {
}

BetaDistribution& BetaDistribution::operator = (const BetaDistribution& other) {
  if (this != &other) {
    this->DirichletDistribution<2>::operator=(other);
  }
  return *this;
}

BetaDistribution::~BetaDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void BetaDistribution::read(std::istream& stream) {
}

void BetaDistribution::write(std::ostream& stream) const {
  stream << "alpha: " << mAlpha(0) << std::endl << "beta: " << mAlpha(1);
}

void BetaDistribution::read(std::ifstream& stream) {
}

void BetaDistribution::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void BetaDistribution::setAlpha(double alpha) {
  DirichletDistribution<2>::setAlpha(Eigen::Matrix<double, 2, 1>(alpha,
    getBeta()));
}

double BetaDistribution::getAlpha() const {
  return mAlpha(0);
}

void BetaDistribution::setBeta(double beta) {
  DirichletDistribution<2>::setAlpha(Eigen::Matrix<double, 2, 1>(getAlpha(),
    beta));
}

double BetaDistribution::getBeta() const {
  return mAlpha(1);
}

double BetaDistribution::getMean() const {
  return DirichletDistribution<2>::getMean()(1);
}

double BetaDistribution::getMode() const {
  if (mAlpha(0) > 1 && mAlpha(1) > 1)
    return (mAlpha(1) - 1) / (mAlpha(0) + mAlpha(1) - 2);
  else
    return 0;
}

double BetaDistribution::getVariance() const {
  return DirichletDistribution<2>::getCovariance()(1, 1);
}
