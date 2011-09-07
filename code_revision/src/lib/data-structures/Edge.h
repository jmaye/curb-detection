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

/** \file Edge.h
    \brief This file defines the Edge class, which represents an undirected
           graph edge
  */

#ifndef EDGE_H
#define EDGE_H

#include "base/Serializable.h"

/** The class Edge represents an undirected graph edge.
    \brief Undirected graph edge
  */
template <typename V, typename P> class Edge :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /// Vertex descriptor
  typedef V VertexType;
  /// Edge property
  typedef P PropertyType;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructor with parameter
  Edge(const VertexType& head, const VertexType& tail, const PropertyType&
    property);
  /// Copy constructor
  Edge(const Edge& other);
  /// Assignment operator
  Edge& operator = (const Edge& other);
  /// Destructor
  virtual ~Edge();
  /** @}
    */

  /** \name Accessors
      @{
    */
  /// Sets the head of the edge
  void setHead(const VertexType& head);
  /// Returns the head of the edge
  const VertexType& getHead() const;
  /// Sets the tail of the edge
  void setTail(const VertexType& tail);
  /// Returns the tail of the edge
  const VertexType& getTail() const;
  /// Sets the edge property
  void setProperty(const PropertyType& property);
  /// Returns the edge property
  const PropertyType& getProperty() const;
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
  /// Head vertex
  VertexType mHead;
  /// Tail vertex
  VertexType mTail;
  /// Edge property
  PropertyType mProperty;
  /** @}
    */

};

#include "data-structures/Edge.tpp"

#endif // EDGE_H
