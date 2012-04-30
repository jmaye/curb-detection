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

EstimatorBayesImproper<NormalDistribution<1> >::EstimatorBayesImproper() :
    mNumPoints(0),
    mValid(false),
    mValuesSum(0),
    mSquaredValuesSum(0) {
}

EstimatorBayesImproper<NormalDistribution<1> >::EstimatorBayesImproper(const
    EstimatorBayesImproper& other) :
    mMeanVarianceDist(other.mMeanVarianceDist),
    mNumPoints(other.mNumPoints),
    mValid(other.mValid),
    mValuesSum(other.mValuesSum),
    mSquaredValuesSum(other.mSquaredValuesSum) {
}

EstimatorBayesImproper<NormalDistribution<1> >&
    EstimatorBayesImproper<NormalDistribution<1> >::operator =
    (const EstimatorBayesImproper& other) {
  if (this != &other) {
    mMeanVarianceDist = other.mMeanVarianceDist;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
    mValuesSum = other.mValuesSum;
    mSquaredValuesSum = other.mSquaredValuesSum;
  }
  return *this;
}

EstimatorBayesImproper<NormalDistribution<1> >::~EstimatorBayesImproper() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

void EstimatorBayesImproper<NormalDistribution<1> >::read(std::istream&
    stream) {
}

void EstimatorBayesImproper<NormalDistribution<1> >::write(std::ostream& stream)
    const {
  stream << "Mean and variance distribution: " << std::endl << mMeanVarianceDist
    << std::endl << "Mean and variance mode: " << std::endl <<
      std::get<0>(mMeanVarianceDist.getMode()) << std::endl
    << std::get<1>(mMeanVarianceDist.getMode())
    << std::endl << "Predictive distribution: " << std::endl << getPredDist() <<
    std::endl << "Predictive mean: " << getPredDist().getMean() << std::endl
    << "Predictive variance: " << getPredDist().getVariance() << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

void EstimatorBayesImproper<NormalDistribution<1> >::read(std::ifstream&
    stream) {
}

void EstimatorBayesImproper<NormalDistribution<1> >::write(std::ofstream&
    stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

const NormalScaledInvChiSquareDistribution&
    EstimatorBayesImproper<NormalDistribution<1> >::getDist() const {
  return mMeanVarianceDist;
}

StudentDistribution<1>
    EstimatorBayesImproper<NormalDistribution<1> >::getPredDist() const {
  return StudentDistribution<1>(mMeanVarianceDist.getNu(),
    mMeanVarianceDist.getMu(), mMeanVarianceDist.getSigma() *
    (mMeanVarianceDist.getKappa() + 1) / mMeanVarianceDist.getKappa());
}

size_t EstimatorBayesImproper<NormalDistribution<1> >::getNumPoints() const {
  return mNumPoints;
}

bool EstimatorBayesImproper<NormalDistribution<1> >::getValid() const {
  return mValid;
}

void EstimatorBayesImproper<NormalDistribution<1> >::reset() {
  mNumPoints = 0;
  mValid = false;
  mValuesSum = 0;
  mSquaredValuesSum = 0;
}

void EstimatorBayesImproper<NormalDistribution<1> >::addPoint(const Point&
    point) {
  mNumPoints++;
  mValuesSum += point;
  mSquaredValuesSum += point * point;
  try {
    mValid = true;
    const double mean = mValuesSum / mNumPoints;
    const double variance = mSquaredValuesSum / (mNumPoints - 1) -
      mValuesSum * mValuesSum * 2 / ((mNumPoints - 1) * mNumPoints) +
      mean * mean * ((double)mNumPoints / (mNumPoints - 1));
    mMeanVarianceDist.setNu(mNumPoints - 1);
    mMeanVarianceDist.setKappa(mNumPoints);
    mMeanVarianceDist.setMu(mean);
    mMeanVarianceDist.setSigma(variance);
  }
  catch (...) {
    mValid = false;
  }
}

void EstimatorBayesImproper<NormalDistribution<1> >::addPoints(const
    ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  for (auto it = itStart; it != itEnd; ++it)
    addPoint(*it);
}

void EstimatorBayesImproper<NormalDistribution<1> >::addPoints(const Container&
    points) {
  addPoints(points.begin(), points.end());
}
