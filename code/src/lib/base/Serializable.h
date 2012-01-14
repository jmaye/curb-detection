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

/** \file Serializable.h
    \brief This file defines the Serializable class, which is an interface to
           serializable types
  */

#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <iostream>
#include <fstream>

/** The class Serializable is an interface to serializable types.
    \brief Serializable class
  */
class Serializable {
  /** \name Stream methods
    @{
    */
  /// Writes object to standard output
  friend std::ostream& operator << (std::ostream& stream,
    const Serializable& obj);
  /// Reads object from standard input
  friend std::istream& operator >> (std::istream& stream, Serializable& obj);
  /// Writes object to file
  friend std::ofstream& operator << (std::ofstream& stream,
    const Serializable& obj);
  /// Reads object from file
  friend std::ifstream& operator >> (std::ifstream& stream, Serializable& obj);
  /** @}
    */

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  Serializable(const Serializable& other);
  /// Assignment operator
  Serializable& operator = (const Serializable& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  Serializable();
  /// Destructor
  virtual ~Serializable();
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream) = 0;
  /// Writes to standard output
  virtual void write(std::ostream& stream) const = 0;
  /// Reads from a file
  virtual void read(std::ifstream& stream) = 0;
  /// Writes to a file
  virtual void write(std::ofstream& stream) const = 0;
  /** @}
    */

};

#endif // SERIALIZABLE_H
