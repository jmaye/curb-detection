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

/** \file PointCloud.h
    \brief This file defines the PointCloud class, which represents a point
           cloud.
  */

#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include "base/Serializable.h"
#include "exceptions/OutOfBoundException.h"
#include "exceptions/IOException.h"

#include <Eigen/Core>

#include <vector>

/** The class PointCloud represents a point cloud, i.e., a group of n-d points.
    \brief A point cloud
  */
template <typename X = double, size_t M = 3> class PointCloud :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /// Point type
  typedef Eigen::Matrix<X, M, 1> Point;
  /// Container type
  typedef std::vector<Point> Container;
  /// Constant iterator type
  typedef typename Container::const_iterator ConstPointIterator;
  /// Iterator type
  typedef typename Container::iterator PointIterator;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  PointCloud();
  /// Copy constructor
  PointCloud(const PointCloud& other);
  /// Assignment operator
  PointCloud& operator = (const PointCloud& other);
  /// Destructor
  ~PointCloud();
  /** @}
    */

  /** \name Accessors
      @{
    */
  /// Returns a point using [] operator
  const Point& operator [] (size_t idx) const throw
    (OutOfBoundException<size_t>);
  /// Returns a point using [] operator
  Point& operator [] (size_t idx) throw (OutOfBoundException<size_t>);
  /// Check if an index is valid
  bool isValidIndex(size_t idx) const;
  /// Returns the size of the point cloud
  size_t getNumPoints() const;
  /// Clears the point cloud
  void clear();
  /// Inserts a point into the point cloud
  void insertPoint(const Point& point);
  /// Merge point clouds
  void merge(const PointCloud& other);
  /// Returns iterator at start of the container
  ConstPointIterator getPointBegin() const;
  /// Returns iterator at start of the container
  PointIterator getPointBegin();
  /// Returns iterator at end of the container
  ConstPointIterator getPointEnd() const;
  /// Returns iterator at end of the container
  PointIterator getPointEnd();
  /// Returns the container
  const Container& getPoints() const;
  /// Reserve memory for a point cloud
  void reserve(size_t numPoints);
  /** @}
    */

  /** \name Methods
      @{
    */
  /// Writes into a output stream
  bool writeBinary(std::ostream& stream) const;
  /// Reads from an input stream
  bool readBinary(std::istream& stream);
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
  virtual void read(std::ifstream& stream) throw (IOException);
  /// Writes to a file
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Points container
  Container mPoints;
  /** @}
    */

};

#include "data-structures/PointCloud.tpp"

#endif // POINTCLOUD_H
