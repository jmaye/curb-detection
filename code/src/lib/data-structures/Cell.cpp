#include "Cell.h"

#include <iostream>
#include <fstream>

#include <math.h>

using namespace std;

Cell::Cell() {
}

Cell::Cell(const Cell& other) : mf64HeightMean(other.mf64HeightMean),
                                mf64HeightVariance(other.mf64HeightVariance),
                                mLabelVector(other.mLabelVector),
                                mf64CenterX(other.mf64CenterX),
                                mf64CenterY(other.mf64CenterY),
                                mf64CellSizeX(other.mf64CellSizeX),
                                mf64CellSizeY(other.mf64CellSizeY),
                                mu32PointsNbr(other.mu32PointsNbr) {
}

Cell& Cell::operator = (const Cell& other) {
  mf64HeightMean = other.mf64HeightMean;
  mf64HeightVariance = other.mf64HeightVariance;
  mLabelVector = other.mLabelVector;
  mf64CenterX = other.mf64CenterX;
  mf64CenterY = other.mf64CenterY;
  mf64CellSizeX = other.mf64CellSizeX;
  mf64CellSizeY = other.mf64CellSizeY;
  mu32PointsNbr = other.mu32PointsNbr;
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
  mu32PointsNbr++;
  mf64HeightMean += 1.0 / (double)mu32PointsNbr *
    (f64Height - mf64HeightMean);
  mf64HeightVariance += 1.0 / (double)mu32PointsNbr *
    (pow(f64Height - mf64HeightMean, 2) - mf64HeightVariance);
}

void Cell::accept(const DEMVisitor& v) const {
  v.visit(this);
}
