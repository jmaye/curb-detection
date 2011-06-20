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

#include "misc/CurbFinder.h"

#include <iostream>
#include <fstream>

void CurbFinder::find(const DEM& dem,
  const std::multiset<Edge, EdgeCompare>& edgeSet, PointCloud& pointCloud) {
  std::multiset<Edge>::const_iterator it;
  for (it = edgeSet.begin(); it != edgeSet.end(); it++) {
    const Cell& cell1 = dem((*it).getNode1().first, (*it).getNode1().second);
    const Cell& cell2 = dem((*it).getNode2().first, (*it).getNode2().second);
    if (cell1.getInvalidFlag() == false && cell2.getInvalidFlag() == false) {
      uint32_t u32Label1 = cell1.getMAPLabelsDist();
      uint32_t u32Label2 = cell2.getMAPLabelsDist();
      if (u32Label1 != u32Label2) {
        Point3D curbPoint((cell1.getCellCenter().mf64X +
          cell2.getCellCenter().mf64X) / 2.0, (cell1.getCellCenter().mf64Y +
          cell2.getCellCenter().mf64Y) / 2.0, (cell1.getHeightDist().getMean() +
          cell2.getHeightDist().getMean()) / 2.0);
        pointCloud.addPoint(curbPoint);
      }
    }
  }
}
