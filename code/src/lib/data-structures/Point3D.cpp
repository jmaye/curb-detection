#include "data-structures/Point3D.h"

#include <iostream>
#include <fstream>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Point3D::Point3D() :
  Point2D(0, 0),
  mf64Z(0) {
}

Point3D::Point3D(double f64X, double f64Y, double f64Z) :
  Point2D(f64X, f64Y),
  mf64Z(f64Z) {
}

Point3D::Point3D(const Point3D& other) :
  Point2D(other),
  mf64Z(other.mf64Z) {
}

Point3D& Point3D::operator = (const Point3D& other) {
  Point2D::operator = (other);
  mf64Z = other.mf64Z;
  return *this;
}

Point3D::~Point3D() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Point3D::read(std::istream& stream) {
}

void Point3D::write(std::ostream& stream) const {
}

void Point3D::read(std::ifstream& stream) {
}

void Point3D::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream, const Point3D& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, Point3D& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream, const Point3D& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, Point3D& obj) {
  obj.read(stream);
  return stream;
}
