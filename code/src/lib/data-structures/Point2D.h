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

/** \file Point2D.h
    \brief This file defines the Point2D class, which represents 2d points.
  */

#ifndef POINT2D_H
#define POINT2D_H

#include <iosfwd>

/** The class Point2D represents 2d points.
    \brief A 2d point
  */
class Point2D {
  friend std::ostream& operator << (std::ostream& stream, const Point2D& obj);
  friend std::istream& operator >> (std::istream& stream, Point2D& obj);
  friend std::ofstream& operator << (std::ofstream& stream, const Point2D& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, Point2D& obj);

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
  Point2D();
  /// Constructs point from coordinates
  Point2D(double f64X, double f64Y);
  /// Copy constructor
  Point2D(const Point2D& other);
  /// Assignment operator
  Point2D& operator = (const Point2D& other);
  /// Destructor
  ~Point2D();
  /** @}
    */

  /** \name Public members
      @{
    */
  /// x coordinate of the point
  double mf64X;
  /// y coordinate of the point
  double mf64Y;
  /** @}
    */

protected:

};

#endif // Point2D_H
