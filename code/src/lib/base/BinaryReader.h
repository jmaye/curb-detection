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

/** \file BinaryReader.h
    \brief This file defines the BinaryReader class which is an interface
           for reading basic types from a binary stream
  */

#ifndef BINARYREADER_H
#define BINARYREADER_H

#include <stdint.h>
#include <stdlib.h>

/** The BinaryReader class is an interface for reading basic types from a binary
    stream.
    \brief Binary reader
  */
class BinaryReader {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  BinaryReader(const BinaryReader& other);
  /// Assignment operator
  BinaryReader& operator = (const BinaryReader& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  BinaryReader();
  /// Destructor
  virtual ~BinaryReader();
  /** @}
    */

  /** \name Operators
    @{
    */
  /// Reads 8-bit signed integer
  BinaryReader& operator >> (int8_t& value);
  /// Reads 8-bit unsigned integer
  BinaryReader& operator >> (uint8_t& value);
  /// Reads 16-bit signed integer
  BinaryReader& operator >> (int16_t& value);
  /// Reads 16-bit unsigned integer
  BinaryReader& operator >> (uint16_t& value);
  /// Reads 32-bit signed integer
  BinaryReader& operator >> (int32_t& value);
  /// Reads 32-bit unsigned integer
  BinaryReader& operator >> (uint32_t& value);
  /// Reads 64-bit signed integer
  BinaryReader& operator >> (int64_t& value);
  /// Reads 64-bit unsigned integer
  BinaryReader& operator >> (uint64_t& value);
  /// Reads 32-bit floating point
  BinaryReader& operator >> (float& value);
  /// Reads 64-bit floating point
  BinaryReader& operator >> (double& value);
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Perform read on the stream
  virtual void read(char* buffer, size_t numBytes) = 0;
  /** @}
    */

};

#endif // BINARYREADER_H
