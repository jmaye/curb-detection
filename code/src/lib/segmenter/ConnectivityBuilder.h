#ifndef CONNECTIVITYBUILDER_H
#define CONNECTIVITYBUILDER_H

#include "DEM.h"
#include "Edge.h"

#include <set>
#include <vector>

#include <math.h>

class ConnectivityBuilder {
  ConnectivityBuilder();

public:
  static void build(const DEM& dem, std::multiset<Edge, EdgeCompare>& edgeSet) {
    uint32_t u32CurRow = 0;
    uint32_t u32CurColumn = 0;
    uint32_t u32CellsNbrX = dem.getCellsNbrX();
    uint32_t u32CellsNbrY = dem.getCellsNbrY();
    const std::vector<Cell>& cellsVector = dem.getCellsVector();
    for (uint32_t i = 0; i < cellsVector.size(); i++) {
      if (cellsVector[i].mu32PointsNbr != 0) {
        uint32_t u32IdxDown = (u32CurRow + 1) * u32CellsNbrY + u32CurColumn;
        if (u32CurRow < u32CellsNbrX &&
          cellsVector[u32IdxDown].mu32PointsNbr != 0) {
          Edge edge;
          double f64Mu1 = cellsVector[i].mf64HeightMean;
          double f64Mu2 = cellsVector[u32IdxDown].mf64HeightMean;
          double f64Var1 = cellsVector[i].mf64HeightVariance;
          double f64Var2 = cellsVector[u32IdxDown].mf64HeightVariance;
          edge.mf64Weight = pow(f64Mu1 - f64Mu2, 2) / (2 * f64Var2) +
            1 / 2 * (f64Var1 / f64Var2 - 1 - log(f64Var1 / f64Var2)) +
            pow(f64Mu2 - f64Mu1, 2) / (2 * f64Var1) +
            1 / 2 * (f64Var2 / f64Var1 - 1 - log(f64Var2 / f64Var1));
          edge.mu32Node1Idx = i;
          edge.mu32Node2Idx = u32IdxDown;
          edgeSet.insert(edge);
        }
        uint32_t u32IdxRight = u32CurRow * u32CellsNbrY + u32CurColumn + 1;
        if (u32CurColumn < u32CellsNbrY &&
          cellsVector[u32IdxRight].mu32PointsNbr != 0) {
          Edge edge;
          double f64Mu1 = cellsVector[i].mf64HeightMean;
          double f64Mu2 = cellsVector[u32IdxRight].mf64HeightMean;
          double f64Var1 = cellsVector[i].mf64HeightVariance;
          double f64Var2 = cellsVector[u32IdxRight].mf64HeightVariance;
          edge.mf64Weight = pow(f64Mu1 - f64Mu2, 2) / (2 * f64Var2) +
            1 / 2 * (f64Var1 / f64Var2 - 1 - log(f64Var1 / f64Var2)) +
            pow(f64Mu2 - f64Mu1, 2) / (2 * f64Var1) +
            1 / 2 * (f64Var2 / f64Var1 - 1 - log(f64Var2 / f64Var1));
          edge.mu32Node1Idx = i;
          edge.mu32Node2Idx = u32IdxRight;
          edgeSet.insert(edge);
        }
      }
      u32CurColumn++;
      if (u32CurColumn == u32CellsNbrY) {
        u32CurColumn = 0;
        u32CurRow++;
      }
    }
  }

protected:

};

#endif // CONNECTIVITYBUILDER_H
