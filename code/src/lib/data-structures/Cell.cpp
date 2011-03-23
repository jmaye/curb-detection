#include "Cell.h"

#include <iostream>
#include <fstream>

using namespace std;

Cell::Cell(const UniGaussian& heightDist, const MLEstimator& estimator,
  const Point2D& cellCenter, const Point2D& cellSize)
  : mHeightDist(heightDist),
    mMLEstimator(estimator),
    mCellCenter(cellCenter),
    mCellSize(cellSize),
    mbInvalidFlag(false) {
}

Cell::Cell(const Cell& other) : mHeightDist(other.mHeightDist),
                                mMLEstimator(other.mMLEstimator),
                                mCellCenter(other.mCellCenter),
                                mCellSize(other.mCellSize),
                                mLabelsDistVector(other.mLabelsDistVector),
                                mbInvalidFlag(other.mbInvalidFlag) {
}

Cell& Cell::operator = (const Cell& other) {
  mHeightDist = other.mHeightDist;
  mMLEstimator = other.mMLEstimator;
  mCellCenter = other.mCellCenter;
  mCellSize = other.mCellSize;
  mLabelsDistVector = other.mLabelsDistVector;
  mbInvalidFlag = other.mbInvalidFlag;
  return *this;
}

Cell::~Cell() {
}

void Cell::read(istream& stream) {
}

void Cell::write(ostream& stream) const {
}

void Cell::read(ifstream& stream) {
}

void Cell::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream,
  const Cell& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream,
  Cell& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream,
  const Cell& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream,
  Cell& obj) {
  obj.read(stream);
  return stream;
}

void Cell::addPoint(double f64Height) {
  mMLEstimator.addDataPoint(mHeightDist, f64Height);
}

void Cell::accept(const DEMVisitor& v) const {
  v.visit(this);
}

double Cell::compare(const Cell& other) const {
  return mHeightDist.KLDivergence(other.getHeightDist()) +
    other.getHeightDist().KLDivergence(mHeightDist);
}

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

void Cell::setCellSize(const Point2D& cellSize) {
  mCellSize = cellSize;
}

const vector<double>& Cell::getLabelsDistVector() const {
  return mLabelsDistVector;
}

void Cell::setLabelsDistVector(const std::vector<double>& labelsDistVector) {
  mLabelsDistVector = labelsDistVector;
}

uint32_t Cell::getMAPLabelsDist() const {
  double f64LargestValue = -1.0;
  uint32_t u32LargestIdx = 0;
  for (uint32_t i = 0; i < mLabelsDistVector.size(); i++)
    if (mLabelsDistVector[i] > f64LargestValue) {
      f64LargestValue = mLabelsDistVector[i];
      u32LargestIdx = i;
    }
  return u32LargestIdx;
}

bool Cell::getInvalidFlag() const {
  return mbInvalidFlag;
}

void Cell::setInvalidFlag(bool bInvalidFlag) {
  mbInvalidFlag = bInvalidFlag;
}
