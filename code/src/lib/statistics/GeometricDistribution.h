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
  public DiscreteDistribution<int>,
  public SampleDistribution<int>,
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameter
  inline GeometricDistribution(double probability = 0.5);
  /// Copy constructor
  inline GeometricDistribution(const GeometricDistribution& other);
  /// Assignment operator
  inline GeometricDistribution& operator = (const GeometricDistribution& other);
  /// Destructor
  inline ~GeometricDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the success probability
  inline void setProbability(double probability)
    throw (BadArgumentException<double>);
  /// Returns the success probability
  inline double getProbability() const;
  /// Returns the mean of the distribution
  inline Mean getMean() const;
  /// Returns the mode of the distribution
  inline Mode getMode() const;
  /// Returns the variance of the distribution
  inline Variance getVariance() const;
  /// Returns the probability mass function at a point
  inline virtual double pmf(const RandomVariable& value) const;
  /// Returns the log-probability mass function at a point
  inline double logpmf(const RandomVariable& value) const
    throw (BadArgumentException<RandomVariable>);
  /// Returns the cumulative mass function at a point
  inline double cdf(const RandomVariable& value) const;
  /// Access a sample drawn from the distribution
  inline virtual RandomVariable getSample() const;
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
  /// Success probability
  double mProbability;
  /** @}
    */

};

#include "statistics/GeometricDistribution.tpp"

#endif // GEOMETRICDISTRIBUTION_H
