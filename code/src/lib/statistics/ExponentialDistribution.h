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

/** \file ExponentialDistribution.h
    \brief This file defines the ExponentialDistribution class, which represents
           an exponential distribution
  */

#ifndef EXPONENTIALDISTRIBUTION_H
#define EXPONENTIALDISTRIBUTION_H

#include "statistics/GammaDistribution.h"

/** The ExponentialDistribution class represents an exponential distribution,
    i.e., a continuous distribution that models the time between events in a
    Poisson process, or the time for a continuous process to change state. The
    events appear at a constant average rate.
    \brief Exponential distribution
  */
class ExponentialDistribution :
  public GammaDistribution<size_t> {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameter
  ExponentialDistribution(double rate = 1.0);
  /// Copy constructor
  ExponentialDistribution(const ExponentialDistribution& other);
  /// Assignment operator
  ExponentialDistribution& operator = (const ExponentialDistribution& other);
  /// Destructor
  virtual ~ExponentialDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the event rate
  void setRate(double rate);
  /// Returns the event rate
  double getRate() const;
  /// Returns the median of the distribution
  Median getMedian() const;
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

#include "statistics/ExponentialDistribution.tpp"

#endif // EXPONENTIALDISTRIBUTION_H
