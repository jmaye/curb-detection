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

/** \file Factory.h
    \brief This file defines the Factory class, which implements the object
           factory design pattern
  */

#ifndef FACTORY_H
#define FACTORY_H

#include <map>

#include "base/Singleton.h"
#include "base/Serializable.h"

/** The class Factory implements the object factory design pattern.
    \brief Object factory design pattern
  */
template <typename T, typename C>
class Factory :
  public Singleton<Factory<T, C> >,
  public virtual Serializable {
/// Lets the access for Singleton class
friend class Singleton<Factory<T, C> >;
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  Factory(const Factory& other);
  /// Assignment operator
  Factory& operator = (const Factory& other);
  /** @}
    */

public:
  /** \name Accessors
    @{
    */
  /// Returns the number of registered types
  size_t getNumTypes() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Clear factory
  void clear();
  /// Create prototyped instance of the specified type
  C* create(const T& typeID) const;
  /// Register a type to the factory
  void registerType(const C* object, const T& typeID);
  /// Unregister a type from the factory
  void unregisterType(const T& typeID);
  /// Check if type is registered
  bool isRegistered(const T& typeID) const;
  /** @}
    */

protected:
  /** \name Protected constructors/destructor
    @{
    */
  /// Default constructor
  Factory();
  /// Destructor
  virtual ~Factory();
  /** @}
    */

  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream);
  /// Writes to standard output
  virtual void write(std::ostream& stream) const ;
  /// Reads from a file
  virtual void read(std::ifstream& stream);
  /// Writes to a file
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Contains the mapping between types and ID
  std::map<T, const C*> mTypesMap;
  /** @}
    */

};

#include "base/Factory.tpp"

#endif // FACTORY_H
