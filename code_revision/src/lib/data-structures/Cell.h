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

/** \file Cell.h
    \brief This file defines the Cell class, which represents a cell of a
           Digital Elevation Map (DEM).
  */

#ifndef CELL_H
#define CELL_H

#include "statistics/Histogram.h"
#include "base/Serializable.h"

/** The class Cell represents a cell of a Digital Elevation Map (DEM).
    \brief A cell of Digital Elevation Map (DEM)
  */
class Cell :
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Creates a cell
  Cell();
  /// Copy constructor
  Cell(const Cell& other);
  /// Assignment operator
  Cell& operator = (const Cell& other);
  /// Destructor
  virtual ~Cell();
  /** @}
    */

  /** \name Accessors
      @{
    */
  /// Adds a point into the cell
  void addPoint(double point);
  /// Returns the height histogram
  const Histogram<double, 1>& getHeightHist() const;
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream);
  /// Writes to standard output
  virtual void write(std::ostream& stream) const;
  /// Reads from a file
  virtual void read(std::ifstream& stream);
  /// Writes to a file
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Histogram of the height values
  Histogram<double, 1> mHeightHist;
  /** @}
    */

};

#endif // CELL_H
