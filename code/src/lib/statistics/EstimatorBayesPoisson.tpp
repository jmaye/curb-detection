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

EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    EstimatorBayes(const GammaDistribution<double>& prior) :
    mMeanDist(prior) {
}

EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    EstimatorBayes(const EstimatorBayes& other) :
    mMeanDist(other.mMeanDist) {
}

EstimatorBayes<PoissonDistribution, GammaDistribution<double> >&
    EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    operator = (const EstimatorBayes& other) {
  if (this != &other) {
    mMeanDist = other.mMeanDist;
  }
  return *this;
}

EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    ~EstimatorBayes() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

void EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    read(std::istream& stream) {
}

void EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    write(std::ostream& stream) const {
  stream << "Mean distribution: " << std::endl << mMeanDist << std::endl <<
    "Mean mode: " << mMeanDist.getMode() << std::endl <<
    "Mean variance: " << mMeanDist.getVariance() << std::endl <<
    "Predictive distribution: " << std::endl << getPredDist() << std::endl <<
    "Predictive mean: " << getPredDist().getMean() << std::endl <<
    "Predictive variance: " << getPredDist().getVariance();
}

void EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    read(std::ifstream& stream) {
}

void EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

const GammaDistribution<double>&
    EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::getDist()
    const {
  return mMeanDist;
}

NegativeBinomialDistribution
    EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    getPredDist() const {
  return NegativeBinomialDistribution(mMeanDist.getShape(),
    1.0 / (mMeanDist.getInvScale() + 1));
}

void EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    addPoint(const Point& point) {
  mMeanDist.setShape(mMeanDist.getShape() + point);
  mMeanDist.setInvScale(mMeanDist.getInvScale() + 1);
}

void EstimatorBayes<PoissonDistribution, GammaDistribution<double> >::
    addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd) {
  for (auto it = itStart; it != itEnd; ++it)
    addPoint(*it);
}
