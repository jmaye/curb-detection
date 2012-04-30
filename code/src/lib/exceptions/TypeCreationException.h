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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file TypeCreationException.h
    \brief This file defines the TypeCreationException class, which
           is thrown whenever an exception occured when creating a type
  */

#ifndef TYPECREATIONEXCEPTION_H
#define TYPECREATIONEXCEPTION_H

#include <exception>
#include <string>

/** The class TypeCreationException represents any exceptions occuring when
    creating a type.
    \brief Type creation exception
  */
template <typename X> class TypeCreationException :
  public std::exception {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs exception from argument and string
  TypeCreationException(const X& argument, const std::string& msg, const
    std::string& filename = " ", size_t line = 0);
  /// Copy constructor
  TypeCreationException(const TypeCreationException& other) throw ();
  /// Assignment operator
  TypeCreationException& operator = (const TypeCreationException& other)
    throw ();
  /// Destructor
  virtual ~TypeCreationException() throw ();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Access the exception string
  virtual const char* what() const throw ();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Message in the exception
  std::string mMsg;
  /// Argument that causes the exception
  X mArg;
  /// Filename where the exception occurs
  std::string mFilename;
  /// Line number where the exception occurs
  size_t mLine;
  /** @}
    */

};

#include "exceptions/TypeCreationException.tpp"

#endif // TYPECREATIONEXCEPTION_H
