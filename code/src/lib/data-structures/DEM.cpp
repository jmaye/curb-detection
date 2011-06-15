/******************************************************************************
 * Copyright (C) 2011 by Jerome Maye                                          *
 * jerome.maye@gmail.com                                                      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

#include "data-structures/DEM.h"

#include "data-structures/Point3D.h"
#include "statistics/UniGaussian.h"
#include "statistics/MLEstimator.h"
#include "sensor/Sensor.h"
#include "statistics/BeliefPropagation.h"

#include <iostream>
#include <fstream>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

DEM::DEM(double f64CellSizeX, double f64CellSizeY, uint32_t u32CellsNbrX,
  uint32_t u32CellsNbrY, double f64HeightFilterMin, double f64HeightFilterMax,
  double f64TranslationX, double f64TranslationY,
  uint32_t u32MinPointsPerPlane) throw (OutOfBoundException) :
  mf64CellSizeX(f64CellSizeX),
  mf64CellSizeY(f64CellSizeY),
  mu32CellsNbrX(u32CellsNbrX),
  mu32CellsNbrY(u32CellsNbrY),
  mf64HeightFilterMin(f64HeightFilterMin),
  mf64HeightFilterMax(f64HeightFilterMax),
  mu32ValidCellsNbr(0),
  mu32LabelsNbr(0),
  mu32MinPointsPerPlane(u32MinPointsPerPlane),
  mf64TranslationX(f64TranslationX),
  mf64TranslationY(f64TranslationY) {
  if (u32CellsNbrX == 0 || u32CellsNbrY == 0) {
    std::cerr << "Requested number of cells: " << "(" << u32CellsNbrX << ","
      << u32CellsNbrY << ")" << std::endl;
    throw OutOfBoundException("DEM::DEM(): number of cells must be greater than 0");
  }
  if (f64CellSizeX <= 0 || f64CellSizeY <= 0) {
    std::cerr << "Requested cell size: " << "(" << f64CellSizeX << ","
      << f64CellSizeY << ")" << std::endl;
    throw OutOfBoundException("DEM::DEM(): cell size must be greater than 0");
  }
  if (mf64HeightFilterMin >= mf64HeightFilterMax) {
    std::cerr << "Requested height filter: " << "(" << f64HeightFilterMin << ","
      << f64HeightFilterMax << ")" << std::endl;
    throw OutOfBoundException("DEM::DEM(): height min must be lower than height max");
  }

  double f64CurX = f64TranslationX + mu32CellsNbrX * mf64CellSizeX;
  double f64CurY = f64TranslationY + mu32CellsNbrY * mf64CellSizeY;
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
    f64CurY = f64TranslationY + mu32CellsNbrY * mf64CellSizeY;
  }
}

DEM::DEM(const DEM& other) :
  mf64CellSizeX(other.mf64CellSizeX),
  mf64CellSizeY(other.mf64CellSizeY),
  mu32CellsNbrX(other.mu32CellsNbrX),
  mu32CellsNbrY(other.mu32CellsNbrY),
  mf64HeightFilterMin(other.mf64HeightFilterMin),
  mf64HeightFilterMax(other.mf64HeightFilterMax),
  mCellsMatrix(other.mCellsMatrix),
  mu32ValidCellsNbr(other.mu32ValidCellsNbr),
  mu32LabelsNbr(other.mu32LabelsNbr),
  mu32MinPointsPerPlane(other.mu32MinPointsPerPlane),
  mf64TranslationX(other.mf64TranslationX),
  mf64TranslationY(other.mf64TranslationY) {
}

DEM& DEM::operator = (const DEM& other) {
  mf64CellSizeX = other.mf64CellSizeX;
  mf64CellSizeY = other.mf64CellSizeY;
  mu32CellsNbrX = other.mu32CellsNbrX;
  mu32CellsNbrY = other.mu32CellsNbrY;
  mf64HeightFilterMin = other.mf64HeightFilterMin;
  mf64HeightFilterMax = other.mf64HeightFilterMax;
  mCellsMatrix = other.mCellsMatrix;
  mu32ValidCellsNbr = other.mu32ValidCellsNbr;
  mu32LabelsNbr = other.mu32LabelsNbr;
  mu32MinPointsPerPlane = other.mu32MinPointsPerPlane;
  mf64TranslationX = other.mf64TranslationX;
  mf64TranslationY = other.mf64TranslationY;
  return *this;
}

DEM::~DEM() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void DEM::read(std::istream& stream) {
}

void DEM::write(std::ostream& stream) const {
}

void DEM::read(std::ifstream& stream) {
}

void DEM::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream, const DEM& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, DEM& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream, const DEM& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, DEM& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

uint32_t DEM::getCellsNbrX() const {
  return mu32CellsNbrX;
}

uint32_t DEM::getCellsNbrY() const {
  return mu32CellsNbrY;
}

void DEM::setInitialLabels(
  const std::map<std::pair<uint32_t, uint32_t>, uint32_t>& labelsMap,
  const std::map<uint32_t, uint32_t>& supportsMap)
  throw (InvalidOperationException) {
  if (labelsMap.size() != mu32CellsNbrX * mu32CellsNbrY) {
    std::cerr << "Labeling size: " << labelsMap.size() << " Cells number: "
      << mu32CellsNbrX * mu32CellsNbrY << std::endl;
    throw InvalidOperationException("DEM::setInitialLabels(): inconsistent labeling");
  }

  std::map<uint32_t, uint32_t>::const_iterator it;
  std::map<uint32_t, uint32_t> labelsConvertedMap;
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
      std::map<std::pair<uint32_t, uint32_t>, uint32_t>::const_iterator it =
        labelsMap.find(std::make_pair(i, j));
      if ((*this)(i, j).getMLEstimator().getPointsNbr() == 0 ||
        labelsConvertedMap.find((*it).second) ==
        labelsConvertedMap.end()) {
        mu32ValidCellsNbr--;
      }
      else {
        (*this)(i, j).setInvalidFlag(false);
        std::vector<double> labelsDistVector(labelsConvertedMap.size(), 0);
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

void DEM::setLabelsDist(const BeliefPropagation& bp, double f64Tol) {
  std::vector<uint32_t> supportPointsVector(mu32LabelsNbr);
  for (uint32_t i = 0; i < mu32CellsNbrX; i++) {
    for (uint32_t j = 0; j < mu32CellsNbrY; j++) {
      if ((*this)(i, j).getInvalidFlag() == false) {
        std::vector<double> distVector =
          bp.getNodeDistribution(std::make_pair(i, j));
        for (uint32_t k = 0; k < distVector.size(); k++) {
          if (distVector[k] > f64Tol)
            supportPointsVector[k]++;
        }
      }
    }
  }

  for (uint32_t i = 0; i < mu32CellsNbrX; i++) {
    for (uint32_t j = 0; j < mu32CellsNbrY; j++) {
      if ((*this)(i, j).getInvalidFlag() == false) {
        std::vector<double> distVector =
          bp.getNodeDistribution(std::make_pair(i, j));
        std::vector<double> newDistVector;
        double f64Sum = 0;
        for (uint32_t k = 0; k < distVector.size(); k++) {
          if (supportPointsVector[k] >= mu32MinPointsPerPlane) {
            newDistVector.push_back(distVector[k]);
            f64Sum += distVector[k];
          }
        }
        for (uint32_t k = 0; k < newDistVector.size(); k++) {
          newDistVector[k] /= f64Sum;
        }
        (*this)(i, j).setLabelsDistVector(newDistVector);
        mu32LabelsNbr = newDistVector.size();
      }
    }
  }
}

void DEM::setMAPState(const BeliefPropagation& bp) {
  for (uint32_t i = 0; i < mu32CellsNbrX; i++) {
    for (uint32_t j = 0; j < mu32CellsNbrY; j++) {
      if ((*this)(i, j).getInvalidFlag() == false) {
        uint32_t u32MAPState = bp.getMAPState(std::make_pair(i, j));
        (*this)(i, j).setMAPState(u32MAPState);
      }
    }
  }
}

Cell& DEM::operator () (uint32_t u32Row, uint32_t u32Column)
  throw (OutOfBoundException) {
  if (u32Row >= mu32CellsNbrX || u32Column >= mu32CellsNbrY) {
    std::cerr << "Requesting: (" << u32Row << "," << u32Column << ")"
      << " Number of rows: " << mu32CellsNbrX << " Number of columns: "
      << mu32CellsNbrY << std::endl;
    throw OutOfBoundException("DEM::operator (): invalid indices");
  }
  return mCellsMatrix[u32Row][u32Column];
}

const Cell& DEM::operator () (uint32_t u32Row, uint32_t u32Column) const
  throw (OutOfBoundException) {
  if (u32Row >= mu32CellsNbrX || u32Column >= mu32CellsNbrY) {
    std::cerr << "Requesting: (" << u32Row << "," << u32Column << ")"
      << " Number of rows: " << mu32CellsNbrX << " Number of columns: "
      << mu32CellsNbrY << std::endl;
    throw OutOfBoundException("DEM::operator (): invalid indices");
  }
  return mCellsMatrix[u32Row][u32Column];
}

void DEM::setMinPointsPerPlane(uint32_t u32MinPointsPerPlane)
  throw (OutOfBoundException) {
  if (u32MinPointsPerPlane < 3) {
    std::cerr << "Requesting: " << u32MinPointsPerPlane << std::endl;
    throw OutOfBoundException("DEM::setMinPointsPerPlane(): a plane must contain at least 3 points");
  }
  mu32MinPointsPerPlane = u32MinPointsPerPlane;
}

uint32_t DEM::getMinPointsPerPlane() const {
  return mu32MinPointsPerPlane;
}

double DEM::getCellSizeX() const {
  return mf64CellSizeX;
}

double DEM::getCellSizeY() const {
  return mf64CellSizeY;
}

double DEM::getHeightFilterMin() const {
  return mf64HeightFilterMin;
}

double DEM::getHeightFilterMax() const {
  return mf64HeightFilterMax;
}

double DEM::getTranslationX() const {
  return mf64TranslationX;
}

double DEM::getTranslationY() const {
  return mf64TranslationY;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void DEM::addPointCloud(const PointCloud& pointCloud) {
  double f64MaxX = mf64TranslationX + mu32CellsNbrX * mf64CellSizeX;
  double f64MinX = mf64TranslationX;
  double f64MaxY = mf64TranslationY + mu32CellsNbrY * mf64CellSizeY;
  double f64MinY = mf64TranslationY;
  for (uint32_t i = 0; i < pointCloud.getSize(); i++) {
    const Point3D& point3D = pointCloud[i];
    if (point3D.mf64Z < mf64HeightFilterMax &&
      point3D.mf64Z > mf64HeightFilterMin &&
      point3D.mf64X < f64MaxX &&
      point3D.mf64X > f64MinX &&
      point3D.mf64Y < f64MaxY &&
      point3D.mf64Y > f64MinY) {
      (*this)(mu32CellsNbrX - ceil((point3D.mf64X - mf64TranslationX) /
        mf64CellSizeX), mu32CellsNbrY - ceil((point3D.mf64Y - mf64TranslationY)
        / mf64CellSizeY)).addPoint(point3D.mf64Z);
    }
  }
}

void DEM::clear() {
  for (uint32_t i = 0; i < mu32CellsNbrX; i++) {
    for (uint32_t j = 0; j < mu32CellsNbrY; j++) {
      (*this)(i, j).clear();
    }
  }
  mu32ValidCellsNbr = 0;
  mu32LabelsNbr = 0;
}
