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

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename P>
Vertex<P>::Vertex(const Vertex<P>::PropertyType& property) :
  mProperty(property) {
}

template <typename P>
Vertex<P>::Vertex(const Vertex<P>::Vertex& other) :
  mProperty(other.mProperty) {
}

template <typename P>
Vertex<P>& Vertex<P>::operator = (const Vertex<P>& other) {
  if (this != &other) {
    mProperty = other.mProperty;
  }
  return *this;
}

template <typename P>
Vertex<P>::~Vertex() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename P>
void Vertex<P>::read(std::istream& stream) {
}

template <typename P>
void Vertex<P>::write(std::ostream& stream) const {
  stream << "property: " << mProperty;
}

template <typename P>
void Vertex<P>::read(std::ifstream& stream) {
}

template <typename P>
void Vertex<P>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename P>
void Vertex<P>::setProperty(const PropertyType& property) {
  mProperty = property;
}

template <typename P>
const typename Vertex<P>::PropertyType& Vertex<P>::getProperty() const {
  return mProperty;
}
