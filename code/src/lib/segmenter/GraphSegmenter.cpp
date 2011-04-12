#include "GraphSegmenter.h"

#include "Component.h"

#include <list>

#include <math.h>

using namespace std;

void GraphSegmenter::segment(const DEM& dem,
  const multiset<Edge, EdgeCompare>& edgeSet,
  map<pair<uint32_t, uint32_t>, uint32_t>& labelsMap,
  map<uint32_t, uint32_t>& supportsMap, uint32_t u32K) {
  labelsMap.clear();
  supportsMap.clear();
  map<uint32_t, Component> componentsMap;
  uint32_t u32Idx = 0;
  for (uint32_t i = 0; i < dem.getCellsNbrX(); i++) {
    for (uint32_t j = 0; j < dem.getCellsNbrY(); j++) {
      componentsMap[u32Idx] = make_pair(i, j);
      labelsMap[make_pair(i, j)] = u32Idx;
      u32Idx++;
    }
  }
  multiset<Edge>::const_iterator it;
  for (it = edgeSet.begin(); it != edgeSet.end(); it++) {
    uint32_t u32C1Idx = labelsMap[(*it).getNode1()];
    uint32_t u32C2Idx = labelsMap[(*it).getNode2()];
    if (u32C1Idx != u32C2Idx) {
      if ((*it).getWeight() <=
        componentsMap[u32C1Idx].compare(componentsMap[u32C2Idx], u32K)) {
          list<pair<uint32_t, uint32_t> >::iterator nodesIt;
          for (nodesIt =
            componentsMap[u32C2Idx].getNodesList().begin();
            nodesIt != componentsMap[u32C2Idx].getNodesList().end();
            nodesIt++) {
            labelsMap[*nodesIt] = u32C1Idx;
          }
          componentsMap[u32C1Idx].merge(componentsMap[u32C2Idx]);
          double f64Int = fmax(componentsMap[u32C1Idx].getInt(),
            componentsMap[u32C2Idx].getInt());
          componentsMap[u32C1Idx].setInt(fmax(f64Int, (*it).getWeight()));
          componentsMap.erase(u32C2Idx);
      }
    }
  }
  map<pair<uint32_t, uint32_t>, uint32_t>::iterator labelsIt;
  for (labelsIt = labelsMap.begin(); labelsIt != labelsMap.end(); labelsIt++)
    if (supportsMap.find((*labelsIt).second) == supportsMap.end())
      supportsMap[(*labelsIt).second] =
        componentsMap[(*labelsIt).second].getNodesList().size();
}
