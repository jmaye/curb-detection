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
  mSampleMean(0),
  mSampleVariance(0),
  mNumPoints(0),
  mValid(false) {
}

EstimatorBayesImproper<NormalDistribution<1> >::EstimatorBayesImproper(const
  EstimatorBayesImproper<NormalDistribution<1> >& other) :
  mPostMeanDist(other.mPostMeanDist),
  mPostVarianceDist(other.mPostVarianceDist),
  mPostPredDist(other.mPostPredDist),
  mSampleMean(other.mSampleMean),
  mSampleVariance(other.mSampleVariance),
  mNumPoints(other.mNumPoints),
  mValid(other.mValid) {
}

EstimatorBayesImproper<NormalDistribution<1> >&
  EstimatorBayesImproper<NormalDistribution<1> >::operator =
  (const EstimatorBayesImproper<NormalDistribution<1> >& other) {
  if (this != &other) {
    mPostMeanDist = other.mPostMeanDist;
    mPostVarianceDist = other.mPostVarianceDist;
    mPostPredDist = other.mPostPredDist;
    mSampleMean = other.mSampleMean;
    mSampleVariance = other.mSampleVariance;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
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
  stream << "posterior mean distribution: " << std::endl << mPostMeanDist
    << std::endl << "posterior variance distribution: " << std::endl
    << mPostVarianceDist
    << std::endl << "posterior predictive distribution: " << std::endl
    << mPostPredDist << std::endl
    << "sample mean: " << mSampleMean << std::endl
    << "sample variance: " << mSampleVariance << std::endl
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

const StudentDistribution<1>& EstimatorBayesImproper<NormalDistribution<1> >::
getPostMeanDist() const {
  return mPostMeanDist;
}

const ScaledInvChiSquareDistribution&
EstimatorBayesImproper<NormalDistribution<1> >::getPostVarianceDist() const {
  return mPostVarianceDist;
}

const StudentDistribution<1>& EstimatorBayesImproper<NormalDistribution<1> >::
getPostPredDist() const {
  return mPostPredDist;
}

double EstimatorBayesImproper<NormalDistribution<1> >::getSampleMean() const {
  return mSampleMean;
}

double EstimatorBayesImproper<NormalDistribution<1> >::getSampleVariance()
  const {
  return mSampleVariance;
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
  mSampleMean = 0;
  mSampleVariance = 0;
}

void EstimatorBayesImproper<NormalDistribution<1> >::addPoint(const Point&
  point) {
  mNumPoints++;
  mSampleMean += 1.0 / mNumPoints * (point - mSampleMean);
  if (mNumPoints > 1)
    mSampleVariance += 1.0 / (mNumPoints - 1) * ((point - mSampleMean) *
      (point - mSampleMean) - mSampleVariance);
  if (mSampleVariance != 0.0) {
    mPostMeanDist.setDegrees(mNumPoints - 1);
    mPostMeanDist.setLocation(mSampleMean);
    mPostMeanDist.setScale(mSampleVariance / mNumPoints);
    mPostVarianceDist.setDegrees(mNumPoints - 1);
    mPostVarianceDist.setScale(mSampleVariance);
    mPostPredDist.setDegrees(mNumPoints - 1);
    mPostPredDist.setLocation(mSampleMean);
    mPostPredDist.setScale(mSampleVariance * (1 + 1.0 / mNumPoints));
    mValid = true;
  }
  else
    mValid = false;
}

void EstimatorBayesImproper<NormalDistribution<1> >::addPoints(const
  ConstPointIterator& itStart, const ConstPointIterator& itEnd) {
  for (ConstPointIterator it = itStart; it != itEnd; ++it)
    addPoint(*it);
}
