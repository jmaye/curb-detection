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

#include "data-structures/Point3D.h"

#include <iostream>
#include <fstream>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Point3D::Point3D() :
  Point2D(0.0, 0.0),
  mf64Z(0.0) {
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
