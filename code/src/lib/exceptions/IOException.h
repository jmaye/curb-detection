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

/** \file IOException.h
    \brief This file defines the IOException class, which represents any
           exceptions occuring with input/output operations (e.g. files)
  */

#ifndef IOEXCEPTION_H
#define IOEXCEPTION_H

#include <stdexcept>
#include <string>

/** The class IOException represents any
    exceptions occuring with input/output operations (e.g. files)
    \brief Input/Output exception
  */
class IOException : public std::runtime_error {
  /// Assignment operator
  IOException& operator = (const IOException &other);

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs exception from message
  IOException(const std::string &msg = "");
  /// Copy constructor
  IOException(const IOException &other);
  /** @}
    */

protected:

};

#endif // IOEXCEPTION_H
