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
  for (size_t i = 0; i < dem.getNumCells()(0); ++i)
    for (size_t j = 0; j < dem.getNumCells()(1); ++j) {
      const Cell& cell =
        dem[(Grid<double, Cell, 2>::Index() << i, j).finished()];
      if (cell.getHeightEstimator().getValid()) {
        size_t cellIdx = dem.computeLinearIndex(
          (Grid<double, Cell, 2>::Index() << i, j).finished());
        mVertices[cellIdx] = cellIdx;
        NormalDistribution<1> cellDist(cell.getHeightEstimator().getMean(),
          cell.getHeightEstimator().getVariance());
        if ((i + 1) < dem.getNumCells()(0)) {
          const Cell& cellDown =
            dem[(Grid<double, Cell, 2>::Index() << i + 1, j).finished()];
          if (cellDown.getHeightEstimator().getValid()) {
            NormalDistribution<1> cellDownDist(
              cellDown.getHeightEstimator().getMean(),
              cellDown.getHeightEstimator().getVariance());
            mEdges.push_back(UndirectedEdge<V, P>(cellIdx,
              dem.computeLinearIndex(
              (Grid<double, Cell, 2>::Index() << i + 1, j).finished()),
              cellDist.KLDivergence(cellDownDist) +
              cellDownDist.KLDivergence(cellDist)));
          }
        }
        if ((j + 1) < dem.getNumCells()(1)) {
          const Cell& cellRight =
            dem[(Grid<double, Cell, 2>::Index() << i, j + 1).finished()];
          if (cellRight.getHeightEstimator().getValid()) {
            NormalDistribution<1> cellRightDist(
              cellRight.getHeightEstimator().getMean(),
              cellRight.getHeightEstimator().getVariance());
            mEdges.push_back(UndirectedEdge<V, P>(cellIdx,
              dem.computeLinearIndex(
              (Grid<double, Cell, 2>::Index() << i, j + 1).finished()),
              cellDist.KLDivergence(cellRightDist) +
              cellRightDist.KLDivergence(cellDist)));
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
  stream << "edges: " << std::endl;
  for (ConstEdgeIterator it = getEdgeBegin(); it != getEdgeEnd(); ++it)
    stream << *it << std::endl;
}

void DEMGraph::read(std::ifstream& stream) {
}

void DEMGraph::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

DEMGraph::ConstEdgeIterator DEMGraph::getEdgeBegin() const {
  return mEdges.begin();
}

DEMGraph::EdgeIterator DEMGraph::getEdgeBegin() {
  return mEdges.begin();
}

DEMGraph::ConstEdgeIterator DEMGraph::getEdgeEnd() const {
  return mEdges.end();
}

DEMGraph::EdgeIterator DEMGraph::getEdgeEnd() {
  return mEdges.end();
}

size_t DEMGraph::getNumEdges() const {
  return mEdges.size();
}

DEMGraph::E DEMGraph::getEdge(ConstEdgeIterator it) const throw
  (OutOfBoundException<size_t>) {
  if (it >= getEdgeEnd())
    throw OutOfBoundException<size_t>(0,
      "DEMGraph::getEdge(): invalid iterator", __FILE__, __LINE__);
  else
    return it - getEdgeBegin();
}

DEMGraph::EdgeIterator DEMGraph::findEdge(const E& edge) const {
  if (getEdgeBegin() + edge >= getEdgeEnd())
    return ((EdgeContainer&)mEdges).end();
  else
    return ((EdgeContainer&)mEdges).begin() + edge;
}

void DEMGraph::setEdgeProperty(const E& edge, const P& property) {
  getEdgeProperty(edge) = property;
}

DEMGraph::P& DEMGraph::getEdgeProperty(const E& edge) throw
  (OutOfBoundException<E>) {
  EdgeIterator it = findEdge(edge);
  if (it == getEdgeEnd())
    throw OutOfBoundException<E>(edge,
      "DEMGraph::getEdgeProperty(): invalid edge", __FILE__, __LINE__);
  else
    return it->getProperty();
}

const DEMGraph::P& DEMGraph::getEdgeProperty(const E& edge) const throw
  (OutOfBoundException<E>) {
  EdgeIterator it = findEdge(edge);
  if (it == getEdgeEnd())
    throw OutOfBoundException<E>(edge,
      "DEMGraph::getEdgeProperty(): invalid edge", __FILE__, __LINE__);
  else
    return it->getProperty();
}

DEMGraph::V DEMGraph::getTailVertex(const E& edge) const {
  return findEdge(edge)->getTail();
}

DEMGraph::V DEMGraph::getHeadVertex(const E& edge) const {
  return findEdge(edge)->getHead();
}

DEMGraph::VertexContainer& DEMGraph::getVertices() {
  return mVertices;
}
