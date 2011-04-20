#include "CurbMapVisitor.h"

#include "CurbMap.h"

#include <iostream>
#include <fstream>

using namespace std;

CurbMapVisitor::CurbMapVisitor() {
}

CurbMapVisitor::~CurbMapVisitor() {
}

void CurbMapVisitor::read(istream& stream) {
}

void CurbMapVisitor::write(ostream& stream) const {
}

void CurbMapVisitor::read(ifstream& stream) {
}

void CurbMapVisitor::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream,
  const CurbMapVisitor& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream,
  CurbMapVisitor& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream,
  const CurbMapVisitor& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream,
  CurbMapVisitor& obj) {
  obj.read(stream);
  return stream;
}

void CurbMapVisitor::visit(const CurbMap* curbMap) {
  GLuint glListIdx = glGenLists(1);
  glNewList(glListIdx, GL_COMPILE);
  glPointSize(10.0);
  glBegin(GL_POINTS);
  glColor3f(0, 0, 0);
  const vector<Point3D>& curbPointsVector = curbMap->getCurbPointsVector();
  for (uint32_t i = 0; i < curbPointsVector.size(); i++) {
    glVertex3f(curbPointsVector[i].mf64X, curbPointsVector[i].mf64Y,
      curbPointsVector[i].mf64Z);
  }
  glEnd();
  glEndList();
  mGLListVector.push_back(glListIdx);
}
