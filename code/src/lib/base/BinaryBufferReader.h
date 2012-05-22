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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file BinaryBufferReader.h
    \brief This file defines the BinaryBufferReader class which allows reading
           binary data from a byte buffer.
  */

#ifndef BINARYBUFFERREADER_H
#define BINARYBUFFERREADER_H

#include <vector>

#include "base/BinaryReader.h"

/** The BinaryBufferReader class allows for reading binary data from a byte
    buffer.
    \brief Binary buffer reader
  */
class BinaryBufferReader :
  public BinaryReader {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  BinaryBufferReader(const BinaryBufferReader& other);
  /// Assignment operator
  BinaryBufferReader& operator = (const BinaryBufferReader& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs object
  BinaryBufferReader(const char* buffer, size_t size);
  /// Destructor
  virtual ~BinaryBufferReader();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Get the position in the buffer
  size_t getPos() const;
  /// Set the position in the buffer
  void setPos(size_t pos);
  /// Returns the buffer size
  size_t getBufferSize() const;
  /// Returns the remaining size to read
  size_t getReadLeft() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Perform read on the stream
  virtual void read(char* buffer, size_t numBytes);
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Associated byte array
  std::vector<char> mBuffer;
  /// Position of the reader
  size_t mPos;
  /** @}
    */

};

#endif // BINARYBUFFERREADER_H
