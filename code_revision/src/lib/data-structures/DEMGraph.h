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

#include "data-structures/Grid.h"
#include "data-structures/Cell.h"
#include "data-structures/UndirectedEdge.h"
#include "utils/IndexHash.h"

#include <vector>
#include <tr1/unordered_map>

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
  typedef Grid<double, Cell, 2>::Index VertexDescriptor;
  /// Vertex descriptor
  typedef VertexDescriptor V;
  /// Edge descriptor
  typedef size_t EdgeDescriptor;
  /// Edge descriptor
  typedef EdgeDescriptor E;
  /// Edge property
  typedef double EdgeProperty;
  /// Edge property
  typedef EdgeProperty P;
  /// Edge container
  typedef std::vector<UndirectedEdge<V, P> > EdgeContainer;
  /// Constant edge iterator
  typedef EdgeContainer::const_iterator ConstEdgeIterator;
  /// Edge iterator
  typedef EdgeContainer::iterator EdgeIterator;
  /// Vertex container
  typedef std::tr1::unordered_map<V, size_t, IndexHash> VertexContainer;
  /// Constant vertex iterator
  typedef VertexContainer::const_iterator ConstVertexIterator;
  /// Vertex iterator
  typedef VertexContainer::iterator VertexIterator;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs the graph from the DEM
  inline DEMGraph(const Grid<double, Cell, 2>& dem);
  /// Copy constructor
  inline DEMGraph(const DEMGraph& other);
  /// Assignment operator
  inline DEMGraph& operator = (const DEMGraph& other);
  /// Destructor
  inline virtual ~DEMGraph();
  /** @}
    */

  /** \name Accessors
      @{
    */
  /// Returns iterator at start of the edge container
  inline ConstEdgeIterator getEdgeBegin() const;
  /// Returns iterator at start of the edge container
  inline EdgeIterator getEdgeBegin();
  /// Returns iterator at end of the edge container
  inline ConstEdgeIterator getEdgeEnd() const;
  /// Returns iterator at end of the edge container
  inline EdgeIterator getEdgeEnd();
  /// Returns the number of edges
  inline size_t getNumEdges() const;
  /// Returns an edge descriptor from an iterator
  inline E getEdge(const ConstEdgeIterator& it) const
    throw (OutOfBoundException<E>);
  /// Finds an edge in the graph
  inline EdgeIterator findEdge(const E& edge) const;
  /// Sets an edge property
  inline void setEdgeProperty(const E& edge, const P& property);
  /// Returns an edge property
  inline P& getEdgeProperty(const E& edge) throw (OutOfBoundException<E>);
  /// Returns an edge property
  inline const P& getEdgeProperty(const E& edge) const
    throw (OutOfBoundException<E>);
  /// Returns the tail vertex
  inline const V& getTailVertex(const E& edge) const;
  /// Returns head vertex from an edge
  inline const V& getHeadVertex(const E& edge) const;
  /// Return the vertex container
  inline VertexContainer& getVertices();
  /// Returns iterator at start of the vertex container
  inline ConstVertexIterator getVertexBegin() const;
  /// Returns iterator at start of the vertex container
  inline VertexIterator getVertexBegin();
  /// Returns iterator at end of the vertex container
  inline ConstVertexIterator getVertexEnd() const;
  /// Returns iterator at end of the vertex container
  inline VertexIterator getVertexEnd();
  /// Returns the number of vertices
  inline size_t getNumVertices() const;
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  inline virtual void read(std::istream& stream);
  /// Writes to standard output
  inline virtual void write(std::ostream& stream) const;
  /// Reads from a file
  inline virtual void read(std::ifstream& stream);
  /// Writes to a file
  inline virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Protected members
      @{
    */
  /// Edges in the graph
  EdgeContainer mEdges;
  /// Vertices in the graph
  VertexContainer mVertices;
  /** @}
    */

};

#include "data-structures/DEMGraph.tpp"

#endif // DEMGRAPH_H
