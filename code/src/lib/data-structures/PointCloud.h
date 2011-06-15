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

#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include "data-structures/Point3D.h"
#include "exceptions/OutOfBoundException.h"
#include "exceptions/IOException.h"

#include <iosfwd>
#include <vector>

#include <stdint.h>

class PointCloud {
  friend std::ostream& operator << (std::ostream& stream,
    const PointCloud& obj);
  friend std::istream& operator >> (std::istream& stream, PointCloud& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const PointCloud& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, PointCloud& obj);

  PointCloud(const PointCloud& other);
  PointCloud& operator = (const PointCloud& other);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream) throw (IOException);
  virtual void write(std::ofstream& stream) const;

  std::vector<Point3D> mPointsVector;

public:
  PointCloud();
  ~PointCloud();

  const Point3D& operator [] (uint32_t u32Idx) const
    throw (OutOfBoundException);
  uint32_t getSize() const;
  void clear();
  void addPoint(const Point3D& point);
  void addPointCloud(const PointCloud& pointCloud);

protected:

};

#endif // POINTCLOUD_H
