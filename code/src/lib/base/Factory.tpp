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

#include "exceptions/TypeCreationException.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename T, typename C>
Factory<T, C>::Factory() {
}

template <typename T, typename C>
Factory<T, C>::~Factory() {
  clear();
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename T, typename C>
void Factory<T, C>::read(std::istream& stream) {
}

template <typename T, typename C>
void Factory<T, C>::write(std::ostream& stream) const {
  for (auto it = mTypesMap.begin(); it != mTypesMap.end(); ++it)
    stream << it->first << std::endl;
}

template <typename T, typename C>
void Factory<T, C>::read(std::ifstream& stream) {
}

template <typename T, typename C>
void Factory<T, C>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename T, typename C>
size_t Factory<T, C>::getNumTypes() const {
  return mTypesMap.size();
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

template <typename T, typename C>
void Factory<T, C>::clear() {
  for (auto it = mTypesMap.begin(); it != mTypesMap.end(); ++it)
    unregisterType(it->first);
}

template <typename T, typename C>
C* Factory<T, C>::create(const T& typeID) const {
  auto it = mTypesMap.find(typeID);
  if (it != mTypesMap.end())
    return it->second->clone();
  else
    throw TypeCreationException<T>(typeID,
      "Factory<T, C>::create(): unregistered type");
}

template <typename T, typename C>
void Factory<T, C>::registerType(const C* object, const T& typeID) {
  if (mTypesMap.find(typeID) == mTypesMap.end())
    mTypesMap[typeID] = object;
  else
    throw TypeCreationException<T>(typeID,
      "Factory<T, C>::registerType(): already registered type");
}

template <typename T, typename C>
void Factory<T, C>::unregisterType(const T& typeID) {
  if (mTypesMap.find(typeID) == mTypesMap.end())
    throw TypeCreationException<T>(typeID,
      "Factory<T, C>::unregisterType(): unregistered type");
  else
    mTypesMap.erase(typeID);
}

template <typename T, typename C>
bool Factory<T, C>::isRegistered(const T& typeID) const {
  return (mTypesMap.find(typeID) != mTypesMap.end());
}
