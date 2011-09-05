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

/** \file point-viewer.cpp
    \brief This file is a testing binary for viewing a 3D point cloud loaded
           from a log file.
  */

#include "data-structures/PointCloud.h"
#include "data-structures/Grid.h"
#include "data-structures/Cell.h"

int main (int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <log-file>" << std::endl;
    return 1;
  }
  std::ifstream logFile(argv[1]);
  PointCloud<> pointCloud;
  logFile >> pointCloud;
  Grid<double, Cell> dem(Eigen::Matrix<double, 2, 1>(0.0, 0.0),
    Eigen::Matrix<double, 2, 1>(4.0, 4.0),
    Eigen::Matrix<double, 2, 1>(0.5, 0.5));
  std::cout << "Number of cells: " << dem.getNumCells().transpose()
    << std::endl;
  for (size_t i = 0; i < dem.getNumCells()(0); ++i)
    for (size_t j = 0; j < dem.getNumCells()(1); ++j)
      dem((Eigen::Matrix<size_t, 2, 1>() << i, j).finished());
  return 0;
}
