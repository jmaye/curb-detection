#include "misc/CurbFinder.h"

#include <iostream>
#include <fstream>

void CurbFinder::find(const DEM& dem,
  const std::multiset<Edge, EdgeCompare>& edgeSet, CurbMap& curbMap) {
  std::multiset<Edge>::const_iterator it;
  for (it = edgeSet.begin(); it != edgeSet.end(); it++) {
    const Cell& cell1 = dem((*it).getNode1().first, (*it).getNode1().second);
    const Cell& cell2 = dem((*it).getNode2().first, (*it).getNode2().second);
    if (cell1.getInvalidFlag() == false && cell2.getInvalidFlag() == false) {
      uint32_t u32Label1 = cell1.getMAPLabelsDist();
      uint32_t u32Label2 = cell2.getMAPLabelsDist();
      if (u32Label1 != u32Label2) {
        Point3D curbPoint((cell1.getCellCenter().mf64X +
          cell2.getCellCenter().mf64X) / 2, (cell1.getCellCenter().mf64Y +
          cell2.getCellCenter().mf64Y) / 2, (cell1.getHeightDist().getMean() +
          cell2.getHeightDist().getMean()) / 2);
        curbMap.insert(curbPoint);
      }
    }
  }
}
