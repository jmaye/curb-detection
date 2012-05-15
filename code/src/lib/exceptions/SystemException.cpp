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

#include "exceptions/SystemException.h"

#include <cstring>

#include <sstream>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

SystemException::SystemException(int errNo, const
    std::string& msg, const std::string& filename, size_t line) :
    mMsg(msg),
    mErrno(errNo),
    mFilename(filename),
    mLine(line) {
}

SystemException::SystemException(const SystemException& other) throw() :
    mMsg(other.mMsg),
    mErrno(other.mErrno),
    mFilename(other.mFilename),
    mLine(other.mLine) {
}

SystemException& SystemException::operator =
    (const SystemException& other) throw() {
  if (this != &other) {
    mMsg = other.mMsg;
    mErrno = other.mErrno;
    mFilename = other.mFilename;
    mLine = other.mLine;
  }
  return *this;
}

SystemException::~SystemException() throw() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

const char* SystemException::what() const throw() {
  std::stringstream stream;
  stream << mMsg << ": " << strerror(mErrno);
  if (mFilename != " ")
    stream << " [file = " << mFilename << "]" << "[line = " << mLine << "]";
  return stream.str().c_str();
}
