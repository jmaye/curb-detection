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

/** \file HistogramPlot1v.h
    \brief This file contains a plotting tool for univariate histograms
  */

#include "statistics/Histogram.h"

#include <QtCore/QVector>

#include <qwt-qt4/qwt_plot.h>
#include <qwt-qt4/qwt_plot_curve.h>
#include <qwt-qt4/qwt_plot_grid.h>
#include <qwt-qt4/qwt_plot_panner.h>
#include <qwt-qt4/qwt_plot_magnifier.h>

/** The HistogramPlot1v class is a plotting tool for univariate histograms.
    \brief 1-v histogram plot
  */
template <typename T> class HistogramPlot<T, 1> :
  public QwtPlot {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  HistogramPlot(const HistogramPlot<T, 1>& other);
  /// Assignment operator
  HistogramPlot<T, 1>& operator = (const HistogramPlot<T, 1>& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs plot from parameters
  HistogramPlot(const std::string& title, const Histogram<T, 1>& histogram);
  /// Destructor
  virtual ~HistogramPlot();
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
  /// Histogram plotted
  QwtPlotCurve mHistogram;
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

#include "visualization/HistogramPlot1v.tpp"
