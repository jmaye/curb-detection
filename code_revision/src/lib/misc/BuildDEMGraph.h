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

/** \file BuildDEMGraph.h
    \brief This file defines the BuildDEMGraph class which is an utility for
           building a graph from a DEM.
  */

#ifndef BUILDDEMGRAPH_H
#define BUILDDEMGRAPH_H

#include "data-structures/Grid.h"
#include "data-structures/Cell.h"
#include "data-structures/Graph.h"

/** The class BuildDEMGraph is an utility for building a graph from a DEM.
    \brief DEM graph building utility
  */
class BuildDEMGraph {
  /** \name Private constructors
    @{
    */
  /// Default constructor
  BuildDEMGraph();
  /** @}
    */

public:
  /** \name Methods
      @{
    */
  /// Build the graph
  static void build(const Grid<double, Cell, 2>& dem,
    Graph<Grid<double, Cell, 2>::Index, size_t, size_t, double>& graph);
  /** @}
    */

};

#include "misc/BuildDEMGraph.tpp"

#endif // BUILDDEMGRAPH_H
