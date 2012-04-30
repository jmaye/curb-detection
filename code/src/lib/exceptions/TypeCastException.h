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

/** \file TypeCastException.h
    \brief This file defines the TypeCastException class, which represents wrong
           type casts
  */

#ifndef TYPECASTEXCEPTION_H
#define TYPECASTEXCEPTION_H

#include <stdexcept>
#include <string>

/** The class TypeCastException represents a wrong type cast.
    \brief Type cast exception
  */
class TypeCastException :
  public std::runtime_error {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Constructs exception from message
  TypeCastException(const std::string& msg = "");
  /// Copy constructor
  TypeCastException(const TypeCastException& other) throw ();
  /// Destructor
  virtual ~TypeCastException() throw ();
  /** @}
    */

protected:

};

#endif // TYPECASTEXCEPTION_H
