#include "Point3D.h"

#include <iostream>
#include <fstream>

using namespace std;

Point3D::Point3D() {
}

Point3D::Point3D(const Point3D& other) : mf64X(other.mf64X),
                                         mf64Y(other.mf64Y),
                                         mf64Z(other.mf64Z) {
}

Point3D& Point3D::operator = (const Point3D& other) {
  mf64X = other.mf64X;
  mf64Y = other.mf64Y;
  mf64Z = other.mf64Z;
  return *this;
}

Point3D::~Point3D() {
}

void Point3D::read(istream& stream) {
}

void Point3D::write(ostream& stream) const {
}

void Point3D::read(ifstream& stream) {
}

void Point3D::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream,
  const Point3D& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream,
  Point3D& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream,
  const Point3D& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream,
  Point3D& obj) {
  obj.read(stream);
  return stream;
}

void Point3D::accept(const PointCloudVisitor& v) const {
  v.visit(this);
}
