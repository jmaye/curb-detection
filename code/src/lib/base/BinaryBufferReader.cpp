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

#include "base/BinaryBufferReader.h"

#include <cstring>

#include "exceptions/OutOfBoundException.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

BinaryBufferReader::BinaryBufferReader(const char* buffer, size_t size) :
    mPos(0) {
  mBuffer.reserve(size);
  mBuffer.assign(buffer, buffer + size);
}

BinaryBufferReader::~BinaryBufferReader() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

size_t BinaryBufferReader::getPos() const {
  return mPos;
}

void BinaryBufferReader::setPos(size_t pos) {
  if (pos >= mBuffer.size())
    throw OutOfBoundException<size_t>(mPos,
      "BinaryBufferReader::setPos(): invalid position");
  mPos = pos;
}

size_t BinaryBufferReader::getBufferSize() const {
  return mBuffer.size();
}

size_t BinaryBufferReader::getReadLeft() const {
  return mBuffer.size() - mPos;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void BinaryBufferReader::read(char* buffer, size_t numBytes) {
  if (mPos + numBytes > mBuffer.size())
    throw OutOfBoundException<size_t>(mPos,
      "BinaryBufferReader::readBuffer(): no more bytes available");
  memcpy(buffer, &mBuffer[mPos], numBytes);
  mPos += numBytes;
}
