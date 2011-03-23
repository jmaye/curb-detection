#include "DEMVisitor.h"

#include "DEM.h"
#include "Cell.h"

#include <GL/gl.h>

#include <iostream>
#include <fstream>
#include <map>

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
  const vector<Cell>& cellsVector = dem->getCellsVector();
  map<uint32_t, Color>::iterator it;
  srand(time(NULL));
  map<uint32_t, Color> colorMap;
  for (uint32_t i = 0; i < dem->getLabelsNbr(); i++) {
    Color color;
    color.mRedColorByte = round((double)rand() / (double)RAND_MAX * 255.0);
    color.mGreenColorByte = round((double)rand() / (double)RAND_MAX * 255.0);
    color.mBlueColorByte = round((double)rand() / (double)RAND_MAX * 255.0);
    colorMap[i] = color;
  }
  for (uint32_t i = 0; i < cellsVector.size(); i++) {
    uint32_t u32LabelIdx = cellsVector[i].getMAPLabelsDist();
    glColor3f(colorMap[u32LabelIdx].mRedColorByte,
      colorMap[u32LabelIdx].mGreenColorByte,
      colorMap[u32LabelIdx].mBlueColorByte);
    cellsVector[i].accept(*this);
  }
  glEndList();
  mGLListVector.push_back(glListIdx);
}

void DEMVisitor::visit(const Cell* cell) const {
  if (cell->getInvalidFlag() == false) {
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
