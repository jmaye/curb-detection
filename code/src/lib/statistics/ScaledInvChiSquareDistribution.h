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

/** \file ScaledInvChiSquareDistribution.h
    \brief This file defines the ScaledInvChiSquareDistribution class, which
           represents a scaled inverse chi-square distribution
  */

#ifndef SCALEDINVCHISQUAREDISTRIBUTION_H
#define SCALEDINVCHISQUAREDISTRIBUTION_H

#include "statistics/InvGammaDistribution.h"

/** The ScaledInvChiSquareDistribution class represents an inverse chi-square
    distribution.
    \brief Scaled inverse chi-Square distribution
  */
class ScaledInvChiSquareDistribution :
  public InvGammaDistribution<> {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameters
  inline ScaledInvChiSquareDistribution(size_t degrees = 1, double scale = 1.0);
  /// Copy constructor
  inline ScaledInvChiSquareDistribution(const ScaledInvChiSquareDistribution&
    other);
  /// Assignment operator
  inline ScaledInvChiSquareDistribution& operator = (const
    ScaledInvChiSquareDistribution& other);
  /// Destructor
  inline virtual ~ScaledInvChiSquareDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the scale of the distribution
  inline void setScale(double scale);
  /// Returns the scale of the distribution
  inline double getScale() const;
  /// Sets the degrees of freedom of the distribution
  inline void setDegrees(size_t degrees);
  /// Returns the degrees of freedom of the distribution
  inline size_t getDegrees() const;
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

#include "statistics/ScaledInvChiSquareDistribution.tpp"

#endif // SCALEDINVCHISQUAREDISTRIBUTION_H
