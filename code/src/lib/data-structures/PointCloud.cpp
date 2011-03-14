#include "PointCloud.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <stdint.h>

using namespace std;

PointCloud::PointCloud() {
}

PointCloud::~PointCloud() {
}

void PointCloud::read(istream& stream) {
}

void PointCloud::write(ostream& stream) const {
  for (uint32_t i = 0; i < mPointVector.size(); i++) {
    stream << mPointVector[i].mf64X << " " << mPointVector[i].mf64Y << " "
           << mPointVector[i].mf64Z << endl;
  }
}

void PointCloud::read(ifstream& stream) {
  while (stream.eof() == false) {
    Point3D point;
    stream >> point.mf64X;
    stream.seekg(1, ios_base::cur);
    stream >> point.mf64Y;
    stream.seekg(1, ios_base::cur);
    stream >> point.mf64Z;
    mPointVector.push_back(point);
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

const vector<PointCloud::Point3D>& PointCloud::getPointVector() const {
  return mPointVector;
}
