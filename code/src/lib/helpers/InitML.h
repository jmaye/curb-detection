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

/** \file InitML.h
    \brief This file defines the initML function, which is a helper to generate
           initial values for the ML algorithm.
  */

#ifndef INITML_H
#define INITML_H

#include "data-structures/Grid.h"
#include "data-structures/Cell.h"
#include "data-structures/DEMGraph.h"
#include "data-structures/Component.h"
#include "segmenter/GraphSegmenter.h"
#include "statistics/EstimatorML.h"
#include "statistics/LinearRegression.h"
#include "statistics/MixtureDistribution.h"

namespace Helpers {

/** The initML function generates initial values for the Maximum-Likelihood
    estimation of a mixtures of linear regression models.
*/
static bool initML(const Grid<double, Cell, 2>& dem, const DEMGraph& graph,
  const GraphSegmenter<DEMGraph>::Components& components,
  EstimatorML<LinearRegression<3> >::Container& points,
  std::vector<DEMGraph::VertexDescriptor>& pointsMapping,
  MixtureDistribution<LinearRegression<3>, Eigen::Dynamic>*& initMixture,
  bool weighted = true);

#include "helpers/InitML.tpp"

};

#endif // INITML_H
