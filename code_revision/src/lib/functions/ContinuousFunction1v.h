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

/** \file ContinuousFunction1v.h
    \brief This file contains an interface to the univariate continuous
           functions
  */

#ifndef CONTINUOUSFUNCTION1V_H
#define CONTINUOUSFUNCTION1V_H

#include "functions/Function.h"

template <typename Y, typename X, size_t M = 1, size_t N = 1>
  class ContinuousFunction;

/** The ContinuousFunction1v class represents an interface to the univariate
    continuous functions.
    \brief Univariate continuous function
  */
template <typename Y, typename X> class ContinuousFunction<Y, X> :
  public virtual Function<Y, X> {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  ContinuousFunction(const ContinuousFunction<Y, X>& other);
  /// Assignment operator
  ContinuousFunction& operator = (const ContinuousFunction<Y, X>& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  ContinuousFunction();
  /// Destructor
  virtual ~ContinuousFunction();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Access the function's number of variables
  virtual size_t getNumVariables() const;
  /** @}
    */

protected:

};

#include "functions/ContinuousFunction1v.tpp"

#endif // CONTINUOUSFUNCTION1V_H
