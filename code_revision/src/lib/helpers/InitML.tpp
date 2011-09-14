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

#include "statistics/EstimatorML.h"
#include "data-structures/PointCloud.h"

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

bool initML(const Grid<double, Cell, 2>& dem, const DEMGraph& graph, const
  GraphSegmenter<DEMGraph>::Components& components,
  EstimatorML<LinearRegression<3>, 3>::Container& points,
  std::vector<DEMGraph::VertexDescriptor>& pointsMapping,
  Eigen::Matrix<double, Eigen::Dynamic, 3>& coefficients,
  Eigen::Matrix<double, Eigen::Dynamic, 1>& variances,
  Eigen::Matrix<double, Eigen::Dynamic, 1>& weights) {
  points.clear();
  pointsMapping.clear();
  points.reserve(graph.getNumVertices());
  std::vector<EstimatorML<LinearRegression<3>, 3>::Point> c;
  c.reserve(components.size());
  std::vector<double> v;
  v.reserve(components.size());
  std::vector<double> w;
  w.reserve(components.size());
  EstimatorML<LinearRegression<3>, 3> estPlane;
  for (GraphSegmenter<DEMGraph>::CstItComp it = components.begin(); it !=
    components.end(); ++it) {
    Component<Grid<double, Cell, 2>::Index, double>::ConstVertexIterator itV;
    EstimatorML<LinearRegression<3>, 3>::ConstPointIterator itStart =
      points.end();
    //Eigen::Matrix<double, Eigen::Dynamic, 1>
      //weightL(it->second.getNumVertices());
    for (itV = it->second.getVertexBegin(); itV != it->second.getVertexEnd();
      ++itV) {
      PointCloud<double, 3>::Point point;
      point.segment(0, 2) = dem.getCoordinates(*itV);
      point(2) = dem[*itV].getHeightEstimator().getMean();
      points.push_back(point);
      pointsMapping.push_back(*itV);
      //weightL(itV - it->second.getVertexBegin()) = 1.0 /
        //dem[*itV].getHeightEstimator().getVariance();
    }
    EstimatorML<LinearRegression<3>, 3>::ConstPointIterator itEnd =
      points.end();
    estPlane.addPoints(itStart, itEnd);
    if (estPlane.getValid()) {
      c.push_back(estPlane.getCoefficients());
      v.push_back(estPlane.getVariance());
      w.push_back(it->second.getNumVertices());
    }
  }
  if (c.size() != 0) {
    coefficients.resize(c.size(), 3);
    variances.resize(v.size());
    weights.resize(w.size());
    std::vector<EstimatorML<LinearRegression<3>, 3>::Point>::const_iterator itC;
    std::vector<double>::const_iterator itV;
    std::vector<double>::const_iterator itW;
    for (itC = c.begin(), itV = v.begin(), itW = w.begin(); itC != c.end(); ++itC,
      ++itV, ++itW) {
      const size_t row = itC - c.begin();
      coefficients.row(row) = *itC;
      variances(row) = *itV;
      weights(row) = *itW;
    }
    weights = weights / weights.sum();
    return true;
  }
  else
    return false;
}
