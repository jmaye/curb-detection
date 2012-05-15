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

/** \file LogGammaFunction.h
    \brief This file defines the LogGammaFunction class, which represents the
           log-gamma function
  */

#ifndef LOGGAMMAFUNCTION_H
#define LOGGAMMAFUNCTION_H

#include "functions/ContinuousFunction.h"
#include "functions/LogFactorialFunction.h"
#include "base/Serializable.h"

/** The LogGammaFunction class represents the log-gamma function for real
    numbers.
    \brief Log-gamma function for real numbers
  */
template <typename X = size_t> class LogGammaFunction :
  public ContinuousFunction<double, X>,
  public virtual Serializable {
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
  /// Constructs gamma function with parameter
  inline LogGammaFunction(size_t dim = 1.0);
  /// Copy constructor
  inline LogGammaFunction(const LogGammaFunction& other);
  /// Assignment operator
  inline LogGammaFunction& operator = (const LogGammaFunction& other);
  /// Destructor
  inline virtual ~LogGammaFunction();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the dimension
  inline size_t getDim() const;
  /// Sets the dimension
  inline void setDim(size_t dim);
  /// Access the function value for the given argument
  inline virtual double getValue(const VariableType& argument) const;
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

  /** \name Protected members
    @{
    */
  /// Dimensionality parameter
  size_t mDim;
  /** @}
    */

};

/** The LogGammaFunction class represents the log-gamma function for integer
    numbers
    \brief Log-gamma function for integer numbers
  */
template <> class LogGammaFunction<size_t> :
  public LogFactorialFunction {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  inline LogGammaFunction(const LogGammaFunction& other);
  /// Assignment operator
  inline LogGammaFunction& operator = (const LogGammaFunction& other);
  /** @}
    */

public:
  /** \name Types
    @{
    */
  /// Variable type
  typedef LogFactorialFunction::VariableType VariableType;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  inline LogGammaFunction();
  /// Destructor
  inline virtual ~LogGammaFunction();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Access the function value for the given argument
  inline virtual double getValue(const VariableType& argument) const;
  /** @}
    */

protected:

};

#include "functions/LogGammaFunction.tpp"

#endif // LOGGAMMAFUNCTION_H
