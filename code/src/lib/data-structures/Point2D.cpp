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

#include "data-structures/Point2D.h"

#include <iostream>
#include <fstream>


/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Point2D::Point2D() :
  mf64X(0.0),
  mf64Y(0.0) {
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
