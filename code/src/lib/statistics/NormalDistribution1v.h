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

#include <tuple>

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
  /** \name Types
    @{
    */
  /// Precision type
  typedef Variance Precision;
  /// Standard deviation type
  typedef Variance Std;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs a normal distribution from the parameters
  inline NormalDistribution(Mean mean = 0.0, Variance variance = 1.0);
  /// Constructs a normal distribution from the parameters
  inline NormalDistribution(const std::tuple<Mean, Variance>& parameters);
  /// Copy constructor
  inline NormalDistribution(const NormalDistribution& other);
  /// Assignment operator
  inline NormalDistribution& operator = (const NormalDistribution& other);
  /// Destructor
  inline virtual ~NormalDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the mean of the distribution
  inline void setMean(Mean mean);
  /// Returns the mean of the distribution
  inline Mean getMean() const;
  /// Sets the variance of the distribution
  inline void setVariance(Variance variance)
    throw (BadArgumentException<Variance>);
  /// Returns the variance of the distribution
  inline Variance getVariance() const;
  /// Returns the precision of the distribution
  inline Precision getPrecision() const;
  /// Returns the standard deviation of the distribution
  inline Std getStandardDeviation() const;
  /// Returns the normalizer of the distribution
  inline double getNormalizer() const;
  /// Returns the median of the distribution
  inline Median getMedian() const;
  /// Returns the mode of the distribution
  inline Mode getMode() const;
  /// Access the probability density function at the given value
  inline virtual double pdf(const RandomVariable& value) const;
  /// Access the log-probability density function at the given value
  inline double logpdf(const RandomVariable& value) const;
  /// Access the cumulative density function at the given value
  inline double cdf(const RandomVariable& value) const;
  /// Access a sample drawn from the distribution
  inline virtual RandomVariable getSample() const;
  /// Returns the KL-divergence with another distribution
  inline double KLDivergence(const NormalDistribution<1>& other) const;
  /// Returns the squared Mahalanobis distance from a given value
  inline double mahalanobisDistance(const RandomVariable& value) const;
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  inline virtual void read(std::istream& stream);
  /// Writes to standard output
  inline virtual void write(std::ostream& stream) const;
  /// Reads from a file
  inline virtual void read(std::ifstream& stream);
  /// Writes to a file
  inline virtual void write(std::ofstream& stream) const;
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

#include "statistics/NormalDistribution1v.tpp"
