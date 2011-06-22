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
           exceptions where the input variables are out of bound
  */

#ifndef OUTOFBOUNDEXCEPTION_H
#define OUTOFBOUNDEXCEPTION_H

#include <stdexcept>
#include <string>

/** The class OutOfBoundException represents any
    exceptions where the input variables are out of bound
    \brief Out of bounds exception for input variables
  */
class OutOfBoundException : public std::range_error {
  /// Assignment operator
  OutOfBoundException& operator = (const OutOfBoundException &other);

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs exception from message
  OutOfBoundException(const std::string &msg = "");
  /// Copy constructor
  OutOfBoundException(const OutOfBoundException &other);
  /** @}
    */

protected:

};

#endif // OUTOFBOUNDEXCEPTION_H
