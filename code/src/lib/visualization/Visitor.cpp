#include "Visitor.h"

#include <iostream>
#include <fstream>

#include <stdint.h>

using namespace std;

Visitor::Visitor() {
}

Visitor::~Visitor() {
}

void Visitor::read(istream& stream) {
}

void Visitor::write(ostream& stream) const {
}

void Visitor::read(ifstream& stream) {
}

void Visitor::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream,
  const Visitor& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream,
  Visitor& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream,
  const Visitor& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream,
  Visitor& obj) {
  obj.read(stream);
  return stream;
}

void Visitor::draw() const {
  for (uint32_t i = 0; i < mGLListVector.size(); i++)
    glCallList(mGLListVector[i]);
}
