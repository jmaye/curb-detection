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

#include "statistics/UniGaussian.h"
#include "statistics/MLEstimator.h"
#include "data-structures/Point2D.h"
#include "exceptions/InvalidOperationException.h"
#include "exceptions/OutOfBoundException.h"

#include <iosfwd>
#include <vector>

#include <stdint.h>

/** The class Cell represents a cell of a Digital Elevation Map (DEM).
    \brief A cell of Digital Elevation Map (DEM)
  */
class Cell {
  friend std::ostream& operator << (std::ostream& stream, const Cell& obj);
  friend std::istream& operator >> (std::istream& stream, Cell& obj);
  friend std::ofstream& operator << (std::ofstream& stream, const Cell& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, Cell& obj);

  /** \name Streaming methods
    @{
    */
  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Private members
    @{
    */
  /// Stores the height normal distribution for the cell
  UniGaussian mHeightDist;
  /// Estimate the height distribution for the cell
  MLEstimator mMLEstimator;
  /// Stores the coordinates of the cell center
  Point2D mCellCenter;
  /// Stores the cell size in x,y
  Point2D mCellSize;
  /// Flags the cell as being invalid
  bool mbInvalidFlag;
  /// Stores the discrete distribution over labels for the cell
  std::vector<double> mLabelsDistVector;
  /// Stores the MAP label for the cell
  uint32_t mu32MAPState;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Creates a cell
  Cell(const UniGaussian& heightDist, const MLEstimator& estimator,
    const Point2D& cellCenter, const Point2D& cellSize)
    throw (OutOfBoundException);
  /// Copy constructor
  Cell(const Cell& other);
  /// Assignment operator
  Cell& operator = (const Cell& other);
  /// Destructor
  ~Cell();
  /** @}
    */

  /** \name Accessors
      @{
    */
  /// Returns the height distribution for the cell
  const UniGaussian& getHeightDist() const;
  /// Returns the Maximum-Likelihood estimator for the cell
  const MLEstimator& getMLEstimator() const;
  /// Returns the cell center
  const Point2D& getCellCenter() const;
  /// Returns the cell size
  const Point2D& getCellSize() const;
  /// Returns the label distribution for the cell
  const std::vector<double>& getLabelsDistVector() const;
  /// Returns the MAP label for the cell
  uint32_t getMAPLabelsDist() const throw (InvalidOperationException);
  /// Returns the invalid flag
  bool getInvalidFlag() const;
  /// Sets the height distribution for the cell
  void setHeightDist(const UniGaussian& heightDist);
  /// Sets the Maximum-Likelihood estimator for the cell
  void setMLEstimator(const MLEstimator& estimator);
  /// Sets the cell center
  void setCellCenter(const Point2D& cellCenter);
  /// Sets the cell size
  void setCellSize(const Point2D& cellSize) throw (OutOfBoundException);
  /// Sets the label distribution for the cell
  void setLabelsDistVector(const std::vector<double>& labelsDistVector,
    double f64Tol = 1e-6) throw (OutOfBoundException);
  /// Sets the cell as invalid or valid
  void setInvalidFlag(bool bInvalidFlag);
  /// Sets the MAP label for the cell
  void setMAPState(uint32_t u32MAPState) throw (OutOfBoundException);
  /// Adds a new point to the cell
  void addPoint(double f64Height);
  /// Clears the content of the cell
  void clear();
  /** @}
    */
    
  /** \name Methods
      @{
    */
  /// Compares two cells
  double compare(const Cell& other) const;
  /** @}
    */
    
protected:

};

#endif // CELL_H
