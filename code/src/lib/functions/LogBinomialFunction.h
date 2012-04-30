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

/** \file LogBinomialFunction.h
    \brief This file defines the LogBinomialFunction class, which represents the
           log-binomial function
  */

#ifndef LOGBINOMIALFUNCTION_H
#define LOGBINOMIALFUNCTION_H

#include "functions/DiscreteFunction.h"
#include "exceptions/BadArgumentException.h"

/** The LogBinomialFunction class represents the binomial function.
    \brief Binomial function
  */
class LogBinomialFunction :
  public DiscreteFunction<double, size_t, 2> {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  LogBinomialFunction(const LogBinomialFunction& other);
  /// Assignment operator
  LogBinomialFunction& operator = (const LogBinomialFunction& other);
  /** @}
    */

public:
  /** \name Types
    @{
    */
  /// Variable type
  typedef DiscreteFunction<double, size_t, 2>::Domain VariableType;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  LogBinomialFunction();
  /// Destructor
  virtual ~LogBinomialFunction();
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

#include "functions/LogBinomialFunction.tpp"

#endif // LOGBINOMIALFUNCTION_H
