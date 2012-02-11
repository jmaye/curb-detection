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
#include "data-structures/PointCloud.h"

/** \file simulate.cpp
    \brief This file is a testing binary for simulating data.
  */

int main (int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <log-file>" << std::endl;
    return 1;
  }
  LinearRegression<3> dist(Eigen::Matrix<double, 3, 1>(1, 0, 0), 0.0001);
  std::vector<Eigen::Matrix<double, 3, 1> > data;
  dist.setCoefficients(Eigen::Matrix<double, 3, 1>(0, 0, 0));
  for (double x = 0; x < 4; x += 0.01)
    for (double y = 0; y < 4; y += 0.01) {
      if (!(x >= 0 && x < 3 && y >= 0 && y < 2) &&
        !(x >= 0 && x < 3 && y >= 3 && y < 4)) {
        dist.setBasis(Eigen::Matrix<double, 3, 1>(1.0, x, y));
        data.push_back(Eigen::Matrix<double, 3, 1>(x, y, dist.getSample()));
      }
    }
  dist.setCoefficients(Eigen::Matrix<double, 3, 1>(-1.5, 0.0, 0.5));
  for (double x = 0; x < 3; x += 0.01)
    for (double y = 3; y < 4; y += 0.01) {
      dist.setBasis(Eigen::Matrix<double, 3, 1>(1.0, x, y));
      data.push_back(Eigen::Matrix<double, 3, 1>(x, y, dist.getSample()));
    }
  dist.setCoefficients(Eigen::Matrix<double, 3, 1>(1.6, 0.0, -0.8));
  for (double x = 0; x < 3; x += 0.01)
    for (double y = 1.8; y < 2; y += 0.01) {
      dist.setBasis(Eigen::Matrix<double, 3, 1>(1.0, x, y));
      data.push_back(Eigen::Matrix<double, 3, 1>(x, y, dist.getSample()));
    }
  dist.setCoefficients(Eigen::Matrix<double, 3, 1>(0.2, 0.0, 0.0));
  for (double x = 0; x < 3; x += 0.01)
    for (double y = 0; y < 1.8; y += 0.01) {
      dist.setBasis(Eigen::Matrix<double, 3, 1>(1.0, x, y));
      data.push_back(Eigen::Matrix<double, 3, 1>(x, y, dist.getSample()));
    }
  PointCloud<> pointCloud;
  for (size_t i = 0; i < data.size(); ++i)
    pointCloud.insertPoint(data[i]);
  std::ofstream logFile(argv[1]);
  logFile << pointCloud;
  return 0;
}
