#ifndef CURBFINDER_H
#define CURBFINDER_H

#include "DEM.h"
#include "Edge.h"
#include "CurbMap.h"

#include <set>

class CurbFinder {
  CurbFinder();

public:
  static void find(const DEM& dem,
    const std::multiset<Edge, EdgeCompare>& edgeSet, CurbMap& curbMap);

protected:

};

#endif // CURBFINDER_H
