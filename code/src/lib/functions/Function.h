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

/** \file Function.h
    \brief This file defines the class Fonction, which is an interface for any
           kind of functions
  */

#ifndef FUNCTION_H
#define FUNCTION_H

#include <cstdlib>

/** The Function class is an interface to any kind of mathematical functions
    \brief Function
  */
template <typename Y, typename X> class Function {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  Function(const Function& other);
  /// Assignment operator
  Function& operator = (const Function& other);
  /** @}
    */

public:
  /** \name Types
    @{
    */
  /// Domain
  typedef X Domain;
  /// Codomain
  typedef Y Codomain;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  Function();
  /// Destructor
  virtual ~Function();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Access the function value for the given argument
  virtual Y getValue(const X& argument) const = 0;
  /// Access the function value for the given argument
  virtual Y operator()(const X& argument) const;
  /** @}
    */

protected:

};

#include "functions/Function.tpp"

#endif // FUNCTION_H
