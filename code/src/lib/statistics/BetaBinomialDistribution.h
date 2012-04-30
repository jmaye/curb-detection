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

/** \file BetaBinomialDistribution.h
    \brief This file defines the BetaBinomialDistribution class, which represents
           a beta binomial distribution
  */

#ifndef BETABINOMIALDISTRIBUTION_H
#define BETABINOMIALDISTRIBUTION_H

#include "statistics/DCMDistribution.h"

/** The BetaBinomialDistribution class represents a beta binomial distribution,
    which is the predictive distribution of a binomial random variable.
    \brief Beta binomial distribution
  */
class BetaBinomialDistribution :
  public DCMDistribution<2> {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameters
  BetaBinomialDistribution(size_t numTrials = 1, double alpha = 1.0,
    double beta = 1.0);
  /// Copy constructor
  BetaBinomialDistribution(const BetaBinomialDistribution& other);
  /// Assignment operator
  BetaBinomialDistribution& operator = (const BetaBinomialDistribution& other);
  /// Destructor
  virtual ~BetaBinomialDistribution();
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
  int getMode() const;
  /// Returns the variance of the distribution
  double getVariance() const;
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

#include "statistics/BetaBinomialDistribution.tpp"

#endif // BETABINOMIALDISTRIBUTION_H
