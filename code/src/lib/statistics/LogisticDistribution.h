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

/** \file LogisticDistribution.h
    \brief This file defines the logistic distribution
  */

#ifndef LOGISTICDISTRIBUTION_H
#define LOGISTICDISTRIBUTION_H

#include "statistics/ContinuousDistribution.h"
#include "statistics/SampleDistribution.h"
#include "base/Serializable.h"

/** The LogisticDistribution class represents a logistic distribution.
    \brief Logistic distribution
  */
class LogisticDistribution :
  public ContinuousDistribution<double>,
  public SampleDistribution<double>,
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the distribution from the parameters
  LogisticDistribution(double location = 0.0, double scale = 1.0);
  /// Copy constructor
  LogisticDistribution(const LogisticDistribution& other);
  /// Assignment operator
  LogisticDistribution& operator = (const LogisticDistribution& other);
  /// Destructor
  virtual ~LogisticDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the location of the distribution
  void setLocation(double scale);
  /// Returns the location of the distribution
  double getLocation() const;
  /// Sets the scale of the distribution
  void setScale(double scale);
  /// Returns the scale of the distribution
  double getScale() const;
  /// Returns the inverse scale of the distribution
  double getInverseScale() const;
  /// Returns the mean of the distribution
  Mean getMean() const;
  /// Returns the median of the distribution
  Median getMedian() const;
  /// Returns the mode of the distribution
  Mode getMode() const;
  /// Returns the variance of the distribution
  Variance getVariance() const;
  /// Access the probability density function at the given value
  virtual double pdf(const RandomVariable& value) const;
  /// Access the log-probability density function at the given value
  double logpdf(const RandomVariable& value) const;
  /// Access the cumulative density function at the given value
  double cdf(const RandomVariable& value) const;
  /// Access a sample drawn from the distribution
  virtual RandomVariable getSample() const;
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
  /// Location of the distribution
  double mLocation;
  /// Scale of the distribution
  double mScale;
  /// Inverse scale of the distribution
  double mInverseScale;
  /** @}
    */

};

#include "statistics/LogisticDistribution.tpp"

#endif // LOGISTICDISTRIBUTION_H
