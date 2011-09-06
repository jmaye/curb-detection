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
#include "data-structures/Grid.h"
#include "data-structures/Cell.h"
#include "base/Timestamp.h"

int main (int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <log-file>" << std::endl;
    return 1;
  }
  std::ifstream logFile(argv[1]);
  PointCloud<> pointCloud;
  double before = Timestamp::now();
  logFile >> pointCloud;
  double after = Timestamp::now();
  std::cout << "Loading point cloud: " << after - before << " [s]" << std::endl;
  before = Timestamp::now();
  Grid<double, Cell, 2> dem(Eigen::Matrix<double, 2, 1>(0.0, 0.0),
    Eigen::Matrix<double, 2, 1>(4.0, 4.0),
    Eigen::Matrix<double, 2, 1>(0.5, 0.5));
  for (size_t i = 0; i < pointCloud.getNumPoints(); ++i)
    try {
      dem(pointCloud[i].segment(0, 2)).addPoint(pointCloud[i](2));
    }
    catch (OutOfBoundException<Eigen::Matrix<double, 2, 1> >& e) {
    }
  after = Timestamp::now();
  std::cout << "Building DEM: " << after - before << " [s]" << std::endl;
  return 0;
}