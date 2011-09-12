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

/** \file BinomialDistribution.h
    \brief This file defines the BinomialDistribution class, which represents a
           binomial distribution
  */

#ifndef BINOMIALDISTRIBUTION_H
#define BINOMIALDISTRIBUTION_H

#include "statistics/MultinomialDistribution.h"

/** The BinomialDistribution class represents a binomial distribution, i.e., the
    discrete distribution of the number of successes in N independent Bernoulli
    draws, each with the same probability of success p.
    \brief Binomial distribution
  */
class BinomialDistribution :
  public MultinomialDistribution<2> {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the distribution from the parameter
  BinomialDistribution(size_t numTrials = 1, double successProbability = 0.5);
  /// Copy constructor
  BinomialDistribution(const BinomialDistribution& other);
  /// Assignment operator
  BinomialDistribution& operator = (const BinomialDistribution& other);
  /// Destructor
  virtual ~BinomialDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the success probability
  void setSuccessProbability(double successProbability);
  /// Returns the success probability
  double getSuccessProbability() const;
  /// Returns the mean of the distribution
  double getMean() const;
  /// Returns the median of the distribution
  double getMedian() const;
  /// Returns the mode of the distribution
  double getMode() const;
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

#include "statistics/BinomialDistribution.tpp"

#endif // BINOMIALDISTRIBUTION_H
