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

/** \file DEM.h
    \brief This file defines the DEM class, which represents a
           Digital Elevation Map
  */

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

/** The class DEM represents a Digital Elevation Map
    \brief A Digital Elevation Map
  */
class DEM {
  friend std::ostream& operator << (std::ostream& stream, const DEM& obj);
  friend std::istream& operator >> (std::istream& stream, DEM& obj);
  friend std::ofstream& operator << (std::ofstream& stream, const DEM& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, DEM& obj);

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
   /// Constructs DEM from parameters
   DEM(double f64CellSizeX = 0.15, double f64CellSizeY = 0.15,
    uint32_t u32CellsNbrX = 30, uint32_t u32CellsNbrY = 30,
    double f64HeightFilterMin = -2.0, double f64HeightFilterMax = 1.0,
    double f64TranslationX = 0.0, double f64TranslationY = 0.0,
    uint32_t u32MinPointsPerPlane = 3) throw (OutOfBoundException);
  /// Copy constructor
  DEM(const DEM& other);
  /// Assignment operator
  DEM& operator = (const DEM& other);
  /// Destructor
  ~DEM();
  /** @}
    */

  /** \name Accessors
      @{
    */
  /// Adds a point cloud to the DEM
  void addPointCloud(const PointCloud& pointCloud);
  /// Clears the DEM
  void clear();
  /// Returns the number of cells in X
  uint32_t getCellsNbrX() const;
  /// Returns the number of cells in Y
  uint32_t getCellsNbrY() const;
  /// Returns the number of valid cells
  uint32_t getValidCellsNbr() const;
  /// Returns the number of labels for the cells
  uint32_t getLabelsNbr() const;
  /// Access a particular cell of the DEM
  const Cell& operator () (uint32_t u32Row, uint32_t u32Column) const
    throw (OutOfBoundException);
  /// Returns the number of points needed to build a plane
  uint32_t getMinPointsPerPlane() const;
  /// Returns the size of a cell in X
  double getCellSizeX() const;
  /// Returns the size of a cell in Y
  double getCellSizeY() const;
  /// Return the minimum height of the considered points
  double getHeightFilterMin() const;
  /// Return the maximum height of the considered points
  double getHeightFilterMax() const;
  /// Returns the translation of the DEM in X with respect to the sensor
  double getTranslationX() const;
  /// Returns the translation of the DEM in Y with respect to the sensor
  double getTranslationY() const;
  /// Sets the initial labels from pre-segmentation
  void setInitialLabels(const std::map<std::pair<uint32_t, uint32_t>, uint32_t>&
    labelsMap, const std::map<uint32_t, uint32_t>& supportsMap)
    throw (InvalidOperationException);
  /// Sets the number of valid cells (should not be used)
  void setValidCellsNbr(uint32_t u32ValidCellsNbr);
  /// Sets the number of labels per cell (should not be used)
  void setLabelsNbr(uint32_t u32LabelsNbr);
  /// Sets the label distribution to the DEM from the result of belief propagation
  void setLabelsDist(const BeliefPropagation& bp, double f64Tol = 1e-6);
  /// Sets the MAP state of the DEM from belief propagation
  void setMAPState(const BeliefPropagation& bp);
  /// Sets the minimum number of points needed for building a plane
  void setMinPointsPerPlane(uint32_t u32MinPointsPerPlane)
    throw (OutOfBoundException);
  /** @}
    */

protected:
  /** \name Protected methods
      @{
    */
  /// Access a cell of the DEM
  Cell& operator () (uint32_t u32Row, uint32_t u32Column)
    throw (OutOfBoundException);
  /** @}
    */

  /** \name Protected members
      @{
    */
  /// Size of the cells in X
  double mf64CellSizeX;
  /// Size of the cells in Y
  double mf64CellSizeY;
  /// Number of cells in X
  uint32_t mu32CellsNbrX;
  /// Number of cells in Y
  uint32_t mu32CellsNbrY;
  /// Minimum height considered
  double mf64HeightFilterMin;
  /// Maximum height considered
  double mf64HeightFilterMax;
  /// Stores the cells
  std::vector<std::vector<Cell> > mCellsMatrix;
  /// Number of valid cells
  uint32_t mu32ValidCellsNbr;
  /// Number of labels in the cells
  uint32_t mu32LabelsNbr;
  /// Minimum number of points needed for a plane
  uint32_t mu32MinPointsPerPlane;
  /// Translation of the DEM in X with respect to the sensor
  double mf64TranslationX;
  /// Translation of the DEM in X with respect to the sensor
  double mf64TranslationY;
  /** @}
    */

};

#endif // DEM_H
