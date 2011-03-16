#include "Component.h"

#include <iostream>
#include <fstream>

using namespace std;

Component::Component() {
}

Component::Component(const Component& other)
  : mf64Int(other.mf64Int),
    mNodesIndexList(other.mNodesIndexList) {
}

Component& Component::operator = (const Component& other) {
  mf64Int = other.mf64Int;
  mNodesIndexList = other.mNodesIndexList;
  return *this;
}

Component::~Component() {
}

void Component::read(istream& stream) {
}

void Component::write(ostream& stream) const {
}

void Component::read(ifstream& stream) {
}

void Component::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream,
  const Component& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream,
  Component& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream,
  const Component& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream,
  Component& obj) {
  obj.read(stream);
  return stream;
}
