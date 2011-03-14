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
