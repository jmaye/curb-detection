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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file CauchyDistribution.h
    \brief This file defines the CauchyDistribution class, which represents
           a Cauchy distribution
  */

#ifndef CAUCHYDISTRIBUTION_H
#define CAUCHYDISTRIBUTION_H

#include "statistics/ContinuousDistribution.h"
#include "statistics/SampleDistribution.h"
#include "base/Serializable.h"
#include "exceptions/BadArgumentException.h"
#include "exceptions/InvalidOperationException.h"

/** The CauchyDistribution class represents a Cauchy distribution.
    \brief Cauchy distribution
  */
class CauchyDistribution :
  public ContinuousDistribution<double>,
  public SampleDistribution<double>,
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameters
  CauchyDistribution(double location = 0.0, double scale = 1.0);
  /// Copy constructor
  CauchyDistribution(const CauchyDistribution& other);
  /// Assignment operator
  CauchyDistribution& operator = (const CauchyDistribution& other);
  /// Destructor
  virtual ~CauchyDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the location parameter
  void setLocation(double location);
  /// Returns the location parameter
  double getLocation() const;
  /// Sets the scale parameter
  void setScale(double scale) throw (BadArgumentException<double>);
  /// Returns the inverse scale parameter
  double getScale() const;
  /// Returns the mean of the distribution
  Mean getMean() const throw (InvalidOperationException);
  /// Returns the median of the distribution
  Median getMedian() const;
  /// Returns the mode of the distribution
  Mode getMode() const;
  /// Returns the variance of the distribution
  Variance getVariance() const throw (InvalidOperationException);
  /// Access the probablity density function at the given value
  virtual double pdf(const RandomVariable& value) const;
  /// Access the log-probablity density function at the given value
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
  /// Location parameter
  double mLocation;
  /// Scale parameter
  double mScale;
  /** @}
    */

};

#include "statistics/CauchyDistribution.tpp"

#endif // CAUCHYDISTRIBUTION_H
