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

/** \file mlbp.cpp
    \brief This file is a testing binary for mlbp estimator.
  */

#include <string>

#include "base/Timestamp.h"
#include "data-structures/PointCloud.h"
#include "statistics/EstimatorMLBPMixtureLinearRegression.h"
#include "evaluation/Evaluator.h"
#include "segmenter/GraphSegmenter.h"
#include "helpers/InitML.h"

int main (int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <log-file>" << std::endl;
    return 1;
  }
  std::ifstream logFile(argv[1]);
  PointCloud<> pointCloud;
  logFile >> pointCloud;
  double start = Timestamp::now();
  Grid<double, Cell, 2> dem(Grid<double, Cell, 2>::Coordinate(0.0, 0.0),
    Grid<double, Cell, 2>::Coordinate(4.0, 4.0),
    Grid<double, Cell, 2>::Coordinate(0.1, 0.1));
  for (auto it = pointCloud.getPointBegin(); it != pointCloud.getPointEnd();
      ++it) {
    const Eigen::Matrix<double, 2, 1> point = (*it).segment(0, 2);
    if (dem.isInRange(point))
      dem(point).addPoint((*it)(2));
  }
  DEMGraph graph = DEMGraph(dem);
  GraphSegmenter<DEMGraph>::Components components;
  GraphSegmenter<DEMGraph>::segment(graph, components, graph.getVertices(),
    300);
  EstimatorML<LinearRegression<3> >::Container points;
  std::vector<DEMGraph::VertexDescriptor> pointsMapping;
  MixtureDistribution<LinearRegression<3>, Eigen::Dynamic>* initMixture = 0;
  DEMGraph::VertexContainer vertices;
  if (Helpers::initML(dem, graph, components, points, pointsMapping,
      initMixture, false)) {
    if (initMixture->getCompDistributions().size() > 1) {
      EstimatorMLBP<MixtureDistribution<LinearRegression<3>, Eigen::Dynamic> >
        estMixtPlane(*initMixture, dem, graph, pointsMapping, 200, 1e-9);
      const size_t numIter = estMixtPlane.addPointsEM(points.begin(),
        points.end());
      vertices = estMixtPlane.getVerticesLabels();
    }
    else
      for (auto it = graph.getVertexBegin(); it != graph.getVertexEnd(); ++it)
        vertices[it->first] = 0;
  }
  else
    return 1;
  double stop = Timestamp::now();
  std::cout << "Point cloud processed: " << stop - start << " [s]" << std::endl;
  std::string logFilename(argv[1]);
  size_t pos = logFilename.find(".csv");
  if (pos == 0)
    pos = logFilename.find(".log");
  std::string gtFilename;
  if (pos) {
    gtFilename = logFilename.substr(0, logFilename.size() - 4);
    gtFilename.append(".gt");
  }
  else
    return 1;
  std::ifstream gtFile(gtFilename.c_str());
  Evaluator evaluator;
  gtFile >> evaluator;
  const double vMeasure = evaluator.evaluate(dem, graph, vertices);
  std::cout << "V-Measure = " << vMeasure << std::endl;
  return 0;
}
