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

/** \file Graph.h
    \brief This file defines the Graph class, which represents a graph
  */

#ifndef GRAPH_H
#define GRAPH_H

#include "base/Serializable.h"

#include <vector>

/** The class Graph represents a graph.
    \brief A graph
  */
template <typename V, typename E> class Graph :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  Graph();
  /// Copy constructor
  Graph(const Graph& other);
  /// Assignment operator
  Graph& operator = (const Graph& other);
  /// Destructor
  virtual ~Graph();
  /** @}
    */

  /** \name Accessors
      @{
    */
  /// Returns the graph's order
  size_t getOrder() const;
  /// Returns the graph's number of vertices
  size_t getNumVertices() const;
  /// Returns the graph's size
  size_t getSize() const;
  /// Returns the graph's number of edges
  size_t getNumEdges() const;
  /// Returns the edge connecting the 2 vertices
  const E& getEdge(const V& tail, const V& head) const;
  /// Returns the tail vertex connected by edge
  const V& getTailVertex(const E& edge) const;
  /// Returns the head vertex connected by edge
  const V& getHeadVertex(const E& edge) const;
  /// Check if graph is null
  bool isNull() const;
  /// Check if graph is empty
  bool isEmpty() const;
  /// Check if graph contains vertex
  bool containsVertex(const V& vertex) const;
  /// Check if graph contains edge connecting tail and head
  bool containsEdge(const V& tail, const V& head) const;
  /// Check if graph contains edge
  bool containsEdge(const E& edge) const;
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream);
  /// Writes to standard output
  virtual void write(std::ostream& stream) const;
  /// Reads from a file
  virtual void read(std::ifstream& stream);
  /// Writes to a file
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Protected methods
    @{
    */
  /** @}
    */

  /** \name Protected members
      @{
    */
  /// Graph vertices
  std::vector<V> mVertices;
  /// Graph edges
  std::vector<E> mEdges;
  /** @}
    */

};

#endif // GRAPH_H
