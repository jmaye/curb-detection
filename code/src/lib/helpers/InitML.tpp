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

#include "data-structures/PointCloud.h"

namespace Helpers {

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

bool initML(const Grid<double, Cell, 2>& dem, const DEMGraph& graph, const
    GraphSegmenter<DEMGraph>::Components& components,
    EstimatorML<LinearRegression<3> >::Container& points,
    std::vector<DEMGraph::VertexDescriptor>& pointsMapping,
    MixtureDistribution<LinearRegression<3>, Eigen::Dynamic>*& initMixture,
    bool weighted) {
  points.clear();
  pointsMapping.clear();
  pointsMapping.reserve(graph.getNumVertices());
  points.reserve(graph.getNumVertices());
  std::vector<LinearRegression<3> > distPlanes;
  distPlanes.reserve(components.size());
  std::vector<double> numPoints;
  numPoints.reserve(components.size());
  EstimatorML<LinearRegression<3> > estPlane;
  for (auto it = components.begin(); it != components.end(); ++it) {
    EstimatorML<LinearRegression<3> >::ConstPointIterator itStart =
      points.end();
    Eigen::Matrix<double, Eigen::Dynamic, 1>
      precision(it->second.getNumVertices());
    for (auto itV = it->second.getVertexBegin();
        itV != it->second.getVertexEnd(); ++itV) {
      PointCloud<double, 3>::Point point;
      point.segment(0, 2) = dem.getCoordinates(*itV);
      auto mode = dem[*itV].getHeightEstimator().getDist().getMode();
      point(2) = std::get<0>(mode);
      points.push_back(point);
      pointsMapping.push_back(*itV);
      precision(itV - it->second.getVertexBegin()) =
        1.0 / std::get<1>(mode);
    }
    auto itEnd = points.end();
    if (weighted)
      estPlane.addPoints(itStart, itEnd, precision);
    else
      estPlane.addPoints(itStart, itEnd);
    if (estPlane.getValid()) {
      distPlanes.push_back(estPlane.getDistribution());
      numPoints.push_back(it->second.getNumVertices());
    }
  }
  if (distPlanes.size() != 0) {
    double pointsSum = 0;
    Eigen::Matrix<double, Eigen::Dynamic, 1> weights(numPoints.size());
    for (auto it = numPoints.begin(); it != numPoints.end(); ++it) {
      pointsSum += *it;
      weights(it - numPoints.begin()) = *it;
    }
    initMixture = new
      MixtureDistribution<LinearRegression<3>, Eigen::Dynamic>(distPlanes,
      CategoricalDistribution<Eigen::Dynamic>(weights / weights.sum()));
    return true;
  }
  else
    return false;
}

}
