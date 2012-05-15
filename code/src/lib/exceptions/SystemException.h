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

/** \file SystemException.h
    \brief This file defines the SystemException class, which represents
           low-level system exceptions.
  */

#ifndef SYSTEMEXCEPTION_H
#define SYSTEMEXCEPTION_H

#include <stdexcept>
#include <string>

/** The class SystemException represents system exceptions.
    \brief System exceptions
  */
class SystemException :
  public std::exception {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Constructs exception
  SystemException(int errNo, const std::string& msg = "", const
    std::string& filename = " ", size_t line = 0);
  /// Copy constructor
  SystemException(const SystemException& other) throw ();
  /// Assignment operator
  SystemException& operator = (const SystemException& other) throw();
  /// Destructor
  virtual ~SystemException() throw ();
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
  /// Errno related to the system error
  int mErrno;
  /// Filename where the exception occurs
  std::string mFilename;
  /// Line number where the exception occurs
  size_t mLine;
  /** @}
    */

};

#endif // SYSTEMEXCEPTION_H
