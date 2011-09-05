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

/** \file EstimatorBayesImproperNormal1v.h
    \brief This file implements a Bayesian estimator for univariate normal
           distributions with improper prior.
  */

#include "statistics/NormalDistribution.h"
#include "statistics/StudentDistribution.h"
#include "statistics/ScaledInvChiSquareDistribution.h"

#include <vector>

/** The class EstimatorBayesImproper is implemented for univariate normal
    distributions.
    \brief Univariate normal distribution Bayesian estimator with improper prior
  */
template <> class EstimatorBayesImproper<NormalDistribution<1> > :
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  EstimatorBayesImproper();
  /// Copy constructor
  EstimatorBayesImproper(const EstimatorBayesImproper<NormalDistribution<1> >&
    other);
  /// Assignment operator
  EstimatorBayesImproper<NormalDistribution<1> >& operator =
    (const EstimatorBayesImproper<NormalDistribution<1> >& other);
  /// Destructor
  virtual ~EstimatorBayesImproper();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the posterior marginal mean distribution
  const StudentDistribution<1>& getPostMeanDist() const;
  /// Returns the posterior marginal variance distribution
  const ScaledInvChiSquareDistribution& getPostVarianceDist() const;
  /// Returns the posterior predictive distribution
  const StudentDistribution<1>& getPostPredDist() const;
  /// Returns the sample mean
  double getSampleMean() const;
  /// Returns the sample variance
  double getSampleVariance() const;
  /// Returns the number of points
  size_t getNumPoints() const;
  /// Returns the validity state of the estimator
  bool getValid() const;
  /// Add a point to the estimator
  void addPoint(double point);
  /// Add points to the estimator
  void addPoints(const std::vector<double>& points);
  /// Reset the estimator
  void reset();
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream);
  /// Writes to standard output
  virtual void write(std::ostream& stream) const;
  /// Reads from a file
  virtual void read(std::ifstream& stream);
  /// Writes to a file
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Posterior marginal mean distribution
  StudentDistribution<1> mPostMeanDist;
  /// Posterior marginal variance distribution
  ScaledInvChiSquareDistribution mPostVarianceDist;
  /// Posterior predictive distribution
  StudentDistribution<1> mPostPredDist;
  /// Sample mean
  double mSampleMean;
  /// Sample variance
  double mSampleVariance;
  /// Number of points in the estimator
  size_t mNumPoints;
  /// Valid flag
  bool mValid;
  /** @}
    */

};

#include "statistics/EstimatorBayesImproperNormal1v.tpp"
