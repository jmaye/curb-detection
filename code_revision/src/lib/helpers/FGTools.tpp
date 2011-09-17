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

#include "statistics/NormalDistribution.h"

#include <vector>
#include <map>

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void buildFactorGraph(const Grid<double, Cell, 2>& dem, const DEMGraph&
  graph, const Eigen::Matrix<double, Eigen::Dynamic, 3>& coefficients,
  const Eigen::Matrix<double, Eigen::Dynamic, 1>& variances, const
  Eigen::Matrix<double, Eigen::Dynamic, 1>& weights, FactorGraph& factorGraph,
  DEMGraph::VertexContainer& fgMapping) {
  const size_t numVertices = graph.getNumVertices();
  const size_t numEdges = graph.getNumVertices();
  const size_t numLabels = weights.size();
  std::vector<dai::Var> vars;
  vars.reserve(numVertices);
  std::vector<dai::Factor> factors;
  factors.reserve(numVertices + numEdges);
  fgMapping.clear();
  size_t idx = 0;
  for (DEMGraph::ConstVertexIterator it = graph.getVertexBegin(); it !=
    graph.getVertexEnd(); ++it) {
    vars.push_back(dai::Var(idx, numLabels));
    const Grid<double, Cell, 2>::Index& index = it->first;
    fgMapping[index] = idx;
    dai::Factor fac(vars[idx]);
    computeNodeFactor(dem, coefficients, variances, weights, index, fac);
    factors.push_back(fac);
    idx++;
  }
  for (DEMGraph::ConstEdgeIterator it = graph.getEdgeBegin(); it !=
    graph.getEdgeEnd(); ++it) {
    const DEMGraph::EdgeDescriptor e = graph.getEdge(it);
    const DEMGraph::VertexDescriptor& v1 = graph.getHeadVertex(e);
    const DEMGraph::VertexDescriptor& v2 = graph.getTailVertex(e);
    const dai::Var& var1 = vars[fgMapping[v1]];
    const dai::Var& var2 = vars[fgMapping[v2]];
    const dai::VarSet varSet(var1, var2);
    dai::Factor fac(varSet, 1e-12);
    for (size_t i = 0; i < numLabels; ++i)
      fac.set(i * (numLabels + 1), 1.0);
    factors.push_back(fac);
  }
  factorGraph = FactorGraph(factors.begin(), factors.end(), vars.begin(),
  vars.end(), factors.size(), vars.size());
}

void updateFactorGraph(const Grid<double, Cell, 2>& dem, const DEMGraph& graph,
  const Eigen::Matrix<double, Eigen::Dynamic, 3>& coefficients,
  const Eigen::Matrix<double, Eigen::Dynamic, 1>& variances, const
  Eigen::Matrix<double, Eigen::Dynamic, 1>& weights, FactorGraph& factorGraph,
  DEMGraph::VertexContainer& fgMapping) {
  for (DEMGraph::ConstVertexIterator it = graph.getVertexBegin(); it !=
    graph.getVertexEnd(); ++it) {
    const Grid<double, Cell, 2>::Index& index = it->first;
    dai::Factor fac(factorGraph.var(fgMapping[index]));
    computeNodeFactor(dem, coefficients, variances, weights, index, fac);
    factorGraph.setFactor(fgMapping[index], fac);
  }
}

void computeNodeFactor(const Grid<double, Cell, 2>& dem, const
  Eigen::Matrix<double, Eigen::Dynamic, 3>& coefficients,
  const Eigen::Matrix<double, Eigen::Dynamic, 1>& variances, const
  Eigen::Matrix<double, Eigen::Dynamic, 1>& weights, const
  Grid<double, Cell, 2>::Index& index, dai::Factor& factor) {
  Eigen::Matrix<double, 3, 1> point;
  point(0) = 1.0;
  point.segment(1, 2) = dem.getCoordinates(index);
  const double target = dem[index].getHeightEstimator().getMean();
  const size_t numLabels = weights.size();
  for (size_t i = 0; i < numLabels; ++i)
    factor.set(i, weights(i) * NormalDistribution<1>(
      coefficients.row(i).transpose().dot(point), variances(i))(target));
}
