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
    \brief This file defines the Edge class, which represents an edge in a graph
  */

#ifndef EDGE_H
#define EDGE_H

#include "exceptions/OutOfBoundException.h"

#include <iosfwd>

#include <stdint.h>

/** The class Edge represents an edge in a graph
    \brief An edge in a graph
  */
class Edge {
  friend std::ostream& operator << (std::ostream& stream, const Edge& obj);
  friend std::istream& operator >> (std::istream& stream, Edge& obj);
  friend std::ofstream& operator << (std::ofstream& stream, const Edge& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, Edge& obj);

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
  /// The weight associated with the edge
  double mf64Weight;
  /// The vertex on one side of the edge, given by its coordinates
  std::pair<uint32_t, uint32_t> mNode1;
  /// The vertex on the other side of the edge, given by its coordinates
  std::pair<uint32_t, uint32_t> mNode2;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs edge from parameters
  Edge(double f64Weight, const std::pair<uint32_t, uint32_t>& mNode1,
    const std::pair<uint32_t, uint32_t>& mNode2) throw (OutOfBoundException);
  /// Copy constructor
  Edge(const Edge& other);
  /// Assignment operator
  Edge& operator = (const Edge& other);
  /// Destructor
  ~Edge();
  /** @}
    */

  /** \name Accessors
      @{
    */
  /// Returns the weight of the edge
  double getWeight() const;
  /// Returns the vertex 1 coordinates
  const std::pair<uint32_t, uint32_t>& getNode1() const;
  /// Returns the vertex 2 coordinates
  const std::pair<uint32_t, uint32_t>& getNode2() const;
  /// Sets the weight of the edge
  void setWeight(double f64Weight) throw (OutOfBoundException);
  /// Sets the vertex 1 coordinates
  void setNode1(const std::pair<uint32_t, uint32_t>& node1);
  /// Sets the vertex 2 coordinates
  void setNode2(const std::pair<uint32_t, uint32_t>& node2);
  /** @}
    */

protected:

};

/** The class EdgeCompare implements a comparison between edges
    \brief Comparison for edges
  */
class EdgeCompare {
public:
  bool operator() (const Edge& lhs, const Edge& rhs) const {
    return lhs.getWeight() < rhs.getWeight();
  }
};

#endif // EDGE_H
