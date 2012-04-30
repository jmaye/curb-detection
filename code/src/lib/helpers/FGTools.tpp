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

#include <vector>

#include "statistics/NormalDistribution.h"
#include "utils/IndexHash.h"

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void buildFactorGraph(const Grid<double, Cell, 2>& dem, const DEMGraph&
    graph, const MixtureDistribution<LinearRegression<3>, Eigen::Dynamic>&
    mixture, FactorGraph& factorGraph,
    DEMGraph::VertexContainer& fgMapping, double strength) {
  const size_t numVertices = graph.getNumVertices();
  const size_t numEdges = graph.getNumVertices();
  const size_t numLabels = mixture.getCompDistributions().size();
  std::vector<dai::Var> vars;
  vars.reserve(numVertices);
  std::vector<dai::Factor> factors;
  factors.reserve(numVertices + numEdges);
  fgMapping = DEMGraph::VertexContainer(10, IndexHash(dem.getNumCells()(1)));
  size_t idx = 0;
  for (auto it = graph.getVertexBegin(); it != graph.getVertexEnd(); ++it) {
    vars.push_back(dai::Var(idx, numLabels));
    const Grid<double, Cell, 2>::Index& index = it->first;
    fgMapping[index] = idx;
    dai::Factor fac(vars[idx]);
    computeNodeFactor(dem, mixture, index, fac);
    factors.push_back(fac);
    idx++;
  }
  for (auto it = graph.getEdgeBegin(); it != graph.getEdgeEnd(); ++it) {
    const DEMGraph::EdgeDescriptor e = graph.getEdge(it);
    const DEMGraph::VertexDescriptor& v1 = graph.getHeadVertex(e);
    const DEMGraph::VertexDescriptor& v2 = graph.getTailVertex(e);
    const dai::Var& var1 = vars[fgMapping[v1]];
    const dai::Var& var2 = vars[fgMapping[v2]];
    factors.push_back(createFactorPotts(var1, var2, strength));
  }
  factorGraph = FactorGraph(factors.begin(), factors.end(), vars.begin(),
    vars.end(), factors.size(), vars.size());
}

void updateNodeFactors(const Grid<double, Cell, 2>& dem, const DEMGraph& graph,
    const MixtureDistribution<LinearRegression<3>, Eigen::Dynamic>& mixture,
    FactorGraph& factorGraph,
    DEMGraph::VertexContainer& fgMapping) {
  for (auto it = graph.getVertexBegin(); it != graph.getVertexEnd(); ++it) {
    const Grid<double, Cell, 2>::Index& index = it->first;
    dai::Factor fac(factorGraph.var(fgMapping[index]));
    computeNodeFactor(dem, mixture, index, fac);
    factorGraph.setFactor(fgMapping[index], fac);
  }
}

void computeNodeFactor(const Grid<double, Cell, 2>& dem, const
    MixtureDistribution<LinearRegression<3>, Eigen::Dynamic>& mixture, const
    Grid<double, Cell, 2>::Index& index, dai::Factor& factor) {
  const Eigen::Matrix<double, 2, 1> point = dem.getCoordinates(index);
  auto mode = dem[index].getHeightEstimator().getDist().getMode();
  const double target = std::get<0>(mode);
  const size_t numLabels = mixture.getCompDistributions().size();
  for (size_t i = 0; i < numLabels; ++i)
    factor.set(i, mixture.getAssignDistribution().getProbability(i) *
      mixture.getCompDistribution(i).pdf(
      (Eigen::Matrix<double, 3, 1>() << point, target).finished()));
}
