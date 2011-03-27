#include "DEM.h"

#include "Point3D.h"
#include "UniGaussian.h"
#include "MLEstimator.h"
#include "Sensor.h"
#include "DEMCRF.h"

#include <ANN/ANN.h>

#include <iostream>
#include <fstream>

using namespace std;

DEM::DEM(const PointCloud& pointCloud, double f64CellSizeX, double f64CellSizeY,
  uint32_t u32CellsNbrX, uint32_t u32CellsNbrY, double f64MinX,
  double f64HeightMin, double f64HeightMax) throw (OutOfBoundException)
  : mf64CellSizeX(f64CellSizeX),
    mf64CellSizeY(f64CellSizeY),
    mu32CellsNbrX(u32CellsNbrX),
    mu32CellsNbrY(u32CellsNbrY),
    mf64MinX(f64MinX),
    mf64HeightMin(f64HeightMin),
    mf64HeightMax(f64HeightMax),
    mu32ValidCellsNbr(u32CellsNbrX * u32CellsNbrY),
    mu32LabelsNbr(0) {
  if (f64CellSizeX <= 0 || f64CellSizeY <= 0)
    throw OutOfBoundException("DEM::DEM(): cell size must be greater than 0");
  ANNpointArray cellCenters = annAllocPts(mu32CellsNbrX * mu32CellsNbrY, 2);
  double f64CurX = mf64MinX + mu32CellsNbrX * mf64CellSizeX;
  double f64CurY = (mu32CellsNbrY * mf64CellSizeY) / 2.0;
  for (uint32_t i = 0; i < mu32CellsNbrX; i++) {
    for (uint32_t j = 0; j < mu32CellsNbrY; j++) {
      mCellsVector.push_back(Cell(UniGaussian(0.0,
        Sensor::getNoise(f64CurX, f64CurY, 0)), MLEstimator(),
        Point2D(f64CurX - mf64CellSizeX / 2.0, f64CurY - mf64CellSizeY / 2.0),
        Point2D(mf64CellSizeX, mf64CellSizeY)));
      ANNpoint cellCenter = annAllocPt(2);
      cellCenter[0] = f64CurX - mf64CellSizeX / 2.0;
      cellCenter[1] = f64CurY - mf64CellSizeY / 2.0;
      cellCenters[i * mu32CellsNbrY + j] = cellCenter;
      f64CurY -= mf64CellSizeY;
    }
    f64CurX -= mf64CellSizeX;
    f64CurY = (mu32CellsNbrY * mf64CellSizeY) / 2.0;
  }
  ANNkd_tree* kdTree = new ANNkd_tree(cellCenters,
    mu32CellsNbrX * mu32CellsNbrY, 2);
  ANNidxArray nnIdxArray = new ANNidx[1];
  ANNdistArray distArray = new ANNdist[1];
  const vector<Point3D>& pointsVector = pointCloud.getPointsVector();
  double f64MaxX = mf64MinX + mu32CellsNbrX * mf64CellSizeX;
  double f64MaxY = (mu32CellsNbrY * mf64CellSizeY) / 2.0;
  double f64MinY = - f64MaxY;
  for (uint32_t i = 0; i < pointsVector.size(); i++) {
    if (pointsVector[i].mf64Z <= mf64HeightMax &&
      pointsVector[i].mf64Z >= mf64HeightMin &&
      pointsVector[i].mf64X <= f64MaxX &&
      pointsVector[i].mf64X >= mf64MinX &&
      pointsVector[i].mf64Y <= f64MaxY &&
      pointsVector[i].mf64Y >= f64MinY) {
      ANNpoint queryPoint = annAllocPt(2);
      queryPoint[0] = pointsVector[i].mf64X;
      queryPoint[1] = pointsVector[i].mf64Y;
      kdTree->annkSearch(queryPoint, 1, nnIdxArray, distArray, 0);
      mCellsVector[nnIdxArray[0]].addPoint(pointsVector[i].mf64Z);
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

const vector<Cell>& DEM::getCellsVector() const {
  return mCellsVector;
}

uint32_t DEM::getCellsNbrX() const {
  return mu32CellsNbrX;
}

uint32_t DEM::getCellsNbrY() const {
  return mu32CellsNbrY;
}

void DEM::accept(DEMVisitor& v) const {
  v.visit(this);
}

void DEM::setInitialLabelsVector(const vector<uint32_t>& labelsVector,
  const map<uint32_t, uint32_t>& supportsMap)
  throw (InvalidOperationException) {
  if (labelsVector.size() != mCellsVector.size())
    throw InvalidOperationException("DEM::setInitialLabelsVector(): wrong input arguments");
  mInitialLabelsVector = labelsVector;
  map<uint32_t, uint32_t>::const_iterator it;
  map<uint32_t, uint32_t> labelsMap;
  uint32_t i = 0;
  for (it = supportsMap.begin(); it != supportsMap.end(); it++) {
    if ((*it).second >= 3) {
      labelsMap[(*it).first] = i++;
    }
  }
  mu32LabelsNbr = labelsMap.size();
  mu32ValidCellsNbr = mu32CellsNbrX * mu32CellsNbrY;
  for (uint32_t i = 0; i < mCellsVector.size(); i++) {
    map<uint32_t, uint32_t>::const_iterator it =
      labelsMap.find(labelsVector[i]);
    if (mCellsVector[i].getMLEstimator().getPointsNbr() == 0 ||
      it == labelsMap.end()) {
      mCellsVector[i].setInvalidFlag(true);
      mu32ValidCellsNbr--;
    }
    else {
      vector<double> labelsDistVector(labelsMap.size(), 0);
      labelsDistVector[labelsMap[labelsVector[i]]] = 1.0;
      mCellsVector[i].setLabelsDistVector(labelsDistVector);
    }
  }
}

const vector<uint32_t>& DEM::getInitialLabelsVector() const {
  return mInitialLabelsVector;
}

uint32_t DEM::getValidCellsNbr() const {
  return mu32ValidCellsNbr;
}

void DEM::setValidCellsNbr(uint32_t u32ValidCellsNbr) {
  mu32ValidCellsNbr = u32ValidCellsNbr;
}

uint32_t DEM::getLabelsNbr() const {
  return mu32LabelsNbr;
}

void DEM::setLabelsNbr(uint32_t u32LabelsNbr) {
  mu32LabelsNbr = u32LabelsNbr;
}

void DEM::setLabelsDist(const DEMCRF& crf) throw (OutOfBoundException) {
  const map<uint32_t, uint32_t>& idMap = crf.getIdMap();
  map<uint32_t, uint32_t>::const_iterator it;
  for (uint32_t i = 0; i < mCellsVector.size(); i++) {
    if (mCellsVector[i].getInvalidFlag() == false) {
      it = idMap.find(i);
      if (it == idMap.end())
        throw OutOfBoundException("DEM::setLabelsDist(): invalid input arguments");
      Vector distVectorCRF = crf.GetLabelDistribution((*it).second);
      vector<double> distVector(distVectorCRF.Size(), 0);
      for (uint32_t j = 0; j < distVector.size(); j++)
        distVector[crf.GetClassLabel(j)] = distVectorCRF[j];
      mCellsVector[i].setLabelsDistVector(distVector);
    }
  }
}
