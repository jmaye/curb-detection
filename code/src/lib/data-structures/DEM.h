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

#ifndef DEM_H
#define DEM_H

#include "data-structures/PointCloud.h"
#include "data-structures/Cell.h"
#include "exceptions/OutOfBoundException.h"
#include "exceptions/InvalidOperationException.h"

#include <iosfwd>
#include <vector>
#include <map>

#include <stdint.h>

class BeliefPropagation;

class DEM {
  friend std::ostream& operator << (std::ostream& stream, const DEM& obj);
  friend std::istream& operator >> (std::istream& stream, DEM& obj);
  friend std::ofstream& operator << (std::ofstream& stream, const DEM& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, DEM& obj);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

public:
   DEM(double f64CellSizeX = 0.15, double f64CellSizeY = 0.15,
    uint32_t u32CellsNbrX = 30, uint32_t u32CellsNbrY = 30,
    double f64HeightFilterMin = -2.0, double f64HeightFilterMax = 1.0,
    double f64TranslationX = 0.0, double f64TranslationY = 0.0,
    uint32_t u32MinPointsPerPlane = 3) throw (OutOfBoundException);

  DEM(const DEM& other);
  DEM& operator = (const DEM& other);

  ~DEM();

  void addPointCloud(const PointCloud& pointCloud);

  void clear();

  uint32_t getCellsNbrX() const;
  uint32_t getCellsNbrY() const;
  uint32_t getValidCellsNbr() const;
  uint32_t getLabelsNbr() const;
  const Cell& operator () (uint32_t u32Row, uint32_t u32Column) const
    throw (OutOfBoundException);
  uint32_t getMinPointsPerPlane() const;
  double getCellSizeX() const;
  double getCellSizeY() const;
  double getHeightFilterMin() const;
  double getHeightFilterMax() const;
  double getTranslationX() const;
  double getTranslationY() const;

  void setInitialLabels(const std::map<std::pair<uint32_t, uint32_t>, uint32_t>&
    labelsMap, const std::map<uint32_t, uint32_t>& supportsMap)
    throw (InvalidOperationException);
  void setValidCellsNbr(uint32_t u32ValidCellsNbr);
  void setLabelsNbr(uint32_t u32LabelsNbr);
  void setLabelsDist(const BeliefPropagation& bp, double f64Tol = 1e-6);
  void setMAPState(const BeliefPropagation& bp);
  void setMinPointsPerPlane(uint32_t u32MinPointsPerPlane)
    throw (OutOfBoundException);

protected:
  Cell& operator () (uint32_t u32Row, uint32_t u32Column)
    throw (OutOfBoundException);

  double mf64CellSizeX;
  double mf64CellSizeY;
  uint32_t mu32CellsNbrX;
  uint32_t mu32CellsNbrY;
  double mf64HeightFilterMin;
  double mf64HeightFilterMax;
  std::vector<std::vector<Cell> > mCellsMatrix;
  uint32_t mu32ValidCellsNbr;
  uint32_t mu32LabelsNbr;
  uint32_t mu32MinPointsPerPlane;
  double mf64TranslationX;
  double mf64TranslationY;

};

#endif // DEM_H
