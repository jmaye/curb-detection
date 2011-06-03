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
