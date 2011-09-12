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

/** \file PoissonDistribution.h
    \brief This file defines the PoissonDistribution class, which represents a
           Poisson distribution
  */

#ifndef POISSONDISTRIBUTION_H
#define POISSONDISTRIBUTION_H

#include "statistics/DiscreteDistribution.h"
#include "statistics/SampleDistribution.h"
#include "base/Serializable.h"
#include "exceptions/BadArgumentException.h"

/** The PoissonDistribution class represents a Poisson distribution, i.e., a
    discrete distribution that models the probability of a given number of
    events occurring in a fixed interval of time and/or space with a known
    average rate.
    \brief Poisson distribution
  */
class PoissonDistribution :
  public DiscreteDistribution<size_t>,
  public SampleDistribution<size_t>,
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the distribution from the parameter
  PoissonDistribution(double mean = 1.0);
  /// Copy constructor
  PoissonDistribution(const PoissonDistribution& other);
  /// Assignment operator
  PoissonDistribution& operator = (const PoissonDistribution& other);
  /// Destructor
  virtual ~PoissonDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the event mean
  void setMean(double mean) throw (BadArgumentException<double>);
  /// Returns the event mean
  double getMean() const;
  /// Returns the median of the distribution
  double getMedian() const;
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
  /// Returns the KL-divergence with another distribution
  double KLDivergence(const PoissonDistribution& other) const;
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
  /// Event mean
  double mMean;
  /** @}
    */

};

#include "statistics/PoissonDistribution.tpp"

#endif // POISSONDISTRIBUTION_H
