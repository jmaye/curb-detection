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

/** \file ScatterPlot2v.h
    \brief This file contains a plotting tool for bivariate scatter plots
  */

#include <vector>
#include <tuple>

#include <QtCore/QVector>

#include <qwt-qt4/qwt_plot.h>
#include <qwt-qt4/qwt_plot_curve.h>
#include <qwt-qt4/qwt_plot_grid.h>
#include <qwt-qt4/qwt_plot_panner.h>
#include <qwt-qt4/qwt_plot_magnifier.h>

#include "data-structures/PointCloud.h"
#include "utils/Colors.h"

/** The ScatterPlot2v class is a plotting tool for bivariate scatter plots.
    \brief 2-v scatter plot
  */
template <> class ScatterPlot<2> :
  public QwtPlot {
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
  ScatterPlot(const std::string& title, const PointCloud<double, 2>::Container&
    data);
  /// Constructs plot from parameters with different color for points
  ScatterPlot(const std::string& title, const
    std::vector<std::tuple<PointCloud<double, 2>::Point, size_t> >& data);
  /// Destructor
  virtual ~ScatterPlot();
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Add a points plot with the specified color
  void addPoints(const PointCloud<double, 2>::Container& data, const
    Colors::Color& color);
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Points plotted
  std::vector<QwtPlotCurve*> mPoints;
  /// Grid
  QwtPlotGrid mGrid;
  /// Panner
  QwtPlotPanner mPanner;
  /// Magnifier
  QwtPlotMagnifier mMagnifier;
  /** @}
    */

};

#include "visualization/ScatterPlot2v.tpp"
