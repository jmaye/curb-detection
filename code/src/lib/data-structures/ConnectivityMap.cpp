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

#include "data-structures/ConnectivityMap.h"

#include <iostream>
#include <fstream>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ConnectivityMap::ConnectivityMap(const DEM& dem,
  const std::multiset<Edge, EdgeCompare>& edgeSet) {
  std::multiset<Edge>::const_iterator it;
  for (it = edgeSet.begin(); it != edgeSet.end(); it++) {
    const Cell& cell1 = dem((*it).getNode1().first, (*it).getNode1().second);
    const Cell& cell2 = dem((*it).getNode2().first, (*it).getNode2().second);
    if (cell1.getInvalidFlag() == false && cell2.getInvalidFlag() == false) {
      Point3D point1(cell1.getCellCenter().mf64X, cell1.getCellCenter().mf64Y,
        cell1.getHeightDist().getMean());
      Point3D point2(cell2.getCellCenter().mf64X, cell2.getCellCenter().mf64Y,
        cell2.getHeightDist().getMean());
      mEdgePositionsVector.push_back(std::make_pair(point1, point2));
    }
  }
}

ConnectivityMap::~ConnectivityMap() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void ConnectivityMap::read(std::istream& stream) {
}

void ConnectivityMap::write(std::ostream& stream) const {
}

void ConnectivityMap::read(std::ifstream& stream) {
}

void ConnectivityMap::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream, const ConnectivityMap& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, ConnectivityMap& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream, const ConnectivityMap& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, ConnectivityMap& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

const std::vector<std::pair<Point3D, Point3D> >& ConnectivityMap::
  getEdgePositionsVector()
  const {
  return mEdgePositionsVector;
}
