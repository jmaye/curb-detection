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

/** \file HistogramPlot2v.h
    \brief This file contains a plotting tool for bivariate histogram plots
  */

#include <string>

#include <qwtplot3d-qt4/qwt3d_surfaceplot.h>

#include "statistics/Histogram.h"

/** The HistogramPlot2v class is a plotting tool for bivariate histogram plots.
    \brief 2-v histogram plot
  */
template <typename T> class HistogramPlot<T, 2> :
  public Qwt3D::SurfacePlot {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  HistogramPlot(const HistogramPlot& other);
  /// Assignment operator
  HistogramPlot& operator = (const HistogramPlot& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs plot from parameters
  HistogramPlot(const std::string& title, const Histogram<T, 2>& histogram);
  /// Destructor
  virtual ~HistogramPlot();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the plot's title
  const std::string& getTitle() const;
  /// Returns the histogram
  const Histogram<T, 2>& getHistogram() const;
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Title of the graph
  std::string mTitle;
  /// Plotted histogram
  Histogram<T, 2> mHistogram;
  /// Data on to be plotted
  double** mData;
  /** @}
    */

};

#include "visualization/HistogramPlot2v.tpp"
