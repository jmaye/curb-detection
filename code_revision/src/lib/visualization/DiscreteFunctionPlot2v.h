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

/** \file DiscreteFunctionPlot2v.h
    \brief This file contains a plotting tool for bivariate discrete
           functions
  */

#include "functions/DiscreteFunction.h"
#include "visualization/FunctionPlot.h"
#include "exceptions/BadArgumentException.h"

#include <qwtplot3d-qt4/qwt3d_surfaceplot.h>

template <typename Y, typename X, size_t M> class DiscreteFunctionPlot;

/** The DiscreteFunctionPlot1v class is a plotting tool for bivariate
    discrete functions.
    \brief 2-v discrete function plotting tool
  */
template <typename Y, typename X> class DiscreteFunctionPlot<Y, X, 2> :
  public FunctionPlot<Y, Eigen::Matrix<X, 2, 1> >,
  public Qwt3D::SurfacePlot {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  DiscreteFunctionPlot(const DiscreteFunctionPlot<Y, X, 2>& other);
  /// Assignment operator
  DiscreteFunctionPlot<Y, X, 2>& operator =
    (const DiscreteFunctionPlot<Y, X, 2>& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs plot from parameters
  DiscreteFunctionPlot(const std::string& title, const
    DiscreteFunction<Y, X, 2>& function, const Eigen::Matrix<X, 2, 1>& minimum,
    const Eigen::Matrix<X, 2, 1>& maximum)
    throw (BadArgumentException<Eigen::Matrix<X, 2, 1> >);
  /// Destructor
  virtual ~DiscreteFunctionPlot();
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
  /// Data on to be plotted
  double** mData;
  /** @}
    */

};

#include "visualization/DiscreteFunctionPlot2v.tpp"
