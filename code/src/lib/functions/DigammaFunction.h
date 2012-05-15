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

/** \file DigammaFunction.h
    \brief This file defines the DigammaFunction class, which represents the
           digamma function
  */

#ifndef DIGAMMAFUNCTION_H
#define DIGAMMAFUNCTION_H

#include "functions/ContinuousFunction.h"
#include "exceptions/BadArgumentException.h"

/** The DigammaFunction class represents the digamma function for real numbers.
    \brief Digamma function for real numbers
  */
template <typename X = size_t> class DigammaFunction :
  public ContinuousFunction<double, X> {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  inline DigammaFunction(const DigammaFunction& other);
  /// Assignment operator
  inline DigammaFunction& operator = (const DigammaFunction& other);
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
  DigammaFunction();
  /// Destructor
  virtual ~DigammaFunction();
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

/** The DigammaFunction class represents the digamma function for integer.
    \brief Digamma function for integer numbers
  */
template <> class DigammaFunction<size_t> :
  public ContinuousFunction<double, size_t> {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  inline DigammaFunction(const DigammaFunction& other);
  /// Assignment operator
  inline DigammaFunction& operator = (const DigammaFunction& other);
  /** @}
    */

public:
  /** \name Types
    @{
    */
  /// Variable type
  typedef ContinuousFunction<double, size_t>::Domain VariableType;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  inline DigammaFunction();
  /// Destructor
  inline virtual ~DigammaFunction();
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

#include "functions/DigammaFunction.tpp"

#endif // DIGAMMAFUNCTION_H
