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

/** \file FunctionPlot1v.h
    \brief This file is an interface for plotting univariate functions
  */

#include <string>

#include <qwt-qt4/qwt_plot.h>
#include <qwt-qt4/qwt_plot_curve.h>
#include <qwt-qt4/qwt_plot_grid.h>
#include <qwt-qt4/qwt_plot_panner.h>
#include <qwt-qt4/qwt_plot_magnifier.h>

#include "data-structures/Grid.h"
#include "utils/IsReal.h"
#include "utils/IsInteger.h"

/** The FunctionPlot1v class is an interface for plotting univariate
    functions.
    \brief Univariate function plotter
  */
template <typename F> class FunctionPlot<F, 1> :
   public QwtPlot {
  /** \name Types definitions
    @{
    */
  /// Domain type
  typedef typename F::Domain Domain;
  /// Domain type
  typedef typename F::DomainType DomainType;
  /// Coordinate type
  typedef typename Grid<DomainType, double, 1>::Coordinate Coordinate;
  /// Index type
  typedef typename Grid<DomainType, double, 1>::Index Index;
  /** @}
    */

  /** \name Traits
    @{
    */
  /// Specialization for integer or real types
  struct Traits {
  public:
    /// Style for real types
    template <typename Z, typename IsReal<Z>::Result::Numeric>
      static void setCurveStyle(QwtPlotCurve& curve);
    /// Style for integer types
    template <typename Z, typename IsInteger<Z>::Result::Numeric>
      static void setCurveStyle(QwtPlotCurve& curve);
  };
  /** @}
    */

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  FunctionPlot(const FunctionPlot& other);
  /// Assignment operator
  FunctionPlot& operator = (const FunctionPlot& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs plot from parameters
  FunctionPlot(const std::string& title, const F& function, const Domain&
    minimum, const Domain& maximum, const Domain& resolution = Domain(1));
  /// Destructor
  virtual ~FunctionPlot();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the plot's title
  const std::string& getTitle() const;
  /// Returns the plot's minimum
  const Domain& getMinimum() const;
  /// Returns the plot's maximum
  const Domain& getMaximum() const;
  /// Returns the plot's resolution
  const Domain& getResolution() const;
  /// Returns the data grid
  const Grid<DomainType, double, 1>& getDataGrid() const;
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Title of the graph
  std::string mTitle;
  /// Minimum value on the x-axis
  Domain mMinimum;
  /// Maximum value on the x-axis
  Domain mMaximum;
  /// Resolution of the plot
  Domain mResolution;
  /// Data grid
  Grid<DomainType, double, 1> mDataGrid;
  /// Plotted curve
  QwtPlotCurve mCurve;
  /// Displayed grid
  QwtPlotGrid mGrid;
  /// Panner
  QwtPlotPanner mPanner;
  /// Magnifier
  QwtPlotMagnifier mMagnifier;
  /** @}
    */

};

#include "visualization/FunctionPlot1v.tpp"
