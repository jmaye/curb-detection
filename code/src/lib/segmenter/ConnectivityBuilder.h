#ifndef CONNECTIVITYBUILDER_H
#define CONNECTIVITYBUILDER_H

#include "DEM.h"
#include "Edge.h"

#include <set>

class ConnectivityBuilder {
  ConnectivityBuilder();

public:
  static void build(const DEM& dem, std::multiset<Edge, EdgeCompare>& edgeSet);

protected:

};

#endif // CONNECTIVITYBUILDER_H
