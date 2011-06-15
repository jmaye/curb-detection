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

#ifndef CONNECTIVITYMAP_H
#define CONNECTIVITYMAP_H

#include "data-structures/DEM.h"
#include "data-structures/Edge.h"
#include "data-structures/Point3D.h"

#include <iosfwd>
#include <set>
#include <vector>

class ConnectivityMap {
  friend std::ostream& operator << (std::ostream& stream,
    const ConnectivityMap& obj);
  friend std::istream& operator >> (std::istream& stream,
    ConnectivityMap& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const ConnectivityMap& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    ConnectivityMap& obj);

  ConnectivityMap(const ConnectivityMap& other);
  ConnectivityMap& operator = (const ConnectivityMap& other);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  std::vector<std::pair<Point3D, Point3D> > mEdgePositionsVector;

public:
  ConnectivityMap(const DEM& dem,
    const std::multiset<Edge, EdgeCompare>& edgeSet);
  ~ConnectivityMap();

  const std::vector<std::pair<Point3D, Point3D> >& getEdgePositionsVector()
    const;

protected:

};

#endif // CONNECTIVITYMAP_H
