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

/** \file BinaryBufferWriter.h
    \brief This file defines the BinaryBufferWriter class which allows writing
           binary data to a byte buffer.
  */

#ifndef BINARYBUFFERWRITER_H
#define BINARYBUFFERWRITER_H

#include <vector>

#include "base/BinaryWriter.h"

/** The BinaryBufferWriter class allows for writing binary data to a byte
    buffer.
    \brief Binary buffer writer
  */
class BinaryBufferWriter :
  public BinaryWriter {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  BinaryBufferWriter(const BinaryBufferWriter& other);
  /// Assignment operator
  BinaryBufferWriter& operator = (const BinaryBufferWriter& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs object
  BinaryBufferWriter(size_t reservedSize = 1000);
  /// Destructor
  virtual ~BinaryBufferWriter();
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
  /// Returns the buffer
  const char* getBuffer() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Performs write on the stream
  virtual void write(const char* buffer, size_t numBytes);
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

#endif // BINARYBUFFERWRITER_H
