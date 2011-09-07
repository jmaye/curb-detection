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

/** \file Component.h
    \brief This file defines the Component class, which represents a component
           in the graph-based segmentation
  */

#ifndef COMPONENT_H
#define COMPONENT_H

#include "base/Serializable.h"

#include <list>

/** The class Component represents a component in the graph-based segmentation,
    i.e., a list of vertices, with some internal value.
    \brief A segmented component
  */
template <typename V, typename P> class Component :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /// Vertex descriptor
  typedef V VertexType;
  /// Component property
  typedef P PropertyType;
  /// Container type
  typedef std::list<VertexType> ContainerType;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructor with one vertex and property parameter
  Component(const VertexType& vertex, const PropertyType& property =
    PropertyType(0));
  /// Constructor with property parameter
  Component(const PropertyType& property = PropertyType(0));
  /// Copy constructor
  Component(const Component& other);
  /// Assignment operator
  Component& operator = (const Component& other);
  /// Destructor
  virtual ~Component();
  /** @}
    */

  /** \name Accessors
      @{
    */
  /// Insert a vertex in the component
  void insertVertex(const VertexType& vertex);
  /// Remove a vertex from the component
  void removeVertex(const VertexType& vertex);
  /// Merge components
  void merge(const Component& other);
  /// Clears the component
  void clear();
  /// Returns the number of vertices
  size_t getNumVertices() const;
  /// Sets the component property
  void setProperty(const PropertyType& property);
  /// Returns the component property
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
  /// Vertices in the component
  ContainerType mVertices;
  /// Component property
  PropertyType mProperty;
  /** @}
    */

};

#include "data-structures/Component.tpp"

#endif // COMPONENT_H
