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

/** \file BinaryStreamReader.h
    \brief This file defines the BinaryStreamReader class which allows reading
           binary data from a standard stream
  */

#ifndef BINARYSTREAMREADER_H
#define BINARYSTREAMREADER_H

#include <iosfwd>

#include "base/BinaryReader.h"

/** The BinaryStreamReader class allows for reading binary data from a standard
    stream
    \brief Binary stream reader
  */
template <typename T> class BinaryStreamReader :
  public BinaryReader {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  BinaryStreamReader(const BinaryStreamReader& other);
  /// Assignment operator
  BinaryStreamReader& operator = (const BinaryStreamReader& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs object
  BinaryStreamReader(T& stream);
  /// Destructor
  virtual ~BinaryStreamReader();
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
  /// Stream object
  T& mStream;
  /** @}
    */

};

#include "base/BinaryStreamReader.tpp"

#endif // BINARYSTREAMREADER_H
