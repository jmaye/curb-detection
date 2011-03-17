#include "Point2D.h"

#include <iostream>
#include <fstream>

using namespace std;

Point2D::Point2D() : mf64X(0),
                     mf64Y(0) {
}

Point2D::Point2D(double f64X, double f64Y) : mf64X(f64X),
                                             mf64Y(f64Y) {
}

Point2D::Point2D(const Point2D& other) : mf64X(other.mf64X),
                                         mf64Y(other.mf64Y) {
}

Point2D& Point2D::operator = (const Point2D& other) {
  mf64X = other.mf64X;
  mf64Y = other.mf64Y;
  return *this;
}

Point2D::~Point2D() {
}

void Point2D::read(istream& stream) {
}

void Point2D::write(ostream& stream) const {
}

void Point2D::read(ifstream& stream) {
}

void Point2D::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream,
  const Point2D& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream,
  Point2D& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream,
  const Point2D& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream,
  Point2D& obj) {
  obj.read(stream);
  return stream;
}
