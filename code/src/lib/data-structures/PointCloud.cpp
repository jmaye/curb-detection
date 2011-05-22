#include "PointCloud.h"

#include <iostream>
#include <fstream>

using namespace std;

PointCloudETH::PointCloudETH() {
}

PointCloudETH::~PointCloudETH() {
}

void PointCloudETH::read(istream& stream) {
}

void PointCloudETH::write(ostream& stream) const {
}

void PointCloudETH::read(ifstream& stream) throw (IOException) {
  if (stream.is_open() == false)
    throw IOException("PointCloudETH::read(): could not open file");
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

void PointCloudETH::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream, const PointCloudETH& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream, PointCloudETH& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream, const PointCloudETH& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream, PointCloudETH& obj) {
  obj.read(stream);
  return stream;
}

void PointCloudETH::accept(PointCloudVisitor& v) const {
  v.visit(this);
}

const Point3D& PointCloudETH::operator [] (uint32_t u32Idx) const
  throw (OutOfBoundException) {
  if (u32Idx >= mPointsVector.size()) {
    cerr << "Requesting: " << u32Idx << " Number of points: "
         << mPointsVector.size() << endl;
    throw OutOfBoundException("PointCloudETH::operator []: invalid index");
  }
  return mPointsVector[u32Idx];
}

uint32_t PointCloudETH::getSize() const {
  return mPointsVector.size();
}
