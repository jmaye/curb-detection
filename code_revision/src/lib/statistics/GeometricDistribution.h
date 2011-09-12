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

/** \file GeometricDistribution.h
    \brief This file defines the GeometricDistribution class, which represents a
           geometric distribution
  */

#ifndef GEOMETRICDISTRIBUTION_H
#define GEOMETRICDISTRIBUTION_H

#include "statistics/DiscreteDistribution.h"
#include "statistics/SampleDistribution.h"
#include "base/Serializable.h"
#include "exceptions/BadArgumentException.h"

/** The GeometricDistribution class represents a geometric distribution, i.e.,
    a discrete distribution which models the number of Bernoulli trial before
    a success occurs, or the number of Bernoulli trials before a discrete
    process changes state.
    \brief Geometric distribution
  */
class GeometricDistribution :
  public DiscreteDistribution<size_t>,
  public SampleDistribution<size_t>,
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameter
  GeometricDistribution(double successProbability = 0.5);
  /// Copy constructor
  GeometricDistribution(const GeometricDistribution& other);
  /// Assignment operator
  GeometricDistribution& operator = (const GeometricDistribution& other);
  /// Destructor
  ~GeometricDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the success probability
  void setSuccessProbability(double successProbability)
    throw (BadArgumentException<double>);
  /// Returns the success probability
  double getSuccessProbability() const;
  /// Returns the mean of the distribution
  double getMean() const;
  /// Returns the mode of the distribution
  double getMode() const;
  /// Returns the variance of the distribution
  double getVariance() const;
  /// Returns the probability mass function at a point
  virtual double pmf(const size_t& value) const;
  /// Returns the log-probability mass function at a point
  double logpmf(const size_t& value) const;
  /// Returns the cumulative mass function at a point
  double cdf(const size_t& value) const;
  /// Access a sample drawn from the distribution
  virtual size_t getSample() const;
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
  /// Success probability
  double mSuccessProbability;
  /** @}
    */

};

#include "statistics/GeometricDistribution.tpp"

#endif // GEOMETRICDISTRIBUTION_H
