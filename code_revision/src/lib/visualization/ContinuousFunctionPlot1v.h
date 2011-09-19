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

/** \file ContinuousFunctionPlot1v.h
    \brief This file contains a plotting tool for univariate continuous
           functions
  */

#include "functions/ContinuousFunction.h"
#include "visualization/FunctionPlot.h"
#include "exceptions/BadArgumentException.h"

#include <QtCore/QVector>

#include <qwt-qt4/qwt_plot.h>
#include <qwt-qt4/qwt_plot_curve.h>
#include <qwt-qt4/qwt_plot_grid.h>
#include <qwt-qt4/qwt_plot_panner.h>
#include <qwt-qt4/qwt_plot_magnifier.h>

/** The ContinuousFunctionPlot1v class is a plotting tool for univariate
    continuous functions.
    \brief 1-v continuous function plotting tool
  */
template <typename Y, typename X> class ContinuousFunctionPlot<Y, X, 1> :
  public FunctionPlot<Y, X>,
  public QwtPlot {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  ContinuousFunctionPlot(const ContinuousFunctionPlot<Y, X, 1>& other);
  /// Assignment operator
  ContinuousFunctionPlot<Y, X, 1>& operator =
    (const ContinuousFunctionPlot<Y, X, 1>& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs plot from parameters
  ContinuousFunctionPlot(const std::string& title, const
    ContinuousFunction<Y, X>& function, const X& minimum, const X& maximum,
    const X& resolution) throw (BadArgumentException<X>);
  /// Destructor
  virtual ~ContinuousFunctionPlot();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the plot's resolution
  const X& getResolution() const;
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
  /// Resolution on the axis
  X mResolution;
  /** @}
    */

};

#include "visualization/ContinuousFunctionPlot1v.tpp"
