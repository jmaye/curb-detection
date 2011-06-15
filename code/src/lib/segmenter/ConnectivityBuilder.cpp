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

#include "segmenter/ConnectivityBuilder.h"

#include <stdint.h>

void ConnectivityBuilder::build(const DEM& dem,
  std::multiset<Edge, EdgeCompare>& edgeSet) {
  edgeSet.clear();
  for (uint32_t i = 0; i < dem.getCellsNbrX(); i++) {
    for (uint32_t j = 0; j < dem.getCellsNbrY(); j++) {
      if (dem(i, j).getMLEstimator().getPointsNbr() != 0) {
        if ((i + 1) < dem.getCellsNbrX() &&
          dem(i + 1, j).getMLEstimator().getPointsNbr() != 0) {
          edgeSet.insert(Edge(dem(i, j).compare(dem(i + 1, j)),
            std::make_pair(i, j), std::make_pair(i + 1, j)));
        }
        if ((j + 1) < dem.getCellsNbrY() &&
          dem(i, j + 1).getMLEstimator().getPointsNbr() != 0) {
          edgeSet.insert(Edge(dem(i, j).compare(dem(i, j + 1)),
            std::make_pair(i, j), std::make_pair(i, j + 1)));
        }
      }
    }
  }
}
