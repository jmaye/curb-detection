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

template <typename V, typename E, typename T, typename P>
Graph<V, E, T, P>::Graph() {
}

template <typename V, typename E, typename T, typename P>
Graph<V, E, T, P>::Graph(const Graph<V, E, T, P>::Graph& other) :
  mVertices(other.mVertices),
  mEdges(other.mEdges) {
}

template <typename V, typename E, typename T, typename P>
Graph<V, E, T, P>& Graph<V, E, T, P>::operator = (const Graph<V, E, T, P>&
  other) {
  if (this != &other) {
    mVertices = other.mVertices;
    mEdges = other.mEdges;
  }
  return *this;
}

template <typename V, typename E, typename T, typename P>
Graph<V, E, T, P>::~Graph() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename V, typename E, typename T, typename P>
void Graph<V, E, T, P>::read(std::istream& stream) {
}

template <typename V, typename E, typename T, typename P>
void Graph<V, E, T, P>::write(std::ostream& stream) const {
  stream << "vertices: " << std::endl;
  for (ConstVertexIterator it = getVertexBegin(); it != getVertexEnd(); ++it)
    stream << it->second << std::endl;
  stream << "edges: " << std::endl;
  for (ConstEdgeIterator it = getEdgeBegin(); it != getEdgeEnd(); ++it)
    stream << it->second << std::endl;
}

template <typename V, typename E, typename T, typename P>
void Graph<V, E, T, P>::read(std::ifstream& stream) {
}

template <typename V, typename E, typename T, typename P>
void Graph<V, E, T, P>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename V, typename E, typename T, typename P>
typename Graph<V, E, T, P>::ConstVertexIterator
Graph<V, E, T, P>::getVertexBegin() const {
  return mVertices.begin();
}

template <typename V, typename E, typename T, typename P>
typename Graph<V, E, T, P>::VertexIterator Graph<V, E, T, P>::getVertexBegin() {
  return mVertices.begin();
}

template <typename V, typename E, typename T, typename P>
typename Graph<V, E, T, P>::ConstVertexIterator
Graph<V, E, T, P>::getVertexEnd() const {
  return mVertices.end();
}

template <typename V, typename E, typename T, typename P>
typename Graph<V, E, T, P>::VertexIterator Graph<V, E, T, P>::getVertexEnd() {
  return mVertices.end();
}

template <typename V, typename E, typename T, typename P>
typename Graph<V, E, T, P>::ConstEdgeIterator Graph<V, E, T, P>::getEdgeBegin()
  const {
  return mEdges.begin();
}

template <typename V, typename E, typename T, typename P>
typename Graph<V, E, T, P>::EdgeIterator Graph<V, E, T, P>::getEdgeBegin() {
  return mEdges.begin();
}

template <typename V, typename E, typename T, typename P>
typename Graph<V, E, T, P>::ConstEdgeIterator Graph<V, E, T, P>::getEdgeEnd()
  const {
  return mEdges.end();
}

template <typename V, typename E, typename T, typename P>
typename Graph<V, E, T, P>::EdgeIterator Graph<V, E, T, P>::getEdgeEnd() {
  return mEdges.end();
}

template <typename V, typename E, typename T, typename P>
size_t Graph<V, E, T, P>::getNumVertices() const {
  return mVertices.size();
}

template <typename V, typename E, typename T, typename P>
size_t Graph<V, E, T, P>::getNumEdges() const {
  return mEdges.size();
}

template <typename V, typename E, typename T, typename P>
E Graph<V, E, T, P>::getEdge(ConstEdgeIterator it) const throw
  (OutOfBoundException<size_t>) {
  for (ConstEdgeIterator itE = getEdgeBegin(); itE != getEdgeEnd(); ++itE)
    if (itE == it)
      return it->first;
  throw OutOfBoundException<size_t>(0,
    "Graph<V, E, T, P>::getEdge(): invalid iterator", __FILE__, __LINE__);
}

template <typename V, typename E, typename T, typename P>
E Graph<V, E, T, P>::getEdge(const V& tail, const V& head) const
  throw (OutOfBoundException<V>) {
  for (ConstEdgeIterator it = getEdgeBegin(); it != getEdgeEnd(); ++it) {
    E edge = getEdge(it);
    if (getTailVertex(edge) == tail && getHeadVertex(edge) == head)
      return edge;
  }
  throw OutOfBoundException<V>(tail,
    "Graph<V, E, T, P>::getEdge(): invalid edge", __FILE__, __LINE__);
}

template <typename V, typename E, typename T, typename P>
bool Graph<V, E, T, P>::containsVertex(const V& vertex) const {
  return findVertex(vertex) != getVertexEnd();
}

template <typename V, typename E, typename T, typename P>
bool Graph<V, E, T, P>::containsEdge(const V& tail, const V& head) const {
  for (ConstEdgeIterator it = getEdgeBegin(); it != getEdgeEnd(); ++it) {
    E edge = getEdge(it);
    if ((getTailVertex(edge) == tail && getHeadVertex(edge) == head) ||
      (getTailVertex(edge) == head && getHeadVertex(edge) == tail))
      return true;
  }
  return false;
}

