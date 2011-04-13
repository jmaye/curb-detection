#include "PointCloud.h"

#include <iostream>
#include <fstream>

using namespace std;

PointCloud::PointCloud() {
}

PointCloud::~PointCloud() {
}

void PointCloud::read(istream& stream) {
}

void PointCloud::write(ostream& stream) const {
}

void PointCloud::read(ifstream& stream) {
  while (stream.eof() == false) {
    Point3D point;
    stream >> point.mf64X;
    stream.seekg(1, ios_base::cur);
    stream >> point.mf64Y;
    stream.seekg(1, ios_base::cur);
    stream >> point.mf64Z;
    mPointsVector.push_back(point);
  }
}

void PointCloud::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream,
  const PointCloud& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream,
  PointCloud& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream,
  const PointCloud& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream,
  PointCloud& obj) {
  obj.read(stream);
  return stream;
}

void PointCloud::accept(PointCloudVisitor& v) const {
  v.visit(this);
}

const Point3D& PointCloud::operator [] (uint32_t u32Idx) const
  throw (OutOfBoundException) {
  if (u32Idx >= mPointsVector.size()) {
    cerr << "Requesting: " << u32Idx << " Number of points: " << mPointsVector.size() << endl;
    throw OutOfBoundException("PointCloud::operator []: invalid index");
  }
  return mPointsVector[u32Idx];
}

uint32_t PointCloud::getSize() const {
  return mPointsVector.size();
}
