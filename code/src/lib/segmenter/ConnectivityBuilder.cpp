#include "ConnectivityBuilder.h"

#include <stdint.h>

using namespace std;

void ConnectivityBuilder::build(const DEM& dem,
  multiset<Edge, EdgeCompare>& edgeSet) {
  edgeSet.clear();
  for (uint32_t i = 0; i < dem.getCellsNbrX(); i++) {
    for (uint32_t j = 0; j < dem.getCellsNbrY(); j++) {
      if (dem(i, j).getMLEstimator().getPointsNbr() != 0) {
        if ((i + 1) < dem.getCellsNbrX() &&
          dem(i + 1, j).getMLEstimator().getPointsNbr() != 0) {
          edgeSet.insert(Edge(dem(i, j).compare(dem(i + 1, j)),
            make_pair(i, j), make_pair(i + 1, j)));
        }
        if ((j + 1) < dem.getCellsNbrY() &&
          dem(i, j + 1).getMLEstimator().getPointsNbr() != 0) {
          edgeSet.insert(Edge(dem(i, j).compare(dem(i, j + 1)),
            make_pair(i, j), make_pair(i, j + 1)));
        }
      }
    }
  }
}
