#include "DEM.h"

#include "Point3D.h"
#include "UniGaussian.h"
#include "MLEstimator.h"
#include "Sensor.h"
#include "DEMCRF.h"

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
    mu32ValidCellsNbr(0),
    mu32LabelsNbr(0) {
  if (u32CellsNbrX == 0 || u32CellsNbrY == 0)
    throw OutOfBoundException("DEM::DEM(): number of cells must be greater than 0");
  if (f64CellSizeX <= 0 || f64CellSizeY <= 0)
    throw OutOfBoundException("DEM::DEM(): cell size must be greater than 0");
  double f64CurX = mf64MinX + mu32CellsNbrX * mf64CellSizeX;
  double f64CurY = (mu32CellsNbrY * mf64CellSizeY) / 2.0;
  for (uint32_t i = 0; i < mu32CellsNbrX; i++) {
    for (uint32_t j = 0; j < mu32CellsNbrY; j++) {
      mCellsVector.push_back(Cell(UniGaussian(0.0,
        Sensor::getNoise(f64CurX, f64CurY, 0)), MLEstimator(),
        Point2D(f64CurX - mf64CellSizeX / 2.0, f64CurY - mf64CellSizeY / 2.0),
        Point2D(mf64CellSizeX, mf64CellSizeY)));
      f64CurY -= mf64CellSizeY;
    }
    f64CurX -= mf64CellSizeX;
    f64CurY = (mu32CellsNbrY * mf64CellSizeY) / 2.0;
  }
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
      getCell(mu32CellsNbrX - 1 - floor((pointsVector[i].mf64X - mf64MinX) /
        mf64CellSizeX), mu32CellsNbrY - 1 - floor((pointsVector[i].mf64Y +
        f64MaxY) / mf64CellSizeY)).addPoint(pointsVector[i].mf64Z);
    }
  }
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

Cell& DEM::getCell(uint32_t u32Row, uint32_t u32Column)
  throw (OutOfBoundException) {
  if (u32Row >= mu32CellsNbrX || u32Column >= mu32CellsNbrY)
    throw OutOfBoundException("DEM::getCell(): invalid indices");
  return mCellsVector[u32Row * mu32CellsNbrY + u32Column];
}

const Cell& DEM::getCell(uint32_t u32Row, uint32_t u32Column) const
  throw (OutOfBoundException) {
  if (u32Row >= mu32CellsNbrX || u32Column >= mu32CellsNbrY)
    throw OutOfBoundException("DEM::getCell(): invalid indices");
  return mCellsVector[u32Row * mu32CellsNbrY + u32Column];
}
