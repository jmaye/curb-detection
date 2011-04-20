#include "ConnectivityMapVisitor.h"

#include "ConnectivityMap.h"

#include <iostream>
#include <fstream>

#include <stdint.h>

using namespace std;

ConnectivityMapVisitor::ConnectivityMapVisitor() {
}

ConnectivityMapVisitor::~ConnectivityMapVisitor() {
}

void ConnectivityMapVisitor::read(istream& stream) {
}

void ConnectivityMapVisitor::write(ostream& stream) const {
}

void ConnectivityMapVisitor::read(ifstream& stream) {
}

void ConnectivityMapVisitor::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream, const ConnectivityMapVisitor& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream, ConnectivityMapVisitor& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream, const ConnectivityMapVisitor& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream, ConnectivityMapVisitor& obj) {
  obj.read(stream);
  return stream;
}

void ConnectivityMapVisitor::visit(const ConnectivityMap* connectivityMap) {
  GLuint glListIdx = glGenLists(1);
  glNewList(glListIdx, GL_COMPILE);
  glPointSize(2.0);
  glBegin(GL_LINES);
  glColor3f(0, 0, 0);
  const std::vector<std::pair<Point3D, Point3D> >& edgePositionsVector = 
    connectivityMap->getEdgePositionsVector();
  for (uint32_t i = 0; i < edgePositionsVector.size(); i++) {
    glVertex3f(edgePositionsVector[i].first.mf64X,
      edgePositionsVector[i].first.mf64Y, edgePositionsVector[i].first.mf64Z);
    glVertex3f(edgePositionsVector[i].second.mf64X,
      edgePositionsVector[i].second.mf64Y, edgePositionsVector[i].second.mf64Z);
  }
  glEnd();
  glEndList();
  mGLListVector.push_back(glListIdx);
}
