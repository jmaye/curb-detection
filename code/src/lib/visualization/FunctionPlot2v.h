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

/** \file FunctionPlot2v.h
    \brief This file is an interface for plotting bivariate functions
  */

#include <string>

#include <qwtplot3d-qt4/qwt3d_surfaceplot.h>

#include "data-structures/Grid.h"
#include "utils/IsReal.h"
#include "utils/IsInteger.h"

/** The FunctionPlot2v class is an interface for plotting bivariate
    functions.
    \brief Bivariate function plotter
  */
template <typename F> class FunctionPlot<F, 2> :
   public Qwt3D::SurfacePlot {
  /** \name Types definitions
    @{
    */
  /// Domain type
  typedef typename F::Domain Domain;
  /// Domain type
  typedef typename F::DomainType DomainType;
  /// Coordinate type
  typedef typename Grid<DomainType, double, 2>::Coordinate Coordinate;
  /// Index type
  typedef typename Grid<DomainType, double, 2>::Index Index;
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
    minimum, const Domain& maximum, const Domain& resolution = Domain::Ones());
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
  const Grid<DomainType, double, 2>& getDataGrid() const;
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
  Grid<DomainType, double, 2> mDataGrid;
  /// Data on to be plotted
  double** mData;
  /** @}
    */

};

#include "visualization/FunctionPlot2v.tpp"
