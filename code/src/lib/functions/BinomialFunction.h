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

/** \file BinomialFunction.h
    \brief This file defines the BinomialFunction class, which represents the
           binomial function
  */

#ifndef BINOMIALFUNCTION_H
#define BINOMIALFUNCTION_H

#include "functions/DiscreteFunction.h"
#include "exceptions/BadArgumentException.h"

/** The BinomialFunction class represents the binomial function.
    \brief Binomial function
  */
class BinomialFunction :
  public DiscreteFunction<size_t, size_t, 2> {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  BinomialFunction(const BinomialFunction& other);
  /// Assignment operator
  BinomialFunction& operator = (const BinomialFunction& other);
  /** @}
    */

public:
  /** \name Types
    @{
    */
  /// Variable type
  typedef DiscreteFunction<size_t, size_t, 2>::Domain VariableType;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  BinomialFunction();
  /// Destructor
  virtual ~BinomialFunction();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Access the function value for the given argument
  virtual size_t getValue(const VariableType& argument) const
    throw (BadArgumentException<VariableType>);
  /** @}
    */

protected:

};

#include "functions/BinomialFunction.tpp"

#endif // BINOMIALFUNCTION_H