template <typename V, typename E, typename T, typename P>
typename Graph<V, E, T, P>::EdgeIterator
Graph<V, E, T, P>::findEdge(const E& edge) const {
  return ((EdgeContainer&)mEdges).find(edge);
}

template <typename V, typename E, typename T, typename P>
typename Graph<V, E, T, P>::VertexIterator
Graph<V, E, T, P>::findVertex(const V& vertex) const {
  return ((VertexContainer&)mVertices).find(vertex);
}

template <typename V, typename E, typename T, typename P>
V Graph<V, E, T, P>::getVertex(ConstVertexIterator it) const throw
  (OutOfBoundException<size_t>) {
  for (ConstVertexIterator itE = getVertexBegin(); itE != getVertexEnd(); ++itE)
    if (itE == it)
      return it->first;
  throw OutOfBoundException<size_t>(0,
    "Graph<V, E, T, P>::getVertex(): invalid iterator", __FILE__, __LINE__);
}

template <typename V, typename E, typename T, typename P>
void Graph<V, E, T, P>::setEdgeProperty(const E& edge, const P& property) {
  getEdgeProperty(edge) = property;
}

template <typename V, typename E, typename T, typename P>
P& Graph<V, E, T, P>::getEdgeProperty(const E& edge) throw
  (OutOfBoundException<E>) {
  EdgeIterator it = findEdge(edge);
  if (it == getEdgeEnd())
    throw OutOfBoundException<E>(edge,
      "Graph<V, E, T, P>::getEdgeProperty(): invalid edge", __FILE__, __LINE__);
  else
    return it->second.getProperty();
}

template <typename V, typename E, typename T, typename P>
const P& Graph<V, E, T, P>::getEdgeProperty(const E& edge) const throw
  (OutOfBoundException<E>) {
  EdgeIterator it = findEdge(edge);
  if (it == getEdgeEnd())
    throw OutOfBoundException<E>(edge,
      "Graph<V, E, T, P>::getEdgeProperty(): invalid edge", __FILE__, __LINE__);
  else
    return it->second.getProperty();
}

template <typename V, typename E, typename T, typename P>
void Graph<V, E, T, P>::setVertexProperty(const V& vertex, const T& property) {
  getVertexProperty(vertex) = property;
}

template <typename V, typename E, typename T, typename P>
T& Graph<V, E, T, P>::getVertexProperty(const V& vertex) throw
  (OutOfBoundException<V>) {
  VertexIterator it = findVertex(vertex);
  if (it == getVertexEnd())
    throw OutOfBoundException<V>(vertex,
      "Graph<V, E, T, P>::getVertexProperty(): invalid vertex", __FILE__,
       __LINE__);
  else
    return it->second.getProperty();
}

template <typename V, typename E, typename T, typename P>
const T& Graph<V, E, T, P>::getVertexProperty(const V& vertex) const throw
  (OutOfBoundException<V>) {
  VertexIterator it = findVertex(vertex);
  if (it == getVertexEnd())
    throw OutOfBoundException<V>(vertex,
      "Graph<V, E, T, P>::getVertexProperty(): invalid vertex", __FILE__,
       __LINE__);
  else
    return it->second.getProperty();
}

template <typename V, typename E, typename T, typename P>
V Graph<V, E, T, P>::getTailVertex(const E& edge) const {
  return findEdge(edge)->second.getTail();
}

template <typename V, typename E, typename T, typename P>
V Graph<V, E, T, P>::getHeadVertex(const E& edge) const {
  return findEdge(edge)->second.getHead();
}

template <typename V, typename E, typename T, typename P>
void Graph<V, E, T, P>::insertEdge(const V& tail, const V& head) {
  if (!containsEdge(tail, head)) {
    if (!containsVertex(tail))
      mVertices[tail] = Vertex<T>();
    if (!containsVertex(head))
      mVertices[head] = Vertex<T>();
    mEdges[getNumEdges()] = UndirectedEdge<V, P>(head, tail);
  }
}

template <typename V, typename E, typename T, typename P>
void Graph<V, E, T, P>::removeEdge(ConstEdgeIterator& it) {
  mEdges.erase(it);
}

template <typename V, typename E, typename T, typename P>
void Graph<V, E, T, P>::clearEdges() {
  mEdges.clear();
}

template <typename V, typename E, typename T, typename P>
void Graph<V, E, T, P>::insertVertex(const V& vertex) {
  if (!containsVertex(vertex))
    mVertices[vertex] = Vertex<T>();
}

template <typename V, typename E, typename T, typename P>
void Graph<V, E, T, P>::removeVertex(ConstVertexIterator& it) {
  mVertices.erase(it);
}

template <typename V, typename E, typename T, typename P>
void Graph<V, E, T, P>::clearVertices() {
  mVertices.clear();
}

template <typename V, typename E, typename T, typename P>
void Graph<V, E, T, P>::clear() {
  clearEdges();
  clearVertices();
}
