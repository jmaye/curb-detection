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

/** \file BadArgumentException.h
    \brief This file defines the BadArgumentException class, which
           is thrown whenever the arguments of a function are invalid
  */

#ifndef BADARGUMENTEXCEPTION_H
#define BADARGUMENTEXCEPTION_H

#include <exception>
#include <string>

/** The class BadArgumentException represents any
    exceptions occuring when the arguments passed to a function are invalid.
    \brief Bad argument exception
  */
template <typename X> class BadArgumentException :
  public std::exception {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs exception from argument and string
  BadArgumentException(const X& argument, const std::string& msg, const
    std::string& filename = " ", size_t line = 0);
  /// Copy constructor
  BadArgumentException(const BadArgumentException& other) throw();
  /// Assignment operator
  BadArgumentException& operator = (const BadArgumentException& other) throw();
  /// Destructor
  virtual ~BadArgumentException() throw();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Access the exception string
  virtual const char* what() const throw();
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

#include "exceptions/BadArgumentException.tpp"

#endif // BADARGUMENTEXCEPTION_H
