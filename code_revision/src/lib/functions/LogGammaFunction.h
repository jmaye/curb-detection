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
#include "exceptions/BadArgumentException.h"
#include "base/Serializable.h"

/** The LogGammaFunction class represents the log-gamma function for real
    numbers.
    \brief Log-gamma function for real numbers
  */
template <typename X = size_t> class LogGammaFunction :
  public ContinuousFunction<double, X>,
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs gamma function with parameter
  LogGammaFunction(size_t dim = 1.0);
  /// Copy constructor
  LogGammaFunction(const LogGammaFunction<X>& other);
  /// Assignment operator
  LogGammaFunction& operator = (const LogGammaFunction<X>& other);
  /// Destructor
  virtual ~LogGammaFunction();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the dimension
  size_t getDim() const;
  /// Sets the dimension
  void setDim(size_t dim);
  /// Access the function value for the given argument
  virtual double getValue(const X& argument) const;
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream);
  /// Writes to standard output
  virtual void write(std::ostream& stream) const;
  /// Reads from a file
  virtual void read(std::ifstream& stream);
  /// Writes to a file
  virtual void write(std::ofstream& stream) const;
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
  inline virtual double getValue(const size_t& argument) const
    throw (BadArgumentException<size_t>);
  /** @}
    */

protected:

};

#include "functions/LogGammaFunction.tpp"

#endif // LOGGAMMAFUNCTION_H
