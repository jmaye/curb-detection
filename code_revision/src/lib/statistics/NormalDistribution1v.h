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

/** \file NormalDistribution1v.h
    \brief This file defines the univariate normal distribution
  */

#include "statistics/ContinuousDistribution.h"
#include "statistics/SampleDistribution.h"
#include "base/Serializable.h"
#include "exceptions/BadArgumentException.h"

/** The NormalDistribution1v class represents a univariate normal distribution.
    \brief Univariate normal distribution
  */
template <> class NormalDistribution<1> :
  public ContinuousDistribution<double>,
  public SampleDistribution<double>,
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs a normal distribution from the parameters
  NormalDistribution(double mean = 0.0, double variance = 1.0);
  /// Copy constructor
  NormalDistribution(const NormalDistribution<1>& other);
  /// Assignment operator
  NormalDistribution& operator = (const NormalDistribution<1>& other);
  /// Destructor
  virtual ~NormalDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the mean of the distribution
  void setMean(double mean);
  /// Returns the mean of the distribution
  double getMean() const;
  /// Sets the variance of the distribution
  void setVariance(double variance) throw (BadArgumentException<double>);
  /// Returns the variance of the distribution
  double getVariance() const;
  /// Returns the precision of the distribution
  double getPrecision() const;
  /// Returns the standard deviation of the distribution
  double getStandardDeviation() const;
  /// Returns the normalizer of the distribution
  double getNormalizer() const;
  /// Returns the median of the distribution
  double getMedian() const;
  /// Returns the mode of the distribution
  double getMode() const;
  /// Access the probability density function at the given value
  virtual double pdf(const double& value) const;
  /// Access the log-probability density function at the given value
  double logpdf(const double& value) const;
  /// Access the cumulative density function at the given value
  double cdf(const double& value) const;
  /// Access a sample drawn from the distribution
  virtual double getSample() const;
  /// Returns the KL-divergence with another distribution
  double KLDivergence(const NormalDistribution<1>& other) const;
  /// Returns the squared Mahalanobis distance from a given value
  double mahalanobisDistance(const double& value) const;
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
  /// Mean of the normal distribution
  double mMean;
  /// Variance of the normal distribution
  double mVariance;
  /// Precision of the normal distribution
  double mPrecision;
  /// Standard deviation of the normal distribution
  double mStandardDeviation;
  /// Normalizer of the normal distribution
  double mNormalizer;
  /** @}
    */

};

//#include "statistics/NormalDistribution1v.tpp"
