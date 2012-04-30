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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file ScatterPlot3v.h
    \brief This file contains a plotting tool for trivariate scatter plots
  */

#include <tuple>

#include "visualization/PointViewer3d.h"
#include "data-structures/PointCloud.h"

/** The ScatterPlot3v class is a plotting tool for trivariate scatter plots.
    \brief 3-v scatter plot
  */
template <> class ScatterPlot<3> {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  ScatterPlot(const ScatterPlot& other);
  /// Assignment operator
  ScatterPlot& operator = (const ScatterPlot& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs plot from parameters
  ScatterPlot(const std::string& title, const PointCloud<>::Container& data);
  /// Constructs plot from parameters with different color for points
  ScatterPlot(const std::string& title, const
    std::vector<std::tuple<PointCloud<>::Point, size_t> >& data);
  /// Destructor
  virtual ~ScatterPlot();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Show the plot
  void show();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Point viewer
  PointViewer3d mPointViewer3d;
  /** @}
    */

};

#include "visualization/ScatterPlot3v.tpp"
