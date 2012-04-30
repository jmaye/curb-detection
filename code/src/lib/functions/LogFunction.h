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

/** \file LogFunction.h
    \brief This file defines the LogFunction class, which represents the
           log function
  */

#ifndef LOGFUNCTION_H
#define LOGFUNCTION_H

#include "exceptions/BadArgumentException.h"
#include "functions/ContinuousFunction.h"

/** The LogFunction class represents the log function.
    \brief Log function
  */
template <typename X = double> class LogFunction :
  public ContinuousFunction<double, X> {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  LogFunction(const LogFunction& other);
  /// Assignment operator
  LogFunction& operator = (const LogFunction& other);
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
  LogFunction();
  /// Destructor
  virtual ~LogFunction();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Access the function value for the given argument
  virtual double getValue(const VariableType& argument) const
    throw (BadArgumentException<VariableType>);
  /** @}
    */

protected:

};

#include "functions/LogFunction.tpp"

#endif // LOGFUNCTION_H
