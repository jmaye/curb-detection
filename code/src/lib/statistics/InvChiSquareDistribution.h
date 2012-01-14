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

/** \file InvChiSquareDistribution.h
    \brief This file defines the InvChiSquareDistribution class, which
           represents a inverse chi-square distribution
  */

#ifndef INVCHISQUAREDISTRIBUTION_H
#define INVCHISQUAREDISTRIBUTION_H

#include "statistics/InvGammaDistribution.h"

/** The InvChiSquareDistribution class represents an inverse chi-square
    distribution.
    \brief Inverse chi-Square distribution
  */
class InvChiSquareDistribution :
  public InvGammaDistribution<> {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameters
  InvChiSquareDistribution(size_t degrees = 1);
  /// Copy constructor
  InvChiSquareDistribution(const InvChiSquareDistribution& other);
  /// Assignment operator
  InvChiSquareDistribution& operator = (const InvChiSquareDistribution& other);
  /// Destructor
  virtual ~InvChiSquareDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the degrees of freedom of the distribution
  void setDegrees(size_t degrees);
  /// Returns the degrees of freedom of the distribution
  size_t getDegrees() const;
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

#include "statistics/InvChiSquareDistribution.tpp"

#endif // INVCHISQUAREDISTRIBUTION_H
