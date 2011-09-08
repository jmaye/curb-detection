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

#include <list>

/** The class Graph represents a graph.
    \brief A graph
  */
template <typename V, typename P> class Graph :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /// Vertex descriptor
  typedef V VertexDescriptor;
  /// Graph property
  typedef P Property;
  /// Container type
  typedef std::list<V> Container;
  /// Constant vertex iterator
  typedef typename std::list<V>::const_iterator ConstVertexIterator;
  /// Vertex iterator
  typedef typename std::list<V>::iterator VertexIterator;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructor with one vertex and property parameter
  Graph(const V& vertex, const P& property = P(0));
  /// Constructor with property parameter
  Graph(const P& property = P(0));
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
  /// Insert a vertex in the component
  void insertVertex(const V& vertex);
  /// Remove a vertex from the component
  void removeVertex(const V& vertex);
  /// Merge components
  void merge(const Graph& other);
  /// Clears the component
  void clear();
  /// Returns the number of vertices
  size_t getNumVertices() const;
  /// Sets the component property
  void setProperty(const P& property);
  /// Returns the component property
  const P& getProperty() const;
  /// Returns iterator at start of the container
  ConstVertexIterator getVertexBegin() const;
  /// Returns iterator at start of the container
  VertexIterator getVertexBegin();
  /// Returns iterator at end of the container
  ConstVertexIterator getVertexEnd() const;
  /// Returns iterator at end of the container
  VertexIterator getVertexEnd();
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
  /// Vertices in the component
  Container mVertices;
  /// Graph property
  P mProperty;
  /** @}
    */

};

#include "data-structures/Graph.tpp"

#endif // GRAPH_H
