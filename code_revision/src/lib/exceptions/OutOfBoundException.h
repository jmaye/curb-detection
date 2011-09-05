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

/** \file OutOfBoundException.h
    \brief This file defines the OutOfBoundException class, which represents any
           exceptions occuring when trying to access unallocated memory
  */

#ifndef OUTOFBOUNDEXCEPTION_H
#define OUTOFBOUNDEXCEPTION_H

#include <stdexcept>
#include <string>

/** The class OutOfBoundException represents any exceptions occuring when trying
    to access unallocated memory.
    \brief Out of bounds exception
  */
template <typename X> class OutOfBoundException :
  public std::exception {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs exception from argument and string
  OutOfBoundException(const X& argument, const std::string& msg, const
    std::string& filename = " ", size_t line = 0);
  /// Copy constructor
  OutOfBoundException(const OutOfBoundException& other) throw();
  /// Assignment operator
  OutOfBoundException& operator = (const OutOfBoundException& other) throw();
  /// Destructor
  virtual ~OutOfBoundException() throw();
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

#include "exceptions/OutOfBoundException.tpp"

#endif // OUTOFBOUNDEXCEPTION_H
