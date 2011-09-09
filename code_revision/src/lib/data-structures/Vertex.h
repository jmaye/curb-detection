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

/** \file Vertex.h
    \brief This file defines the Vertex class, which represents an undirected
           graph Vertex
  */

#ifndef VERTEX_H
#define VERTEX_H

#include "base/Serializable.h"

/** The class Vertex represents an undirected graph Vertex.
    \brief Undirected graph Vertex
  */
template <typename P> class Vertex :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /// Vertex property
  typedef P Property;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructor with parameter
  Vertex(const P& property = P(0));
  /// Copy constructor
  Vertex(const Vertex& other);
  /// Assignment operator
  Vertex& operator = (const Vertex& other);
  /// Destructor
  virtual ~Vertex();
  /** @}
    */

  /** \name Accessors
      @{
    */
  /// Sets the vertex property
  void setProperty(const P& property);
  /// Returns the vertex property
  P& getProperty();
  /// Returns the vertex property
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
  /// Vertex property
  P mProperty;
  /** @}
    */

};

#include "data-structures/Vertex.tpp"

#endif // VERTEX_H
