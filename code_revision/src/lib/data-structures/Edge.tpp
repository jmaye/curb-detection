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
Edge<V, P>::Edge(const Edge<V, P>::VertexDescriptorType& head, const
  Edge<V, P>::VertexDescriptorType& tail, const Edge<V, P>::PropertyType&
    property) :
  mHead(head),
  mTail(tail),
  mProperty(property) {
}

template <typename V, typename P>
Edge<V, P>::Edge(const Edge<V, P>::Edge& other) :
  mHead(other.mHead),
  mTail(other.mTail),
  mProperty(other.mProperty) {
}

template <typename V, typename P>
Edge<V, P>& Edge<V, P>::operator = (const Edge<V, P>& other) {
  if (this != &other) {
    mHead = other.mHead;
    mTail = other.mTail;
    mProperty = other.mProperty;
  }
  return *this;
}

template <typename V, typename P>
Edge<V, P>::~Edge() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename V, typename P>
void Edge<V, P>::read(std::istream& stream) {
}

template <typename V, typename P>
void Edge<V, P>::write(std::ostream& stream) const {
  stream << "head node: " << mHead << std::endl
    << "tail node: " << mTail << std::endl
    << "property: " << mProperty;
}

template <typename V, typename P>
void Edge<V, P>::read(std::ifstream& stream) {
}

template <typename V, typename P>
void Edge<V, P>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename V, typename P>
void Edge<V, P>::setHead(const VertexDescriptorType& head) {
  mHead = head;
}

template <typename V, typename P>
const typename Edge<V, P>::VertexDescriptorType& Edge<V, P>::getHead() const {
  return mHead;
}

template <typename V, typename P>
void Edge<V, P>::setTail(const VertexDescriptorType& tail) {
  mTail = tail;
}

template <typename V, typename P>
const typename Edge<V, P>::VertexDescriptorType& Edge<V, P>::getTail() const {
  return mTail;
}

template <typename V, typename P>
void Edge<V, P>::setProperty(const PropertyType& property) {
  mProperty = property;
}

template <typename V, typename P>
const typename Edge<V, P>::PropertyType& Edge<V, P>::getProperty() const {
  return mProperty;
}
