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

/** \file process-file.cpp
    \brief This file is a testing binary for processing a log file.
  */

#include "data-structures/PointCloud.h"
#include "data-structures/DEM.h"
#include "segmenter/ConnectivityBuilder.h"
#include "segmenter/GraphSegmenter.h"
#include "data-structures/Edge.h"
#include "misc/Timestamp.h"

int main (int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <log-file>" << std::endl;
    return 1;
  }
  std::ifstream logFile(argv[1]);
  PointCloud pointCloud;
  double before = Timestamp::now();
  logFile >> pointCloud;
  double after = Timestamp::now();
  std::cout << "Loading point cloud: " << after - before << " [s]" << std::endl;
  before = Timestamp::now();
  DEM dem(0.1, 0.1, 40, 40, -100.0, 100.0, 0.0, 0.0, 3);
  dem.addPointCloud(pointCloud);
  after = Timestamp::now();
  std::cout << "Building DEM: " << after - before << " [s]" << std::endl;
  before = Timestamp::now();
  std::multiset<Edge, EdgeCompare> edgeSet;
  std::map<std::pair<uint32_t, uint32_t>, uint32_t> labelsMap;
  std::map<uint32_t, uint32_t> supportsMap;
  ConnectivityBuilder::build(dem, edgeSet);
  GraphSegmenter::segment(dem, edgeSet, labelsMap, supportsMap, 100.0);
  after = Timestamp::now();
  std::cout << "Segmenting DEM: " << after - before << " [s]" << std::endl;
  return 0;
}
