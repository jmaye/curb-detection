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
    \brief This file defines the Edge class, which represents an graph edge
  */

#ifndef EDGE_H
#define EDGE_H

#include "base/Serializable.h"

/** The class Edge represents a graph edge.
    \brief A graph edge
  */
template <typename T, typename C, size_t M> class Edge :
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
  Edge();
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
  /** @}
    */

};

#endif // EDGE_H
