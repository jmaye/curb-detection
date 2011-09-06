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

/** \file Grid.h
    \brief This file defines the Grid class, which represents an n-dimensional
           grid
  */

#ifndef GRID_H
#define GRID_H

#include "base/Serializable.h"
#include "exceptions/OutOfBoundException.h"
#include "exceptions/BadArgumentException.h"
#include "utils/SizeTSupport.h"

#include <vector>

/** The class Grid represents an n-dimensional grid.
    \brief An n-dimensional grid
  */
template <typename T, typename C, size_t M> class Grid :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /// Constant iterator type
  typedef typename std::vector<C>::const_iterator ConstIteratorType;
  /// Iterator type
  typedef typename std::vector<C>::iterator IteratorType;
  /// Container type
  typedef std::vector<C> ContainerType;
  /// Index type
  typedef Eigen::Matrix<size_t, M, 1> IndexType;
  /// Coordinate type
  typedef Eigen::Matrix<T, M, 1> CoordinateType;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs grid with parameters
  Grid(const CoordinateType& minimum, const CoordinateType& maximum, const
    CoordinateType& resolution) throw (BadArgumentException<CoordinateType>);
  /// Copy constructor
  Grid(const Grid& other);
  /// Assignment operator
  Grid& operator = (const Grid& other);
  /// Destructor
  virtual ~Grid();
  /** @}
    */

  /** \name Accessors
      @{
    */
  /// Returns iterator at start of the container
  ConstIteratorType getItBegin() const;
  /// Returns iterator at start of the container
  IteratorType getItBegin();
  /// Returns iterator at end of the container
  ConstIteratorType getItEnd() const;
  /// Returns iterator at end of the container
  IteratorType getItEnd();
  /// Returns the container
  const ContainerType& getCells() const;
  /// Returns the cell at index
  const C& getCell(const IndexType& idx) const
    throw (OutOfBoundException<IndexType>);
  /// Returns the cell at index
  C& getCell(const IndexType& idx) throw (OutOfBoundException<IndexType>);
  /// Returns a cell using [index] operator
  const C& operator [] (const IndexType& idx) const;
  /// Returns a cell using [index] operator
  C& operator [] (const IndexType& idx);
  /// Returns the index of a cell using coordinates
  IndexType getIndex(const CoordinateType& point) const
    throw (OutOfBoundException<CoordinateType>);
  /// Returns a cell using (coordinate) operator
  const C& operator () (const CoordinateType& point) const;
  /// Returns a cell using (coordinate) operator
  C& operator () (const CoordinateType& point);
  /// Returns the coordinates of a cell using index
  CoordinateType getCoordinates(const IndexType& idx) const
    throw (OutOfBoundException<IndexType>);
  /// Check if the grid contains the point
  bool isInRange(const CoordinateType& point) const;
  /// Check if an index is valid
  bool isValidIndex(const IndexType& index) const;
  /// Returns the number of cells in each dimension
  const IndexType& getNumCells() const;
  /// Returns the total number of cells
  size_t getNumCellsTot() const;
  /// Returns the minimum of the grid
  const CoordinateType& getMinimum() const;
  /// Returns the maximum of the grid
  const CoordinateType& getMaximum() const;
  /// Returns the resolution of the grid
  const CoordinateType& getResolution() const;
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
  /// Computes linear index
  size_t computeLinearIndex(const IndexType& idx) const;
  /** @}
    */

  /** \name Protected members
      @{
    */
  /// Cells container
  ContainerType mCells;
  /// Minimum coordinate of the grid
  CoordinateType mMinimum;
  /// Maximum coordinate of the grid
  CoordinateType mMaximum;
  /// Resolution of the grid
  CoordinateType mResolution;
  /// Number of cells in each dimension
  IndexType mNumCells;
  /// Total number of cells
  size_t mNumCellsTot;
  /** @}
    */

};

#include "data-structures/Grid.tpp"

#endif // GRID_H
