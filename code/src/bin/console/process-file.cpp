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

#include "base/Timestamp.h"
#include "tools/Processor.h"
#include "tools/Evaluator.h"

int main (int argc, char** argv) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <log-file> <gt-file>" << std::endl;
    return 1;
  }
  std::ifstream logFile(argv[1]);
  PointCloud<> pointCloud;
  logFile >> pointCloud;
  Processor processor;
  double before = Timestamp::now();
  processor.processPointCloud(pointCloud);
  double after = Timestamp::now();
  std::cout << "Point cloud processed: " << after - before << " [s]"
    << std::endl;
  std::ifstream gtFile(argv[2]);
  Evaluator evaluator;
  gtFile >> evaluator;
  evaluator.evaluate(processor.getDEM(), processor.getDEMGraph(),
    processor.getVerticesLabels());
  return 0;
}
