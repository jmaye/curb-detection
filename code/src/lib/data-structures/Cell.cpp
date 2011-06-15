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

#include "data-structures/Cell.h"

#include "sensor/Sensor.h"

#include <iostream>
#include <fstream>
#include <limits>

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Cell::Cell(const UniGaussian& heightDist, const MLEstimator& estimator,
  const Point2D& cellCenter, const Point2D& cellSize)
  throw (OutOfBoundException)
  : mHeightDist(heightDist),
    mMLEstimator(estimator),
    mCellCenter(cellCenter),
    mCellSize(cellSize),
    mbInvalidFlag(true),
    mu32MAPState(std::numeric_limits<uint32_t>::max()) {
  if (cellSize.mf64X <= 0 || cellSize.mf64Y <= 0) {
    std::cerr << "Requested cell size: " << "(" << cellSize.mf64X << ","
      << cellSize.mf64Y << ")" << std::endl;
    throw OutOfBoundException("Cell::Cell(): cell size must be positive");
  }
}

Cell::Cell(const Cell& other) : mHeightDist(other.mHeightDist),
                                mMLEstimator(other.mMLEstimator),
                                mCellCenter(other.mCellCenter),
                                mCellSize(other.mCellSize),
                                mbInvalidFlag(other.mbInvalidFlag),
                                mLabelsDistVector(other.mLabelsDistVector),
                                mu32MAPState(other.mu32MAPState) {
}

Cell& Cell::operator = (const Cell& other) {
  mHeightDist = other.mHeightDist;
  mMLEstimator = other.mMLEstimator;
  mCellCenter = other.mCellCenter;
  mCellSize = other.mCellSize;
  mbInvalidFlag = other.mbInvalidFlag;
  mLabelsDistVector = other.mLabelsDistVector;
  mu32MAPState = other.mu32MAPState;
  return *this;
}

Cell::~Cell() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Cell::read(std::istream& stream) {
}

void Cell::write(std::ostream& stream) const {
}

void Cell::read(std::ifstream& stream) {
}

void Cell::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream, const Cell& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, Cell& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream, const Cell& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, Cell& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

const UniGaussian& Cell::getHeightDist() const {
  return mHeightDist;
}

void Cell::setHeightDist(const UniGaussian& heightDist) {
  mHeightDist = heightDist;
}

const MLEstimator& Cell::getMLEstimator() const {
  return mMLEstimator;
}

void Cell::setMLEstimator(const MLEstimator& estimator) {
  mMLEstimator = estimator;
}

const Point2D& Cell::getCellCenter() const {
  return mCellCenter;
}

void Cell::setCellCenter(const Point2D& cellCenter) {
  mCellCenter = cellCenter;
}

const Point2D& Cell::getCellSize() const {
  return mCellSize;
}

void Cell::setCellSize(const Point2D& cellSize) throw (OutOfBoundException) {
  if (cellSize.mf64X <= 0 || cellSize.mf64Y <= 0) {
    std::cerr << "Requested cell size: " << "(" << cellSize.mf64X << ","
      << cellSize.mf64Y << ")" << std::endl;
    throw OutOfBoundException("Cell::setCellSize(): cell size must be positive");
  }
  mCellSize = cellSize;
}

const std::vector<double>& Cell::getLabelsDistVector() const {
  return mLabelsDistVector;
}

void Cell::setLabelsDistVector(const std::vector<double>& labelsDistVector,
  double f64Tol)
  throw (OutOfBoundException) {
  double f64Sum = 0;
  for (uint32_t i = 0; i < labelsDistVector.size(); i++) {
    f64Sum += labelsDistVector[i];
  }
  if (fabs(f64Sum - 1.0) > f64Tol) {
    std::cerr << std::scientific << f64Sum << std::endl;
    throw OutOfBoundException("Cell::setLabelsDistVector(): probability function does not sum to 1");
  }
  mLabelsDistVector = labelsDistVector;
}

uint32_t Cell::getMAPLabelsDist() const throw (InvalidOperationException) {
  if (mLabelsDistVector.size() == 0)
    throw InvalidOperationException("Cell::getMAPLabelsDist(): labels distribution not set");
  if (mu32MAPState == std::numeric_limits<uint32_t>::max()) {
    double f64LargestValue = -std::numeric_limits<double>::max();
    uint32_t u32LargestIdx = 0;
    for (uint32_t i = 0; i < mLabelsDistVector.size(); i++)
      if (mLabelsDistVector[i] > f64LargestValue) {
        f64LargestValue = mLabelsDistVector[i];
        u32LargestIdx = i;
      }
    return u32LargestIdx;
  }
  else {
    return mu32MAPState;
  }
}

void Cell::setMAPState(uint32_t u32MAPState) throw (OutOfBoundException) {
  if (u32MAPState >= mLabelsDistVector.size())
    throw OutOfBoundException("Cell::setMAPState(): invalid MAP state");
  mu32MAPState = u32MAPState;
}

bool Cell::getInvalidFlag() const {
  return mbInvalidFlag;
}

void Cell::setInvalidFlag(bool bInvalidFlag) {
  mbInvalidFlag = bInvalidFlag;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void Cell::addPoint(double f64Height) {
  mMLEstimator.addDataPoint(mHeightDist, f64Height);
}

double Cell::compare(const Cell& other) const {
  return mHeightDist.KLDivergence(other.getHeightDist()) +
    other.getHeightDist().KLDivergence(mHeightDist);
}

void Cell::clear() {
  mHeightDist = UniGaussian(0.0, Sensor::getNoise(mCellCenter.mf64X,
    mCellCenter.mf64Y, 0));
  mMLEstimator = MLEstimator();
  mbInvalidFlag = true;
  mLabelsDistVector.clear();
  mu32MAPState = std::numeric_limits<uint32_t>::max();
}
