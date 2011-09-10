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

/** \file DEMGraph.h
    \brief This file defines the DEMGraph class which is a special graph
           implementation for a DEM purpose.
  */

#ifndef DEMGRAPH_H
#define DEMGRAPH_H

/** The class DEMGraph represents a special graph implementation for a DEM.
    \brief DEM graph
  */
class DEMGraph :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /// Vertex descriptor
  typedef V VertexDescriptor;
  /// Edge descriptor
  typedef E EdgeDescriptor;
  /// Edge property
  typedef P EdgeProperty;
  /// Edge container
  typedef std::map<E, UndirectedEdge<V, P> > EdgeContainer;
  /// Constant edge iterator
  typedef typename EdgeContainer::const_iterator ConstEdgeIterator;
  /// Edge iterator
  typedef typename EdgeContainer::iterator EdgeIterator;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs the graph from the DEM
  DEMGraph(const Grid<double, Cell, 2>& dem);
  /// Copy constructor
  DEMGraph(const DEMGraph& other);
  /// Assignment operator
  DEMGraph& operator = (const DEMGraph& other);
  /// Destructor
  virtual ~DEMGraph();
  /** @}
    */

  /** \name Accessors
      @{
    */
  /// Returns iterator at start of the edge container
  ConstEdgeIterator getEdgeBegin() const;
  /// Returns iterator at start of the edge container
  EdgeIterator getEdgeBegin();
  /// Returns iterator at end of the edge container
  ConstEdgeIterator getEdgeEnd() const;
  /// Returns iterator at end of the edge container
  EdgeIterator getEdgeEnd();
  /// Returns the number of edges
  size_t getNumEdges() const;
  /// Returns an edge descriptor from an iterator
  E getEdge(ConstEdgeIterator it) const throw
    (OutOfBoundException<size_t>);
  /// Returns an edge descriptor from a tail and head vertex
  E getEdge(const V& tail, const V& head) const throw (OutOfBoundException<V>);
  /// Checks if graph contains an edge
  bool containsEdge(const V& tail, const V& head) const;
  /// Finds an edge in the graph
  EdgeIterator findEdge(const E& edge) const;
  /// Sets an edge property
  void setEdgeProperty(const E& edge, const P& property);
  /// Returns an edge property
  P& getEdgeProperty(const E& edge) throw (OutOfBoundException<E>);
  /// Returns an edge property
  const P& getEdgeProperty(const E& edge) const throw (OutOfBoundException<E>);
  /// Sets a vertex property
  void setVertexProperty(const V& vertex, const T& property);
  /// Returns a vertex property
  T& getVertexProperty(const V& vertex) throw (OutOfBoundException<V>);
  /// Returns a vertex property
  const T& getVertexProperty(const V& vertex) const
    throw (OutOfBoundException<V>);
  /// Returns tail vertex from an edge
  V getTailVertex(const E& edge) const;
  /// Returns head vertex from an edge
  V getHeadVertex(const E& edge) const;
  /// Inserts an edge in the graph
  void insertEdge(const V& tail, const V& head);
  /// Removes an edge from the graph
  void removeEdge(ConstEdgeIterator& it);
  /// Clears the edges
  void clearEdges();
  /// Inserts a vertex in the graph
  void insertVertex(const V& vertex);
  /// Removes a vertex from the graph
  void removeVertex(ConstVertexIterator& it);
  /// Clears the vertices
  void clearVertices();
  /// Clears the graph
  void clear();
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

  /** \name Protected members
      @{
    */
  /// Edges in the graph
  EdgeContainer mEdges;
  /** @}
    */

};

#include "data-structures/DEMGraph.tpp"

#endif // DEMGRAPH_H
