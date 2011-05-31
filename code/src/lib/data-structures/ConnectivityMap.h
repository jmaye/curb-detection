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
