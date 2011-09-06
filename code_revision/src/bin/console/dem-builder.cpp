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

/** \file dem-builder.cpp
    \brief This file is a testing binary for building a DEM.
  */

#include "data-structures/Grid.h"
#include "data-structures/Cell.h"

int main (int argc, char **argv) {
  Grid<double, Cell, 2> dem(Eigen::Matrix<double, 2, 1>(0.0, 0.0),
    Eigen::Matrix<double, 2, 1>(4.0, 4.0),
    Eigen::Matrix<double, 2, 1>(0.5, 0.5));
  std::cout << "DEM parameters: " << std::endl << dem << std::endl;
  for (size_t i = 0; i < dem.getNumCells()(0); ++i)
    for (size_t j = 0; j < dem.getNumCells()(1); ++j)
      dem[(Eigen::Matrix<size_t, 2, 1>() << i, j).finished()];
  std::cout << "point(0.0, 0.0) is at index: " <<
    dem.getIndex(Eigen::Matrix<double, 2, 1>(0.0, 0.0)).transpose()
    << std::endl;
  std::cout << "point(0.5, 0.5) is at index: " <<
    dem.getIndex(Eigen::Matrix<double, 2, 1>(0.5, 0.5)).transpose()
    << std::endl;
  std::cout << "point(1.0, 1.0) is at index: " <<
    dem.getIndex(Eigen::Matrix<double, 2, 1>(1.0, 1.0)).transpose()
    << std::endl;
  std::cout << "point(2.0, 2.0) is at index: " <<
    dem.getIndex(Eigen::Matrix<double, 2, 1>(2.0, 2.0)).transpose()
    << std::endl;
  std::cout << "point(3.0, 3.0) is at index: " <<
    dem.getIndex(Eigen::Matrix<double, 2, 1>(3.0, 3.0)).transpose()
    << std::endl;
  std::cout << "point(3.9, 3.9) is at index: " <<
    dem.getIndex(Eigen::Matrix<double, 2, 1>(3.9, 3.9)).transpose()
    << std::endl;
  std::cout << "point(4.0, 4.0) is at index: " <<
    dem.getIndex(Eigen::Matrix<double, 2, 1>(4.0, 4.0)).transpose()
    << std::endl;
  return 0;
}
