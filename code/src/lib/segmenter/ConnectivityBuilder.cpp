#include "ConnectivityBuilder.h"

#include <vector>

#include <stdint.h>

using namespace std;

void ConnectivityBuilder::build(const DEM& dem,
  multiset<Edge, EdgeCompare>& edgeSet) {
  uint32_t u32CurRow = 0;
  uint32_t u32CurColumn = 0;
  uint32_t u32CellsNbrX = dem.getCellsNbrX();
  uint32_t u32CellsNbrY = dem.getCellsNbrY();
  const std::vector<Cell>& cellsVector = dem.getCellsVector();
  for (uint32_t i = 0; i < cellsVector.size(); i++) {
    if (cellsVector[i].getMLEstimator().getPointsNbr() != 0) {
      uint32_t u32IdxDown = (u32CurRow + 1) * u32CellsNbrY + u32CurColumn;
      if (u32CurRow < u32CellsNbrX &&
        cellsVector[u32IdxDown].getMLEstimator().getPointsNbr() != 0) {
        edgeSet.insert(Edge(cellsVector[i].compare(cellsVector[u32IdxDown]),
          i, u32IdxDown));
      }
      uint32_t u32IdxRight = u32CurRow * u32CellsNbrY + u32CurColumn + 1;
      if (u32CurColumn < u32CellsNbrY &&
        cellsVector[u32IdxRight].getMLEstimator().getPointsNbr() != 0) {
        edgeSet.insert(Edge(cellsVector[i].compare(cellsVector[u32IdxRight]),
          i, u32IdxRight));
      }
    }
    u32CurColumn++;
    if (u32CurColumn == u32CellsNbrY) {
      u32CurColumn = 0;
      u32CurRow++;
    }
  }
}
