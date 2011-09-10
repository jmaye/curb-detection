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

DEMGraph::DEMGraph(const Grid<double, Cell, 2>& dem) {
  for (size_t i = 0; i < dem.getNumCells(0); ++i)
    for (size_t j = 0; j < dem.getNumCells(1); ++j) {
      const Cell& cell =
        dem[(Grid<double, Cell, 2>::Index() << i, j).finished()];
      if (cell.getValid()) {
        if ((i + 1) < dem.getNumCells(0)) {
          const Cell& cellDown =
            dem[(Grid<double, Cell, 2>::Index() << i + 1, j).finished()];
          if (cellDown.getHeightEstimator().getValid()) {
  //          edgeSet.insert(Edge(dem(i, j).compare(dem(i + 1, j)),
  //            std::make_pair(i, j), std::make_pair(i + 1, j)));
          }
        }
        if ((j + 1) < dem.getNumCells(1)) {
          const Cell& cellRight =
            dem[(Grid<double, Cell, 2>::Index() << i, j + 1).finished()];
          if (cellRight.getHeightEstimator().getValid()) {
//            edgeSet.insert(Edge(dem(i, j).compare(dem(i, j + 1)),
//              std::make_pair(i, j), std::make_pair(i, j + 1)));
          }
        }
      }
    }
}

DEMGraph::DEMGraph(const DEMGraph::DEMGraph& other) :
  mEdges(other.mEdges) {
}

DEMGraph& DEMGraph::operator = (const DEMGraph& other) {
  if (this != &other) {
    mEdges = other.mEdges;
  }
  return *this;
}

DEMGraph::~DEMGraph() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void DEMGraph::read(std::istream& stream) {
}

void DEMGraph::write(std::ostream& stream) const {
  stream << "vertices: " << std::endl;
  for (ConstVertexIterator it = getVertexBegin(); it != getVertexEnd(); ++it)
    stream << it->second << std::endl;
  stream << "edges: " << std::endl;
  for (ConstEdgeIterator it = getEdgeBegin(); it != getEdgeEnd(); ++it)
    stream << it->second << std::endl;
}

void DEMGraph::read(std::ifstream& stream) {
}

void DEMGraph::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

typename DEMGraph::ConstVertexIterator
DEMGraph::getVertexBegin() const {
  return mVertices.begin();
}

typename DEMGraph::VertexIterator DEMGraph::getVertexBegin() {
  return mVertices.begin();
}

typename DEMGraph::ConstVertexIterator
DEMGraph::getVertexEnd() const {
  return mVertices.end();
}

typename DEMGraph::VertexIterator DEMGraph::getVertexEnd() {
  return mVertices.end();
}

typename DEMGraph::ConstEdgeIterator DEMGraph::getEdgeBegin()
  const {
  return mEdges.begin();
}

typename DEMGraph::EdgeIterator DEMGraph::getEdgeBegin() {
  return mEdges.begin();
}

typename DEMGraph::ConstEdgeIterator DEMGraph::getEdgeEnd()
  const {
  return mEdges.end();
}

typename DEMGraph::EdgeIterator DEMGraph::getEdgeEnd() {
  return mEdges.end();
}

size_t DEMGraph::getNumVertices() const {
  return mVertices.size();
}

size_t DEMGraph::getNumEdges() const {
  return mEdges.size();
}

E DEMGraph::getEdge(ConstEdgeIterator it) const throw
  (OutOfBoundException<size_t>) {
  for (ConstEdgeIterator itE = getEdgeBegin(); itE != getEdgeEnd(); ++itE)
    if (itE == it)
      return it->first;
  throw OutOfBoundException<size_t>(0,
    "DEMGraph::getEdge(): invalid iterator", __FILE__, __LINE__);
}

E DEMGraph::getEdge(const V& tail, const V& head) const
  throw (OutOfBoundException<V>) {
  for (ConstEdgeIterator it = getEdgeBegin(); it != getEdgeEnd(); ++it) {
    E edge = getEdge(it);
    if (getTailVertex(edge) == tail && getHeadVertex(edge) == head)
      return edge;
  }
  throw OutOfBoundException<V>(tail,
    "DEMGraph::getEdge(): invalid edge", __FILE__, __LINE__);
}

