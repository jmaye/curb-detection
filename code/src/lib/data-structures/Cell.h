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

class Cell {
  friend std::ostream& operator << (std::ostream& stream, const Cell& obj);
  friend std::istream& operator >> (std::istream& stream, Cell& obj);
  friend std::ofstream& operator << (std::ofstream& stream, const Cell& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, Cell& obj);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  UniGaussian mHeightDist;
  MLEstimator mMLEstimator;
  Point2D mCellCenter;
  Point2D mCellSize;
  bool mbInvalidFlag;
  std::vector<double> mLabelsDistVector;
  uint32_t mu32MAPState;

public:
  Cell(const UniGaussian& heightDist, const MLEstimator& estimator,
    const Point2D& cellCenter, const Point2D& cellSize)
    throw (OutOfBoundException);
  ~Cell();
  Cell(const Cell& other);
  Cell& operator = (const Cell& other);

  void addPoint(double f64Height);
  void clear();
  double compare(const Cell& other) const;

  const UniGaussian& getHeightDist() const;
  const MLEstimator& getMLEstimator() const;
  const Point2D& getCellCenter() const;
  const Point2D& getCellSize() const;
  const std::vector<double>& getLabelsDistVector() const;
  uint32_t getMAPLabelsDist() const throw (InvalidOperationException);
  bool getInvalidFlag() const;

  void setHeightDist(const UniGaussian& heightDist);
  void setMLEstimator(const MLEstimator& estimator);
  void setCellCenter(const Point2D& cellCenter);
  void setCellSize(const Point2D& cellSize) throw (OutOfBoundException);
  void setLabelsDistVector(const std::vector<double>& labelsDistVector,
    double f64Tol = 1e-6) throw (OutOfBoundException);
  void setInvalidFlag(bool bInvalidFlag);
  void setMAPState(uint32_t u32MAPState) throw (OutOfBoundException);

protected:

};

#endif // CELL_H
