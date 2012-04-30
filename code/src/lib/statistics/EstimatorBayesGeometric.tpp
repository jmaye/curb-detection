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

EstimatorBayes<GeometricDistribution, BetaDistribution>::
    EstimatorBayes(const BetaDistribution& prior) :
    mProbDist(prior) {
}

EstimatorBayes<GeometricDistribution, BetaDistribution>::
    EstimatorBayes(const EstimatorBayes& other) :
    mProbDist(other.mProbDist) {
}

EstimatorBayes<GeometricDistribution, BetaDistribution>&
    EstimatorBayes<GeometricDistribution, BetaDistribution>::
    operator = (const EstimatorBayes& other) {
  if (this != &other) {
    mProbDist = other.mProbDist;
  }
  return *this;
}

EstimatorBayes<GeometricDistribution, BetaDistribution>::~EstimatorBayes() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

void EstimatorBayes<GeometricDistribution, BetaDistribution>::
    read(std::istream& stream) {
}

void EstimatorBayes<GeometricDistribution, BetaDistribution>::
    write(std::ostream& stream) const {
  stream << "Mean distribution: " << std::endl << mProbDist << std::endl <<
    "Mean mode: " << mProbDist.getMode() << std::endl <<
    "Mean variance: " << mProbDist.getVariance();
}

void EstimatorBayes<GeometricDistribution, BetaDistribution>::
    read(std::ifstream& stream) {
}

void EstimatorBayes<GeometricDistribution, BetaDistribution>::
    write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

const BetaDistribution&
    EstimatorBayes<GeometricDistribution, BetaDistribution>::getDist() const {
  return mProbDist;
}

void EstimatorBayes<GeometricDistribution, BetaDistribution>::
    addPoint(const Point& point) {
  mProbDist.setAlpha(mProbDist.getAlpha() + 1);
  mProbDist.setBeta(mProbDist.getBeta() + point);
}

void EstimatorBayes<GeometricDistribution, BetaDistribution>::
    addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd) {
  for (auto it = itStart; it != itEnd; ++it)
    addPoint(*it);
}
