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

/** \file TransGrid2d.h
    \brief This file defines the TransGrid2d class, which represents a
           2-dimensional grid that can be transformed
  */

#include "geometry/Transformation.h"

/** The class TransGrid2d represents an 2-dimensional grid that can be
    transformed.
    \brief A transformable 2-dimensional grid
  */
template <typename T, typename C> class TransGrid<T, C, 2> :
  public Grid<T, C, 2> {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs grid with parameters
  TransGrid(const typename Grid<T, C, 2>::Coordinate& minimum,
    const typename Grid<T, C, 2>::Coordinate& maximum,
    const typename Grid<T, C, 2>::Coordinate& resolution, T x = T(0),
     T y = T(0), T yaw = T(0));
  TransGrid(const typename Grid<T, C, 2>::Coordinate& minimum,
    const typename Grid<T, C, 2>::Coordinate& maximum,
    const typename Grid<T, C, 2>::Coordinate& resolution,
    const Transformation<double, 2>& transformation);
  /// Copy constructor
  TransGrid(const TransGrid& other);
  /// Assignment operator
  TransGrid& operator = (const TransGrid& other);
  /// Destructor
  virtual ~TransGrid();
  /** @}
    */

  /** \name Accessors
      @{
    */
  /// Returns the index of a cell using coordinates
  virtual typename Grid<T, C, 2>::Index getIndex(const typename
    Grid<T, C, 2>::Coordinate& point) const;
  /// Returns the coordinates of the center of a cell using index
  virtual typename Grid<T, C, 2>::Coordinate getCoordinates(const typename
    Grid<T, C, 2>::Index& idx) const;
  /// Returns the coordinates of the upper left corner of a cell using index
  typename Grid<T, C, 2>::Coordinate getULCoordinates(const typename
    Grid<T, C, 2>::Index& idx) const;
  /// Returns the coordinates of the upper right corner of a cell using index
  typename Grid<T, C, 2>::Coordinate getURCoordinates(const typename
    Grid<T, C, 2>::Index& idx) const;
  /// Returns the coordinates of the lower right corner of a cell using index
  typename Grid<T, C, 2>::Coordinate getLRCoordinates(const typename
    Grid<T, C, 2>::Index& idx) const;
  /// Returns the coordinates of the lower left corner of a cell using index
  typename Grid<T, C, 2>::Coordinate getLLCoordinates(const typename
    Grid<T, C, 2>::Index& idx) const;
  /// Check if the grid contains the point
  virtual bool isInRange(const typename Grid<T, C, 2>::Coordinate& point) const;
  /// Returns the transformation
  const Transformation<double, 2>& getTransformation() const;
  /// Sets the transformation
  void setTransformation(const Transformation<double, 2>& transformation);
  /// Sets the transformation with rotation and translation
  void setTransformation(double x, double y, double yaw);
  /** @}
    */

  /** \name Stream methods
      @{
    */
  /// Stream the grid into binary format
  virtual void writeBinary(std::ostream& stream) const;
  /// Reads the grid from a binary format
  virtual void readBinary(std::istream& stream);
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
  /// Transformation applied to the grid
  Transformation<double, 2> mTransformation;
  /// Inverse transformation applied to the grid
  Transformation<double, 2> mInvTransformation;
  /** @}
    */

};

#include "data-structures/TransGrid2d.tpp"
