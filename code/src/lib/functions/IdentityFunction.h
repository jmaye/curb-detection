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

/** \file IdentityFunction.h
    \brief This file defines the IdentityFunction class, which represents the
           log function
  */

#ifndef IDENTITYFUNCTION_H
#define IDENTITYFUNCTION_H

#include "functions/Function.h"

template <typename Y, typename X = Y> class IdentityFunction;

/** The IdentityFunction class represents the identity function.
    \brief Identity function
  */
template <typename X> class IdentityFunction<X, X> :
  public Function<typename Function<X, X>::Domain, X> {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  IdentityFunction(const IdentityFunction& other);
  /// Assignment operator
  IdentityFunction& operator = (const IdentityFunction& other);
  /** @}
    */

public:
  /** \name Types
    @{
    */
  /// Variable type
  typedef typename Function<X, X>::Domain VariableType;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  IdentityFunction();
  /// Destructor
  virtual ~IdentityFunction();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Access the function value for the given argument
  virtual VariableType getValue(const VariableType& argument) const;
  /** @}
    */

protected:

};

#include "functions/IdentityFunction.tpp"

#endif // IDENTITYFUNCTION_H
