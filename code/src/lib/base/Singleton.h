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

/** \file Singleton.h
    \brief This file defines the Singleton class, which implements the singleton
           design pattern
  */

#ifndef SINGLETON_H
#define SINGLETON_H

/** The class Singleton implements the singleton design pattern.
    \brief Singleton design pattern
  */
template <class C> class Singleton {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  Singleton(const Singleton& other);
  /// Assignment operator
  Singleton& operator = (const Singleton& other);
  /** @}
    */

public:
  /** \name Accessors
    @{
    */
  /// Access the static instance
  static C& getInstance();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Check if the object exists
  static bool exists();
  /** @}
    */

protected:
  /** \name Protected constructors/destructor
    @{
    */
  /// Default constructor
  Singleton();
  /// Destructor
  virtual ~Singleton();
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Instance of the object
  static C* instance;
  /** @}
    */

};

#include "base/Singleton.tpp"

#endif
