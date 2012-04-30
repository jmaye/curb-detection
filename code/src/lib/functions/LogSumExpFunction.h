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

/** \file LogSumExpFunction.h
    \brief This file defines the LogSumExpFunction class, which represents the
           log sum exp function
  */

#ifndef LOGSUMEXPFUNCTION_H
#define LOGSUMEXPFUNCTION_H

#include "functions/ContinuousFunction.h"

/** The LogSumExpFunction class represents the log sum exp function.
    \brief Log sum exp function
  */
template <typename X, size_t M> class LogSumExpFunction :
  public ContinuousFunction<double, X, M> {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  LogSumExpFunction(const LogSumExpFunction& other);
  /// Assignment operator
  LogSumExpFunction& operator = (const LogSumExpFunction& other);
  /** @}
    */

public:
  /** \name Types
    @{
    */
  /// Variable type
  typedef typename ContinuousFunction<double, X, M>::Domain VariableType;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  LogSumExpFunction();
  /// Destructor
  virtual ~LogSumExpFunction();
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

#include "functions/LogSumExpFunction.tpp"

#endif // LOGSUMEXPFUNCTION_H
