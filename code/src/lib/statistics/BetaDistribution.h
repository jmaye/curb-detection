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

/** \file BetaDistribution.h
    \brief This file defines the BetaDistribution class, which represents
           a beta distribution
  */

#ifndef BETADISTRIBUTION_H
#define BETADISTRIBUTION_H

#include "statistics/DirichletDistribution.h"
#include "exceptions/InvalidOperationException.h"

/** The BetaDistribution class represents a beta distribution,
    i.e., a continuous distribution that is a conjugate prior to the binomial or
    Bernoulli distribution.
    \brief Beta distribution
  */
class BetaDistribution :
  public DirichletDistribution<2> {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameters
  BetaDistribution(double alpha = 1.0, double beta = 1.0);
  /// Copy constructor
  BetaDistribution(const BetaDistribution& other);
  /// Assignment operator
  BetaDistribution& operator = (const BetaDistribution& other);
  /// Destructor
  virtual ~BetaDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the number of successes
  void setAlpha(double alpha);
  /// Returns the number of successes
  double getAlpha() const;
  /// Sets the number of failures
  void setBeta(double beta);
  /// Returns the number of failures
  double getBeta() const;
  /// Returns the mean of the distribution
  double getMean() const;
  /// Returns the mode of the distribution
  double getMode() const;
  /// Returns the variance of the distribution
  double getVariance() const;
  /// Access the cumulative distribution function at the given value
  double cdf(const double& value) const;
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

};

#include "statistics/BetaDistribution.tpp"

#endif // BETADISTRIBUTION_H
