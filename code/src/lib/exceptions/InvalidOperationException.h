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

/** \file InvalidOperationException.h
    \brief This file defines the InvalidOperationException class, which
           represents any exception occuring when an invalid operation is
           requested
  */

#ifndef INVALIDOPERATIONEXCEPTION_H
#define INVALIDOPERATIONEXCEPTION_H

#include <stdexcept>
#include <string>

/** The class InvalidOperationException represents any
    exceptions when the requested method will not be able to perform
    \brief Invalid operation requested
  */
class InvalidOperationException : public std::runtime_error {
  /// Assignment operator
  InvalidOperationException& operator =
    (const InvalidOperationException &other);

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs exception from message
  InvalidOperationException(const std::string &msg = "");
  /// Copy constructor
  InvalidOperationException(const InvalidOperationException &other);
  /** @}
    */

protected:

};

#endif // INVALIDOPERATIONEXCEPTION_H
