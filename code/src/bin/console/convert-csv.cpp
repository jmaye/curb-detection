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

#include <string>

#include "data-structures/PointCloud.h"

/** \file convert-csv.cpp
    \brief This file is a utility that converts CSV to pure ASCII format.
  */

int main (int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <log-file>" << std::endl;
    return 1;
  }
  std::ifstream logFileCSV(argv[1]);
  PointCloud<> pointCloud;
  logFileCSV >> pointCloud;
  std::ofstream logFileASCII((std::string(argv[1]).append(".ascii")).c_str());
  logFileASCII << pointCloud;
  return 0;
}
