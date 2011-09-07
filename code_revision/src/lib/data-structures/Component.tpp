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

template <typename V, typename P>
Component<V, P>::Component(const VertexType& vertex, const PropertyType&
  property) :
  mProperty(property) {
  mVertices.insert(vertex);
}

template <typename V, typename P>
Component<V, P>::Component(const PropertyType& property) :
  mProperty(property) {
}

template <typename V, typename P>
Component<V, P>::Component(const Component<V, P>::Component& other) :
  mVertices(other.mVertices),
  mProperty(other.mProperty) {
}

template <typename V, typename P>
Component<V, P>& Component<V, P>::operator = (const Component<V, P>& other) {
  if (this != &other) {
    mVertices = other.mVertices;
    mProperty = other.mProperty;
  }
  return *this;
}

template <typename V, typename P>
Component<V, P>::~Component() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename V, typename P>
void Component<V, P>::read(std::istream& stream) {
}

template <typename V, typename P>
void Component<V, P>::write(std::ostream& stream) const {
  stream << "vertices: " << mVertices << std::endl
    << "property: " << mProperty;
}

template <typename V, typename P>
void Component<V, P>::read(std::ifstream& stream) {
}

template <typename V, typename P>
void Component<V, P>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename V, typename P>
void Component<V, P>::insertVertex(const VertexType& vertex) {
  mVertices.insert(vertex);
}

template <typename V, typename P>
void Component<V, P>::removeVertex(const VertexType& vertex) {
  mVertices.remove(vertex);
}

template <typename V, typename P>
void Component<V, P>::merge(const Component<V, P>& other) {
  mVertices.merge(other.mVertices);
}

template <typename V, typename P>
void Component<V, P>::clear() {
  mVertices.clear();
}

template <typename V, typename P>
size_t Component<V, P>::getNumVertices() const {
  return mVertices.size();
}

template <typename V, typename P>
void Component<V, P>::setProperty(const PropertyType& property) {
  mProperty = property;
}

template <typename V, typename P>
const typename Component<V, P>::PropertyType& Component<V, P>::getProperty()
  const {
  return mProperty;
}
