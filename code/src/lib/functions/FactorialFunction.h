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

/** \file FactorialFunction.h
    \brief This file defines the FactorialFunction class, which represents the
           factorial function
  */

#ifndef FACTORIALFUNCTION_H
#define FACTORIALFUNCTION_H

#include "functions/DiscreteFunction.h"

/** The FactorialFunction class represents the factorial function.
    \brief Factorial function
  */
class FactorialFunction :
  public DiscreteFunction<size_t, size_t> {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  inline FactorialFunction(const FactorialFunction& other);
  /// Assignment operator
  inline FactorialFunction& operator = (const FactorialFunction& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  inline FactorialFunction();
  /// Destructor
  inline virtual ~FactorialFunction();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Access the function value for the given argument
  inline virtual size_t getValue(const size_t& argument) const;
  /** @}
    */

protected:

};

#include "functions/FactorialFunction.tpp"

#endif // FACTORIALFUNCTION_H
