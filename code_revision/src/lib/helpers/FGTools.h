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

/** \file FGTools.h
    \brief This file defines some helpers functions to interface libDAI.
  */

#ifndef FGTOOLS_H
#define FGTOOLS_H

#include "data-structures/Grid.h"
#include "data-structures/Cell.h"
#include "data-structures/DEMGraph.h"
#include "data-structures/FactorGraph.h"

namespace Helpers {

/** The buildFactorGraph function generates a factor graph from a DEMGraph.
*/
static void buildFactorGraph(const Grid<double, Cell, 2>& dem, const DEMGraph&
  graph, const Eigen::Matrix<double, Eigen::Dynamic, 3>& coefficients,
  const Eigen::Matrix<double, Eigen::Dynamic, 1>& variances, const
  Eigen::Matrix<double, Eigen::Dynamic, 1>& weights, FactorGraph& factorGraph);

#include "helpers/FGTools.tpp"

};

#endif // FGTOOLS_H
