#ifndef GRAPHSEGMENTER_H
#define GRAPHSEGMENTER_H

#include "Edge.h"
#include "DEM.h"

#include <set>
#include <map>

#include <stdint.h>


class GraphSegmenter {
  GraphSegmenter();

public:
  static void segment(const DEM& dem,
    const std::multiset<Edge, EdgeCompare>& edgeSet,
    std::map<std::pair<uint32_t, uint32_t>, uint32_t>& labelsMap,
    std::map<uint32_t, uint32_t>& supportsMap, uint32_t u32K = 400);

protected:

};

#endif // GRAPHSEGMENTER_H