bool DEMGraph::containsVertex(const V& vertex) const {
  return findVertex(vertex) != getVertexEnd();
}

bool DEMGraph::containsEdge(const V& tail, const V& head) const {
  for (ConstEdgeIterator it = getEdgeBegin(); it != getEdgeEnd(); ++it) {
    E edge = getEdge(it);
    if ((getTailVertex(edge) == tail && getHeadVertex(edge) == head) ||
      (getTailVertex(edge) == head && getHeadVertex(edge) == tail))
      return true;
  }
  return false;
}

typename DEMGraph::EdgeIterator
DEMGraph::findEdge(const E& edge) const {
  return ((EdgeContainer&)mEdges).find(edge);
}

typename DEMGraph::VertexIterator
DEMGraph::findVertex(const V& vertex) const {
  return ((VertexContainer&)mVertices).find(vertex);
}

V DEMGraph::getVertex(ConstVertexIterator it) const throw
  (OutOfBoundException<size_t>) {
  for (ConstVertexIterator itE = getVertexBegin(); itE != getVertexEnd(); ++itE)
    if (itE == it)
      return it->first;
  throw OutOfBoundException<size_t>(0,
    "DEMGraph::getVertex(): invalid iterator", __FILE__, __LINE__);
}

void DEMGraph::setEdgeProperty(const E& edge, const P& property) {
  getEdgeProperty(edge) = property;
}

P& DEMGraph::getEdgeProperty(const E& edge) throw
  (OutOfBoundException<E>) {
  EdgeIterator it = findEdge(edge);
  if (it == getEdgeEnd())
    throw OutOfBoundException<E>(edge,
      "DEMGraph::getEdgeProperty(): invalid edge", __FILE__, __LINE__);
  else
    return it->second.getProperty();
}

const P& DEMGraph::getEdgeProperty(const E& edge) const throw
  (OutOfBoundException<E>) {
  EdgeIterator it = findEdge(edge);
  if (it == getEdgeEnd())
    throw OutOfBoundException<E>(edge,
      "DEMGraph::getEdgeProperty(): invalid edge", __FILE__, __LINE__);
  else
    return it->second.getProperty();
}

void DEMGraph::setVertexProperty(const V& vertex, const T& property) {
  getVertexProperty(vertex) = property;
}

T& DEMGraph::getVertexProperty(const V& vertex) throw
  (OutOfBoundException<V>) {
  VertexIterator it = findVertex(vertex);
  if (it == getVertexEnd())
    throw OutOfBoundException<V>(vertex,
      "DEMGraph::getVertexProperty(): invalid vertex", __FILE__,
       __LINE__);
  else
    return it->second.getProperty();
}

const T& DEMGraph::getVertexProperty(const V& vertex) const throw
  (OutOfBoundException<V>) {
  VertexIterator it = findVertex(vertex);
  if (it == getVertexEnd())
    throw OutOfBoundException<V>(vertex,
      "DEMGraph::getVertexProperty(): invalid vertex", __FILE__,
       __LINE__);
  else
    return it->second.getProperty();
}

V DEMGraph::getTailVertex(const E& edge) const {
  return findEdge(edge)->second.getTail();
}

V DEMGraph::getHeadVertex(const E& edge) const {
  return findEdge(edge)->second.getHead();
}

void DEMGraph::insertEdge(const V& tail, const V& head) {
  if (!containsEdge(tail, head)) {
    if (!containsVertex(tail))
      mVertices[tail] = Vertex<T>();
    if (!containsVertex(head))
      mVertices[head] = Vertex<T>();
    mEdges[getNumEdges()] = UndirectedEdge<V, P>(head, tail);
  }
}

void DEMGraph::removeEdge(ConstEdgeIterator& it) {
  mEdges.erase(it);
}

void DEMGraph::clearEdges() {
  mEdges.clear();
}

void DEMGraph::insertVertex(const V& vertex) {
  if (!containsVertex(vertex))
    mVertices[vertex] = Vertex<T>();
}

void DEMGraph::removeVertex(ConstVertexIterator& it) {
  mVertices.erase(it);
}

void DEMGraph::clearVertices() {
  mVertices.clear();
}

void DEMGraph::clear() {
  clearEdges();
  clearVertices();
}
