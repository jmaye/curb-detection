#ifndef CURBFINDER_H
#define CURBFINDER_H

#include "data-structures/DEM.h"
#include "data-structures/Edge.h"
#include "data-structures/CurbMap.h"

#include <set>

class CurbFinder {
  CurbFinder();

public:
  static void find(const DEM& dem,
    const std::multiset<Edge, EdgeCompare>& edgeSet, CurbMap& curbMap);

protected:

};

#endif // CURBFINDER_H
