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
           in the graph-based segmentation algorithm
  */


#ifndef COMPONENT_H
#define COMPONENT_H

#include "exceptions/InvalidOperationException.h"
#include "exceptions/OutOfBoundException.h"

#include <iosfwd>
#include <list>

#include <stdint.h>

/** The class Component represents a component of the graph-based segmentation
    algorithm
    \brief Component of the segmentation algorithm
  */
class Component {
  friend std::ostream& operator << (std::ostream& stream, const Component& obj);
  friend std::istream& operator >> (std::istream& stream, Component& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const Component& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, Component& obj);

  /** \name Streaming methods
    @{
    */
  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Private members
    @{
    */
  /// Internal value of the component
  double mf64Int;
  /// Stores vertex associated with this component
  std::list<std::pair<uint32_t, uint32_t> > mNodesList;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  Component();
  /// Constructs component from nodes
  Component(const std::pair<uint32_t, uint32_t>& nodeCoordinates);
  /// Copy constructor
  Component(const Component& other);
  /// Assignment operator
  Component& operator = (const Component& other);
  ~Component();
  /** @}
    */

  double compare(const Component& other, uint32_t u32K) const
    throw (InvalidOperationException);
  void merge(Component& other);

  double getInt() const;
  std::list<std::pair<uint32_t, uint32_t> >& getNodesList();

  void setInt(double f64Int) throw (OutOfBoundException);
  void setNodesList(const std::list<std::pair<uint32_t, uint32_t> >& nodesList);

protected:

};

#endif // COMPONENT_H
