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

/** \file BernoulliDistribution.h
    \brief This file defines the BernoulliDistribution class, which represents a
           Bernoulli distribution
  */

#ifndef BERNOULLIDISTRIBUTION_H
#define BERNOULLIDISTRIBUTION_H

#include "statistics/CategoricalDistribution.h"

/** The class BernoulliDistribution represents a Bernoulli distribution, i.e.,
    the discrete distribution of a random event with success or failure.
    \brief Bernoulli distribution
  */
class BernoulliDistribution :
  public CategoricalDistribution<2> {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the distribution from the parameter
  BernoulliDistribution(double successProbability = 0.5);
  /// Copy constructor
  BernoulliDistribution(const BernoulliDistribution& other);
  /// Assignment operator
  BernoulliDistribution& operator = (const BernoulliDistribution& other);
  /// Destructor
  virtual ~BernoulliDistribution();
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

#include "statistics/BernoulliDistribution.tpp"

#endif // BERNOULLIDISTRIBUTION_H
