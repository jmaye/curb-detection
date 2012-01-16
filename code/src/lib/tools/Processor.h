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

/** \file Processor.h
    \brief This file defines the Processor class, which performs all the
           computations to detect planes, curbs, and sidewalks.
  */

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "base/Serializable.h"
#include "data-structures/Grid.h"
#include "data-structures/Cell.h"
#include "data-structures/PointCloud.h"
#include "data-structures/Component.h"
#include "data-structures/DEMGraph.h"
#include "segmenter/GraphSegmenter.h"
#include "data-structures/FactorGraph.h"

/** The class Processor performs all the computations to detect planes, curbs,
    and sidewalks from a 3D point cloud input.
    \brief Processor for curb detection
  */
class Processor :
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructors with parameters
  Processor(const Grid<double, Cell, 2>::Coordinate& minDEM =
    Grid<double, Cell, 2>::Coordinate(0.0, 0.0),
    const Grid<double, Cell, 2>::Coordinate& maxDEM =
    Grid<double, Cell, 2>::Coordinate(4.0, 4.0),
    const Grid<double, Cell, 2>::Coordinate& demCellSize =
    Grid<double, Cell, 2>::Coordinate(0.1, 0.1), double k = 100.0,
    size_t maxMLIter = 200, double mlTol = 1e-6, bool weighted = false,
    size_t maxBPIter = 200, double bpTol = 1e-6, bool logDomain = false);
  /// Copy constructor
  Processor(const Processor& other);
  /// Assignment operator
  Processor& operator = (const Processor& other);
  /// Destructor
  virtual ~Processor();
  /** @}
    */

  /** \name Accessors
      @{
    */
  /** @}
    */

  /** \name Methods
      @{
    */
  void processPointCloud(const PointCloud<double, 3>& pointCloud);
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
  /// DEM min coordinate
  Grid<double, Cell, 2>::Coordinate mMinDEM;
  /// DEM max coordinate
  Grid<double, Cell, 2>::Coordinate mMaxDEM;
  /// DEM cells size
  Grid<double, Cell, 2>::Coordinate mDEMCellSize;
  /// Segmentation parameter
  double mK;
  /// ML maximum number of iterations
  size_t mMaxMLIter;
  /// ML tolerance
  double mMLTol;
  /// Weighted regression flag
  bool mWeighted;
  /// BP maximum number of iterations
  size_t mMaxBPIter;
  /// BP tolerance
  double mBPTol;
  /// Log-domain inference
  bool mLogDomain;

  /// DEM
  Grid<double, Cell, 2> mDEM;
  /// DEM graph
  DEMGraph mGraph;
  /// Vertices labels
  DEMGraph::VertexContainer mVertices;
  /// Regression coefficients
  Eigen::Matrix<double, Eigen::Dynamic, 3> mCoefficients;
  /// Regression variances
  Eigen::Matrix<double, Eigen::Dynamic, 1> mVariances;
  /// Regression weights
  Eigen::Matrix<double, Eigen::Dynamic, 1> mWeights;
  /** @}
    */

};

#include "tools/Processor.tpp"

#endif // PROCESSOR_H
