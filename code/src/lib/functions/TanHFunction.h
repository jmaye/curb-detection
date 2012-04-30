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

/** \file TanHFunction.h
    \brief This file defines the TanHFunction class, which represents the
           tanh function
  */

#ifndef TANHFUNCTION_H
#define TANHFUNCTION_H

#include "functions/ContinuousFunction.h"

/** The TanHFunction class represents the tanh function.
    \brief Tanh function
  */
template <typename X = double> class TanHFunction :
  public ContinuousFunction<double, X> {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  TanHFunction(const TanHFunction& other);
  /// Assignment operator
  TanHFunction& operator = (const TanHFunction& other);
  /** @}
    */

public:
  /** \name Types
    @{
    */
  /// Variable type
  typedef typename ContinuousFunction<double, X>::Domain VariableType;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  TanHFunction();
  /// Destructor
  virtual ~TanHFunction();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Access the function value for the given argument
  virtual double getValue(const VariableType& argument) const;
  /** @}
    */

protected:

};

#include "functions/TanHFunction.tpp"

#endif // TANHFUNCTION_H
