#include "data-structures/Point2D.h"

#include <iostream>
#include <fstream>


/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Point2D::Point2D() :
  mf64X(0),
  mf64Y(0) {
}

Point2D::Point2D(double f64X, double f64Y) :
  mf64X(f64X),
  mf64Y(f64Y) {
}

Point2D::Point2D(const Point2D& other) :
  mf64X(other.mf64X),
  mf64Y(other.mf64Y) {
}

Point2D& Point2D::operator = (const Point2D& other) {
  mf64X = other.mf64X;
  mf64Y = other.mf64Y;
  return *this;
}

Point2D::~Point2D() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Point2D::read(std::istream& stream) {
}

void Point2D::write(std::ostream& stream) const {
}

void Point2D::read(std::ifstream& stream) {
}

void Point2D::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream, const Point2D& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, Point2D& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream, const Point2D& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, Point2D& obj) {
  obj.read(stream);
  return stream;
}
