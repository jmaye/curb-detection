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

/** \file BinaryWriter.h
    \brief This file defines the BinaryWriter class which is an interface
           for writing basic types to a binary stream
  */

#ifndef BINARYWRITER_H
#define BINARYWRITER_H

#include <stdint.h>
#include <stdlib.h>

/** The BinaryWriter class is an interface for writing basic types to a binary
    stream.
    \brief Binary writer
  */
class BinaryWriter {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  BinaryWriter(const BinaryWriter& other);
  /// Assignment operator
  BinaryWriter& operator = (const BinaryWriter& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  BinaryWriter();
  /// Destructor
  virtual ~BinaryWriter();
  /** @}
    */

  /** \name Operators
    @{
    */
  /// Writes 8-bit signed integer
  BinaryWriter& operator << (int8_t value);
  /// Writes 8-bit unsigned integer
  BinaryWriter& operator << (uint8_t value);
  /// Writes 16-bit signed integer
  BinaryWriter& operator << (int16_t value);
  /// Writes 16-bit unsigned integer
  BinaryWriter& operator << (uint16_t value);
  /// Writes 32-bit signed integer
  BinaryWriter& operator << (int32_t value);
  /// Writes 32-bit unsigned integer
  BinaryWriter& operator << (uint32_t value);
  /// Writes 64-bit signed integer
  BinaryWriter& operator << (int64_t value);
  /// Writes 64-bit unsigned integer
  BinaryWriter& operator << (uint64_t value);
  /// Writes 32-bit floating point
  BinaryWriter& operator << (float value);
  /// Writes 64-bit floating point
  BinaryWriter& operator << (double value);
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Writes a buffer of byte
  virtual void writeBuffer(const char* buffer, ssize_t numBytes) = 0;
  /** @}
    */

};

#endif // BINARYWRITER
