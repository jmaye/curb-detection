#ifndef CURBFINDER_H
#define CURBFINDER_H

#include "data-structures/DEM.h"
#include "data-structures/Edge.h"
#include "data-structures/PointCloud.h"

#include <set>

class CurbFinder {
  CurbFinder();

public:
  static void find(const DEM& dem,
    const std::multiset<Edge, EdgeCompare>& edgeSet, PointCloud& pointCloud);

protected:

};

#endif // CURBFINDER_H
