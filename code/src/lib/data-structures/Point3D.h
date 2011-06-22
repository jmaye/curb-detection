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

/** \file Point3D.h
    \brief This file define the Point3D class, which represents 3d points.
  */

#ifndef POINT3D_H
#define POINT3D_H

#include "data-structures/Point2D.h"

#include <iosfwd>

/** The class Point3D represents 3d points.
    \brief A 3d point
  */
class Point3D : public Point2D {
  friend std::ostream& operator << (std::ostream& stream, const Point3D& obj);
  friend std::istream& operator >> (std::istream& stream, Point3D& obj);
  friend std::ofstream& operator << (std::ofstream& stream, const Point3D& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, Point3D& obj);

  /** \name Streaming methods
    @{
    */
  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  Point3D();
  /// Constructs point from coordinates
  Point3D(double f64X, double f64Y, double f64Z);
  /// Copy constructor
  Point3D(const Point3D& other);
  /// Assignment operator
  Point3D& operator = (const Point3D& other);
  /// Destructor
  ~Point3D();
  /** @}
    */

  /** \name Public members
    @{
    */
  /// Z coordinate of the point
  double mf64Z;
  /** @}
    */

protected:

};

#endif // POINT3D_H
