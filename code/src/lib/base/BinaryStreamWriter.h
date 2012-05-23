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

/** \file BinaryStreamWriter.h
    \brief This file defines the BinaryStreamWriter class which allows writing
           binary data to a standard stream.
  */

#ifndef BINARYSTREAMWRITER_H
#define BINARYSTREAMWRITER_H

#include <iosfwd>

#include "base/BinaryWriter.h"

/** The BinaryStreamWriter class allows for writing binary data to a standard
    stream.
    \brief Stream buffer writer
  */
template <typename T> class BinaryStreamWriter :
  public BinaryWriter {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  BinaryStreamWriter(const BinaryStreamWriter& other);
  /// Assignment operator
  BinaryStreamWriter& operator = (const BinaryStreamWriter& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs object
  BinaryStreamWriter(T& stream);
  /// Destructor
  virtual ~BinaryStreamWriter();
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
  T& mStream;
  /** @}
    */

};

#include "base/BinaryStreamWriter.tpp"

#endif // BINARYSTREAMWRITER_H
