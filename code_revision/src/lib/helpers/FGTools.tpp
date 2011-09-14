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

#include "statistics/LinearRegression.h"

#include <vector>

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void buildFactorGraph(const Grid<double, Cell, 2>& dem, const DEMGraph&
  graph, const Eigen::Matrix<double, Eigen::Dynamic, 3>& coefficients,
  const Eigen::Matrix<double, Eigen::Dynamic, 1>& variances, const
  Eigen::Matrix<double, Eigen::Dynamic, 1>& weights, FactorGraph& factorGraph) {
  const size_t numVertices = graph.getNumVertices();
  const size_t numEdges = graph.getNumVertices();
  std::vector<dai::Var> vars;
  vars.reserve(numVertices);
  std::vector<dai::Factor> factors;
  factors.reserve(numVertices + numEdges);
  for (DEMGraph::ConstVertexIterator it = graph.getVertexBegin(); it !=
    graph.getVertexEnd(); ++it) {
    vars.push_back(dai::Var(dem.computeLinearIndex(it->first), weights.size()));
    dai::Factor fac(*(vars.end() - 1));
    for (size_t i = 0; i < weights.size(); ++i) {
      Eigen::Matrix<double, 3, 1> point;
      point(0) = 1.0;
      point.segment(1, 2) = dem.getCoordinates(it->first);
      const double target = dem[it->first].getHeightEstimator().getMean();
      fac.set(i, weights(i) * LinearRegression<3>(
        coefficients.row(i).transpose(), variances(i), point)(target));
    }
    factors.push_back(fac);
  }
  for (DEMGraph::ConstEdgeIterator it = graph.getEdgeBegin(); it !=
    graph.getEdgeEnd(); ++it) {
  }
  factorGraph = FactorGraph(factors.begin(), factors.end(), vars.begin(),
  vars.end(), factors.size(), vars.size());
}
