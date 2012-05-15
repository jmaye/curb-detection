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

#include <sstream>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename X>
BadArgumentException<X>::BadArgumentException(const X& argument,
    const std::string& msg, const std::string& filename, size_t line) :
    mMsg(msg),
    mArg(argument),
    mFilename(filename),
    mLine(line) {
}

template <typename X>
BadArgumentException<X>::BadArgumentException(const BadArgumentException& other)
    throw() :
    mMsg(other.mMsg),
    mArg(other.mArg),
    mFilename(other.mFilename),
    mLine(other.mLine) {
}

template <typename X>
BadArgumentException<X>& BadArgumentException<X>::operator =
    (const BadArgumentException& other) throw() {
  if (this != &other) {
    mMsg = other.mMsg;
    mArg = other.mArg;
    mFilename = other.mFilename;
    mLine = other.mLine;
  }
  return *this;
}

template <typename X>
BadArgumentException<X>::~BadArgumentException() throw() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename X>
const char* BadArgumentException<X>::what() const throw() {
  std::stringstream stream;
  stream << mMsg << " [argument = " << mArg << "]";
  if (mFilename != " ")
    stream << " [file = " << mFilename << "]" << "[line = " << mLine << "]";
  return stream.str().c_str();
}
