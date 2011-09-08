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

/** \file UndirectedEdge.h
    \brief This file defines the UndirectedEdge class, which represents an
           undirected graph edge
  */

#ifndef UNDIRECTEDEDGE_H
#define UNDIRECTEDEDGE_H

#include "base/Serializable.h"

/** The class UndirectedEdge represents an undirected graph edge.
    \brief Undirected graph edge
  */
template <typename V, typename P> class UndirectedEdge :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /// Vertex descriptor
  typedef V VertexDescriptor;
  /// Edge property
  typedef P Property;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructor with parameter
  UndirectedEdge(const V& head, const V& tail, const P& property);
  /// Copy constructor
  UndirectedEdge(const UndirectedEdge& other);
  /// Assignment operator
  UndirectedEdge& operator = (const UndirectedEdge& other);
  /// Destructor
  virtual ~UndirectedEdge();
  /** @}
    */

  /** \name Accessors
      @{
    */
  /// Sets the head of the edge
  void setHead(const V& head);
  /// Returns the head of the edge
  const V& getHead() const;
  /// Sets the tail of the edge
  void setTail(const V& tail);
  /// Returns the tail of the edge
  const V& getTail() const;
  /// Sets the edge property
  void setProperty(const P& property);
  /// Returns the edge property
  P& getProperty();
  /// Returns the edge property
  const P& getProperty() const;
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
  V mHead;
  /// Tail vertex
  V mTail;
  /// Edge property
  P mProperty;
  /** @}
    */

};

#include "data-structures/UndirectedEdge.tpp"

#endif // UNDIRECTEDEDGE_H
