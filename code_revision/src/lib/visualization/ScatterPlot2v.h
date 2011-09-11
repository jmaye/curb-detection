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

#include <QtCore/QVector>

#include <qwt-qt4/qwt_plot.h>
#include <qwt-qt4/qwt_plot_curve.h>
#include <qwt-qt4/qwt_plot_grid.h>
#include <qwt-qt4/qwt_plot_panner.h>
#include <qwt-qt4/qwt_plot_magnifier.h>

#include <Eigen/Core>

#include <vector>

/** The ScatterPlot2v class is a plotting tool for bivariate scatter plots.
    \brief 2-v scatter plot
  */
template <> class ScatterPlot<2> :
  public QwtPlot {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  ScatterPlot(const ScatterPlot<2>& other);
  /// Assignment operator
  ScatterPlot<2>& operator = (const ScatterPlot<2>& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs plot from parameters
  ScatterPlot(const std::string& title, const
    std::vector<Eigen::Matrix<double, 2, 1> >& data);
  /// Destructor
  virtual ~ScatterPlot();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Show the plot
  virtual void show();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Curve plotted
  QwtPlotCurve mCurve;
  /// Grid
  QwtPlotGrid mGrid;
  /// Panner
  QwtPlotPanner mPanner;
  /// Magnifier
  QwtPlotMagnifier mMagnifier;
  /// Data on the x-axis
  QVector<double> mXData;
  /// Data on the y-axis
  QVector<double> mYData;
  /** @}
    */

};

#include "visualization/ScatterPlot2v.tpp"
