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

/** \file test-rms.cpp
    \brief This file is a testing binary for testing the RMS error.
  */

#include <string>

#include "base/Timestamp.h"
#include "processing/Processor.h"
#include "data-structures/PointCloud.h"

int main (int argc, char** argv) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <log-file-1>" << " <log-file-2>"
      << std::endl;
    return 1;
  }
  std::ifstream logFile1(argv[1]);
  PointCloud<> pointCloud1;
  logFile1 >> pointCloud1;
  Processor processor;
  double before = Timestamp::now();
  processor.processPointCloud(pointCloud1);
  double after = Timestamp::now();
  std::cout << "Point cloud processed: " << after - before << " [s]"
    << std::endl;
  std::ifstream logFile2(argv[2]);
  PointCloud<> pointCloud2;
  logFile2 >> pointCloud2;
  Grid<double, Cell, 2> dem(Grid<double, Cell, 2>::Coordinate(0.0, 0.0),
    Grid<double, Cell, 2>::Coordinate(4.0, 4.0),
    Grid<double, Cell, 2>::Coordinate(0.1, 0.1));
  for (PointCloud<double, 3>::ConstPointIterator it =
      pointCloud2.getPointBegin();
      it != pointCloud2.getPointEnd(); ++it) {
    const Eigen::Matrix<double, 2, 1> point = (*it).segment(0, 2);
    if (dem.isInRange(point))
      dem(point).addPoint((*it)(2));
  }
  DEMGraph graph(dem);
  const DEMGraph::VertexContainer& vertices = processor.getVerticesLabels();
  const Eigen::Matrix<double, Eigen::Dynamic, 3>& coefficients =
    processor.getCoefficients();
  double std = 0;
  for (DEMGraph::ConstVertexIterator it = vertices.begin(); it !=
      vertices.end(); ++it) {
    Grid<double, Cell, 3>::Coordinate point;
    point(0) = 1.0;
    point.segment(1, 2) = dem.getCoordinates(it->first);
    const double estimated = (coefficients.row(it->second) * point)(0);
    const Cell& cell = dem[it->first];
    const double sampleMean = cell.getHeightEstimator().getPostPredDist().
      getMean();
    std += fabs(estimated - sampleMean);
  }
  std /= vertices.size();
  std::cout << "std: " << std << std::endl;
  return 0;
}
