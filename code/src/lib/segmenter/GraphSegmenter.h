#ifndef GRAPHSEGMENTER_H
#define GRAPHSEGMENTER_H

#include "Component.h"
#include "Edge.h"

#include <vector>
#include <set>
#include <map>
#include <list>

#include <stdint.h>
#include <math.h>

class GraphSegmenter {
  GraphSegmenter();

public:
  template<class NodeType>
    static void segment(const std::vector<NodeType>& nodesVector,
      const std::multiset<Edge, EdgeCompare>& edgeSet,
      std::vector<uint32_t>& labelsVector, uint32_t u32K = 400) {
      labelsVector.clear();
      std::map<uint32_t, Component> componentsMap;
      for (uint32_t i = 0; i < nodesVector.size(); i++) {
        componentsMap[i] = i;
        labelsVector.push_back(i);
      }
      std::multiset<Edge>::iterator it;
      for (it = edgeSet.begin(); it != edgeSet.end(); it++) {
        uint32_t u32C1Idx = labelsVector[(*it).mu32Node1Idx];
        uint32_t u32C2Idx = labelsVector[(*it).mu32Node2Idx];
        if (u32C1Idx != u32C2Idx) {
          if ((*it).mf64Weight <= fmin(componentsMap[u32C1Idx].mf64Int +
            (double)u32K /
            (double)componentsMap[u32C1Idx].mNodesIndexList.size(),
            componentsMap[u32C2Idx].mf64Int +
            (double)u32K /
            (double)componentsMap[u32C2Idx].mNodesIndexList.size())) {
              std::list<uint32_t>::iterator nodesIt;
              for (nodesIt = componentsMap[u32C2Idx].mNodesIndexList.begin();
                nodesIt != componentsMap[u32C2Idx].mNodesIndexList.end();
                nodesIt++) {
                labelsVector[*nodesIt] = u32C1Idx;
              }
              componentsMap[u32C1Idx].mNodesIndexList.
                merge(componentsMap[u32C2Idx].mNodesIndexList);
              double f64Int = fmax(componentsMap[u32C1Idx].mf64Int,
                componentsMap[u32C2Idx].mf64Int);
              componentsMap[u32C1Idx].mf64Int = fmax(f64Int, (*it).mf64Weight);
              componentsMap.erase(u32C2Idx);
            }
          }
        }
    }

protected:

};

#endif // GRAPHSEGMENTER_H
