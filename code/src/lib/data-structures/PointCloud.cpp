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

#include "data-structures/PointCloud.h"

#include <iostream>
#include <fstream>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

PointCloud::PointCloud() {
}

PointCloud::~PointCloud() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void PointCloud::read(std::istream& stream) {
}

void PointCloud::write(std::ostream& stream) const {
}

void PointCloud::read(std::ifstream& stream) throw (IOException) {
  mPointsVector.clear();
  if (stream.is_open() == false)
    throw IOException("PointCloud::read(): could not open file");
  while (stream.eof() == false) {
    Point3D point;
    stream >> point.mf64X;
    stream.seekg(1, std::ios_base::cur);
    stream >> point.mf64Y;
    stream.seekg(1, std::ios_base::cur);
    stream >> point.mf64Z;
    mPointsVector.push_back(point);
  }
}

void PointCloud::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream, const PointCloud& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, PointCloud& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream, const PointCloud& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, PointCloud& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

const Point3D& PointCloud::operator [] (uint32_t u32Idx) const
  throw (OutOfBoundException) {
  if (u32Idx >= mPointsVector.size()) {
    std::cerr << "Requesting: " << u32Idx << " Number of points: "
      << mPointsVector.size() << std::endl;
    throw OutOfBoundException("PointCloud::operator []: invalid index");
  }
  return mPointsVector[u32Idx];
}

uint32_t PointCloud::getSize() const {
  return mPointsVector.size();
}

void PointCloud::clear() {
  mPointsVector.clear();
}

void PointCloud::addPoint(const Point3D& point) {
  mPointsVector.push_back(point);
}

void PointCloud::addPointCloud(const PointCloud& pointCloud) {
  for (uint32_t i = 0; i < pointCloud.getSize(); i++)
    mPointsVector.push_back(pointCloud[i]);
}
