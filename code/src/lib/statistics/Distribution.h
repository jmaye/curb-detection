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

/** \file Distribution.h
    \brief This file contains an interface to any kind of distributions
  */

#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include "functions/Function.h"

/** The Distribution class represents an interface to any kind of distributions.
    \brief Distribution
  */
template <typename X> class Distribution :
  public virtual Function<double, X> {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  Distribution(const Distribution& other);
  /// Assignment operator
  Distribution& operator = (const Distribution& other);
  /** @}
    */

public:
  /** \name Types
    @{
    */
  /// Random variable type
  typedef typename Function<double, X>::Domain RandomVariable;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  Distribution();
  /// Destructor
  virtual ~Distribution();
  /** @}
    */

protected:

};

#include "statistics/Distribution.tpp"

#endif // DISTRIBUTION_H
