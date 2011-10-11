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

/** \file NegativeBinomialDistribution.h
    \brief This file defines the NegativeBinomialDistribution class, which
           represents a negative binomial distribution
  */

#ifndef NEGATIVEBINOMIALDISTRIBUTION_H
#define NEGATIVEBINOMIALDISTRIBUTION_H

#include "statistics/NegativeMultinomialDistribution.h"

/** The NegativeBinomialDistribution class represents a negative binomial
    distribution, i.e., the discrete distribution that models the number of
    successes in a sequence of categorical trials before a specified
    (non-random) number of failures occurs.
    \brief Negative binomial distribution
  */
class NegativeBinomialDistribution :
  public NegativeMultinomialDistribution<2> {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the distribution from the parameter
  inline NegativeBinomialDistribution(size_t numTrials = 1, double
    successProbability = 0.5);
  /// Copy constructor
  inline NegativeBinomialDistribution(const NegativeBinomialDistribution&
    other);
  /// Assignment operator
  inline NegativeBinomialDistribution& operator =
    (const NegativeBinomialDistribution& other);
  /// Destructor
  inline virtual ~NegativeBinomialDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the success probability
  inline void setSuccessProbability(double successProbability);
  /// Returns the success probability
  inline double getSuccessProbability() const;
  /// Returns the mean of the distribution
  inline double getMean() const;
  /// Returns the mode of the distribution
  inline double getMode() const;
  /// Returns the variance of the distribution
  inline double getVariance() const;
  /// Access a sample drawn from the distribution
  inline virtual Eigen::Matrix<size_t, 2, 1> getSample() const;
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

};

#include "statistics/NegativeBinomialDistribution.tpp"

#endif // NEGATIVEBINOMIALDISTRIBUTION_H
