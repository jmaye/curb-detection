#include "DEMVisitor.h"

#include "DEM.h"
#include "Cell.h"

#include <GL/gl.h>

#include <iostream>
#include <fstream>

#include <stdint.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

DEMVisitor::DEMVisitor() {
}

DEMVisitor::~DEMVisitor() {
}

void DEMVisitor::read(istream& stream) {
}

void DEMVisitor::write(ostream& stream) const {
}

void DEMVisitor::read(ifstream& stream) {
}

void DEMVisitor::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream,
  const DEMVisitor& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream,
  DEMVisitor& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream,
  const DEMVisitor& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream,
  DEMVisitor& obj) {
  obj.read(stream);
  return stream;
}

void DEMVisitor::visit(const DEM* dem) {
  GLuint glListIdx = glGenLists(1);
  glNewList(glListIdx, GL_COMPILE);
  glPointSize(2.0);
  map<uint32_t, Color>::iterator it;
  srand(time(NULL));
  for (uint32_t i = 0; i < dem->getLabelsNbr(); i++) {
    Color color;
    setColor(color);
    mColorMap[i] = color;
  }
  for (uint32_t i = 0; i < dem->getCellsNbrX(); i++) {
    for (uint32_t j =  0; j < dem->getCellsNbrY(); j++) {
      dem->getCell(i, j).accept(*this);
    }
  }
  glEndList();
  mGLListVector.push_back(glListIdx);
}

void DEMVisitor::visit(const Cell* cell) const {
  map<uint32_t, Color>::const_iterator it;
  if (cell->getInvalidFlag() == false) {
    uint32_t u32LabelIdx = cell->getMAPLabelsDist();
    it = mColorMap.find(u32LabelIdx);
    Color color = (*it).second;
    glColor3f(color.mRedColorByte, color.mGreenColorByte, color.mBlueColorByte);
    Point2D cellCenter = cell->getCellCenter();
    Point2D cellSize = cell->getCellSize();
    double f64CellHeightMean = cell->getHeightDist().getMean();
    glBegin(GL_POLYGON);
    glVertex3f(cellCenter.mf64X + cellSize.mf64X / 2.0,
      cellCenter.mf64Y + cellSize.mf64Y / 2.0, f64CellHeightMean);
    glVertex3f(cellCenter.mf64X + cellSize.mf64X / 2.0,
      cellCenter.mf64Y - cellSize.mf64Y / 2.0, f64CellHeightMean);
    glVertex3f(cellCenter.mf64X - cellSize.mf64X / 2.0,
      cellCenter.mf64Y - cellSize.mf64Y / 2.0, f64CellHeightMean);
    glVertex3f(cellCenter.mf64X - cellSize.mf64X / 2.0,
      cellCenter.mf64Y + cellSize.mf64Y / 2.0, f64CellHeightMean);
    glEnd();
  }
}

void DEMVisitor::setColor(Color& color) {
  double f64H = ((double)rand() / (double)RAND_MAX) * 360.0;
  double f64S = 1.0;
  double f64V = 1.0;
  f64H /= 60.0;
  int i32I = floor(f64H);
  double f64F =  f64H - i32I;
  double f64P = f64V * (1 - f64S);
  double f64Q = f64V * (1 - f64S * f64F);
  double f64T = f64V * (1 - f64S * (1 - f64F));

  switch (i32I) {
    case 0:
      color.mRedColorByte = f64V ;
      color.mGreenColorByte = f64T;
      color.mBlueColorByte = f64P;
      break;
    case 1:
      color.mRedColorByte = f64Q;
      color.mGreenColorByte = f64V;
      color.mBlueColorByte = f64P;
      break;
    case 2:
      color.mRedColorByte = f64P;
      color.mGreenColorByte = f64V;
      color.mBlueColorByte = f64T;
      break;
    case 3:
      color.mRedColorByte = f64P;
      color.mGreenColorByte = f64Q;
      color.mBlueColorByte = f64V;
      break;
    case 4:
      color.mRedColorByte = f64T;
      color.mGreenColorByte = f64P;
      color.mBlueColorByte = f64V;
      break;
    default:
      color.mRedColorByte = f64V;
      color.mGreenColorByte = f64P;
      color.mBlueColorByte = f64Q;
      break;
  }
}
