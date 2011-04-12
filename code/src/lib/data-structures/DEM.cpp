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
  uint32_t u32CellsNbrX, uint32_t u32CellsNbrY, double f64XOffset,
  double f64YOffset, double f64HeightMin, double f64HeightMax,
  uint32_t u32MinPointsPerPlane) throw (OutOfBoundException)
  : mf64CellSizeX(f64CellSizeX),
    mf64CellSizeY(f64CellSizeY),
    mu32CellsNbrX(u32CellsNbrX),
    mu32CellsNbrY(u32CellsNbrY),
    mf64XOffset(f64XOffset),
    mf64YOffset(f64YOffset),
    mf64HeightMin(f64HeightMin),
    mf64HeightMax(f64HeightMax),
    mu32ValidCellsNbr(0),
    mu32LabelsNbr(0),
    mu32MinPointsPerPlane(u32MinPointsPerPlane) {
  if (u32CellsNbrX == 0 || u32CellsNbrY == 0)
    throw OutOfBoundException("DEM::DEM(): number of cells must be greater than 0");
  if (f64CellSizeX <= 0 || f64CellSizeY <= 0)
    throw OutOfBoundException("DEM::DEM(): cell size must be greater than 0");
  double f64CurX = mf64XOffset + mu32CellsNbrX * mf64CellSizeX;
  double f64CurY = mf64YOffset + mu32CellsNbrY * mf64CellSizeY;
  mCellsMatrix.resize(mu32CellsNbrX);
  for (uint32_t i = 0; i < mu32CellsNbrX; i++) {
    for (uint32_t j = 0; j < mu32CellsNbrY; j++) {
      mCellsMatrix[i].push_back(Cell(UniGaussian(0.0,
        Sensor::getNoise(f64CurX, f64CurY, 0)), MLEstimator(),
        Point2D(f64CurX - mf64CellSizeX / 2.0, f64CurY - mf64CellSizeY / 2.0),
        Point2D(mf64CellSizeX, mf64CellSizeY)));
      f64CurY -= mf64CellSizeY;
    }
    f64CurX -= mf64CellSizeX;
    f64CurY = mf64YOffset + mu32CellsNbrY * mf64CellSizeY;
  }
  double f64MaxX = mf64XOffset + mu32CellsNbrX * mf64CellSizeX;
  double f64MinX = mf64XOffset;
  double f64MaxY = mf64YOffset + mu32CellsNbrY * mf64CellSizeY;
  double f64MinY = mf64YOffset;
  for (uint32_t i = 0; i < pointCloud.getSize(); i++) {
    const Point3D& point3D = pointCloud[i];
    if (point3D.mf64Z < mf64HeightMax &&
      point3D.mf64Z > mf64HeightMin &&
      point3D.mf64X < f64MaxX &&
      point3D.mf64X > f64MinX &&
      point3D.mf64Y < f64MaxY &&
      point3D.mf64Y > f64MinY) {
      (*this)(mu32CellsNbrX - 1 - floor((point3D.mf64X - mf64XOffset) /
        mf64CellSizeX),
        mu32CellsNbrY - 1 - floor((point3D.mf64Y - mf64YOffset) /
        mf64CellSizeY)).
        addPoint(point3D.mf64Z);
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

uint32_t DEM::getCellsNbrX() const {
  return mu32CellsNbrX;
}

uint32_t DEM::getCellsNbrY() const {
  return mu32CellsNbrY;
}

void DEM::accept(DEMVisitor& v) const {
  v.visit(this);
}

void DEM::setInitialLabels(const map<pair<uint32_t, uint32_t>, uint32_t>&
  labelsMap, const map<uint32_t, uint32_t>& supportsMap)
  throw (InvalidOperationException) {
  if (labelsMap.size() != mu32CellsNbrX * mu32CellsNbrY)
    throw InvalidOperationException("DEM::setInitialLabels(): wrong input arguments");
  map<uint32_t, uint32_t>::const_iterator it;
  map<uint32_t, uint32_t> labelsConvertedMap;
  uint32_t i = 0;
  for (it = supportsMap.begin(); it != supportsMap.end(); it++) {
    if ((*it).second >= mu32MinPointsPerPlane) {
      labelsConvertedMap[(*it).first] = i++;
    }
  }
  mu32LabelsNbr = labelsConvertedMap.size();
  mu32ValidCellsNbr = mu32CellsNbrX * mu32CellsNbrY;
  for (uint32_t i = 0; i < mu32CellsNbrX; i++) {
    for (uint32_t j = 0; j < mu32CellsNbrY; j++) {
      map<pair<uint32_t, uint32_t>, uint32_t>::const_iterator it =
      labelsMap.find(make_pair(i, j));
      if ((*this)(i, j).getMLEstimator().getPointsNbr() == 0 ||
        labelsConvertedMap.find((*it).second) ==
        labelsConvertedMap.end()) {
        mu32ValidCellsNbr--;
      }
      else {
        (*this)(i, j).setInvalidFlag(false);
        vector<double> labelsDistVector(labelsConvertedMap.size(), 0);
        labelsDistVector[labelsConvertedMap[(*it).second]] = 1.0;
        (*this)(i, j).setLabelsDistVector(labelsDistVector);
      }
    }
  }
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
  const map<pair<uint32_t, uint32_t>, uint32_t>& idMap = crf.getIdMap();
  map<pair<uint32_t, uint32_t>, uint32_t>::const_iterator it;
  for (uint32_t i = 0; i < mu32CellsNbrX; i++) {
    for (uint32_t j = 0; j < mu32CellsNbrY; j++) {
      if ((*this)(i, j).getInvalidFlag() == false) {
        it = idMap.find(make_pair(i, j));
        if (it == idMap.end())
          throw OutOfBoundException("DEM::setLabelsDist(): invalid input arguments");
        Vector distVectorCRF = crf.GetLabelDistribution((*it).second);
        vector<double> distVector(distVectorCRF.Size(), 0);
        for (uint32_t k = 0; k < distVector.size(); k++)
          distVector[crf.GetClassLabel(k)] = distVectorCRF[k];
        (*this)(i, j).setLabelsDistVector(distVector);
      }
    }
  }
}

Cell& DEM::operator () (uint32_t u32Row, uint32_t u32Column)
  throw (OutOfBoundException) {
  if (u32Row >= mu32CellsNbrX || u32Column >= mu32CellsNbrY)
    throw OutOfBoundException("DEM::operator (): invalid indices");
  return mCellsMatrix[u32Row][u32Column];
}

const Cell& DEM::operator () (uint32_t u32Row, uint32_t u32Column) const
  throw (OutOfBoundException) {
  if (u32Row >= mu32CellsNbrX || u32Column >= mu32CellsNbrY)
    throw OutOfBoundException("DEM::operator (): invalid indices");
  return mCellsMatrix[u32Row][u32Column];
}

void DEM::setMinPointsPerPlane(uint32_t u32MinPointsPerPlane) {
  mu32MinPointsPerPlane = u32MinPointsPerPlane;
}

uint32_t DEM::getMinPointsPerPlane() const {
  return mu32MinPointsPerPlane;
}
