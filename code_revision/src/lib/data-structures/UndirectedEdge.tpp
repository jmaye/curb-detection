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
UndirectedEdge<V, P>::UndirectedEdge(const V& head, const V& tail, const P&
  property) :
  mHead(head),
  mTail(tail),
  mProperty(property) {
}

template <typename V, typename P>
UndirectedEdge<V, P>::UndirectedEdge(const UndirectedEdge<V, P>::UndirectedEdge&
  other) :
  mHead(other.mHead),
  mTail(other.mTail),
  mProperty(other.mProperty) {
}

template <typename V, typename P>
UndirectedEdge<V, P>& UndirectedEdge<V, P>::operator = (const
  UndirectedEdge<V, P>& other) {
  if (this != &other) {
    mHead = other.mHead;
    mTail = other.mTail;
    mProperty = other.mProperty;
  }
  return *this;
}

template <typename V, typename P>
UndirectedEdge<V, P>::~UndirectedEdge() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename V, typename P>
void UndirectedEdge<V, P>::read(std::istream& stream) {
}

template <typename V, typename P>
void UndirectedEdge<V, P>::write(std::ostream& stream) const {
  stream << "head node: " << mHead << std::endl
    << "tail node: " << mTail << std::endl
    << "property: " << mProperty;
}

template <typename V, typename P>
void UndirectedEdge<V, P>::read(std::ifstream& stream) {
}

template <typename V, typename P>
void UndirectedEdge<V, P>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename V, typename P>
void UndirectedEdge<V, P>::setHead(const V& head) {
  mHead = head;
}

template <typename V, typename P>
const V& UndirectedEdge<V, P>::getHead() const {
  return mHead;
}

template <typename V, typename P>
void UndirectedEdge<V, P>::setTail(const V& tail) {
  mTail = tail;
}

template <typename V, typename P>
const V& UndirectedEdge<V, P>::getTail() const {
  return mTail;
}

template <typename V, typename P>
void UndirectedEdge<V, P>::setProperty(const P& property) {
  mProperty = property;
}

template <typename V, typename P>
const P& UndirectedEdge<V, P>::getProperty() const {
  return mProperty;
}

template <typename V, typename P>
P& UndirectedEdge<V, P>::getProperty() {
  return mProperty;
}
