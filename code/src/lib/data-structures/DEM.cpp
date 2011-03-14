#include "DEM.h"

#include <ANN/ANN.h>

#include <iostream>
#include <fstream>

using namespace std;

DEM::DEM(const PointCloud& pointCloud, double f64CellSizeX, double f64CellSizeY,
  uint32_t u32CellsNbrX, uint32_t u32CellsNbrY, double f64MinX,
  double f64HeightMax, double f64HeightMin) : mf64CellSizeX(f64CellSizeX),
                                              mf64CellSizeY(f64CellSizeY),
                                              mu32CellsNbrX(u32CellsNbrX),
                                              mu32CellsNbrY(u32CellsNbrY),
                                              mf64MinX(f64MinX),
                                              mf64HeightMax(f64HeightMax),
                                              mf64HeightMin(f64HeightMin) {
  ANNpointArray cellCenters = annAllocPts(mu32CellsNbrX * mu32CellsNbrY, 2);
  double f64CurX = mf64MinX + mu32CellsNbrX * mf64CellSizeX;
  double f64CurY = (mu32CellsNbrY * mf64CellSizeY) / 2.0;
  for (uint32_t i = 0; i < mu32CellsNbrX; i++) {
    for (uint32_t j = 0; j < mu32CellsNbrY; j++) {
      Cell cell;
      cell.mf64HeightMean = 0;
      cell.mf64HeightVariance = 0;
      cell.mu32PointsNbr = 0;
      cell.mf64CenterX = f64CurX - mf64CellSizeX / 2.0;
      cell.mf64CenterY = f64CurY - mf64CellSizeY / 2.0;
      mCellVector.push_back(cell);
      f64CurY -= mf64CellSizeY;
      ANNpoint cellCenter = annAllocPt(2);
      cellCenter[0] = cell.mf64CenterX;
      cellCenter[1] = cell.mf64CenterY;
      cellCenters[i * mu32CellsNbrY + j] = cellCenter;
    }
    f64CurX -= mf64CellSizeX;
    f64CurY = (mu32CellsNbrY * mf64CellSizeY) / 2.0;
  }
  ANNkd_tree* kdTree = new ANNkd_tree(cellCenters,
    mu32CellsNbrX * mu32CellsNbrY, 2);
  ANNidxArray nnIdxArray = new ANNidx[1];
  ANNdistArray distArray = new ANNdist[1];
  vector<PointCloud::Point3D> pointVector = pointCloud.getPointVector();
  for (uint32_t i = 0; i < pointVector.size(); i++) {
    if (pointVector[i].mf64Z <= mf64HeightMax &&
      pointVector[i].mf64Z >= mf64HeightMin) {
      ANNpoint queryPoint = annAllocPt(2);
      queryPoint[0] = pointVector[i].mf64X;
      queryPoint[1] = pointVector[i].mf64Y;
      kdTree->annkSearch(queryPoint, 1, nnIdxArray, distArray, 0);
      mCellVector[nnIdxArray[0]].addPoint(pointVector[i].mf64Z);
    }
  }
  delete [] nnIdxArray;
  delete [] distArray;
  delete kdTree;
  annClose();
}

DEM::~DEM() {
}

void DEM::read(istream& stream) {
}

void DEM::write(ostream& stream) const {
}

void DEM::read(ifstream& stream) {
}

void DEM::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream,
  const DEM& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream,
  DEM& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream,
  const DEM& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream,
  DEM& obj) {
  obj.read(stream);
  return stream;
}

const std::vector<DEM::Cell>& DEM::getCellVector() const {
  return mCellVector;
}
