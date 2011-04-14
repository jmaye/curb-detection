#include "Component.h"

#include <iostream>
#include <fstream>

#include <math.h>

using namespace std;

Component::Component() : mf64Int(0) {
}

Component::Component(const pair<uint32_t, uint32_t>& nodeCoordinates)
  : mf64Int(0) {
  mNodesList.push_back(nodeCoordinates);
}

Component::Component(const Component& other) : mf64Int(other.mf64Int),
                                               mNodesList(other.mNodesList) {
}

Component& Component::operator = (const Component& other) {
  mf64Int = other.mf64Int;
  mNodesList = other.mNodesList;
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

ostream& operator << (ostream& stream, const Component& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream, Component& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream, const Component& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream, Component& obj) {
  obj.read(stream);
  return stream;
}

double Component::compare(const Component& other, uint32_t u32K) const
  throw (InvalidOperationException){
  if (mNodesList.size() == 0 || other.mNodesList.size() == 0)
    throw InvalidOperationException("Component::compare(): one of the component is empty");
  return fmin(mf64Int +
    (double)u32K / (double)mNodesList.size(),
    other.mf64Int +
    (double)u32K / (double)other.mNodesList.size());
}

double Component::getInt() const {
  return mf64Int;
}

list<pair<uint32_t, uint32_t> >& Component::getNodesList() {
  return mNodesList;
}

void Component::setInt(double f64Int) throw (OutOfBoundException) {
  if (f64Int < 0) {
    cerr << "f64Int: " << f64Int << endl;
    throw OutOfBoundException("Component::setInt(): value must be greater than 0");
  }
  mf64Int = f64Int;
}

void Component::setNodesList(const list<pair<uint32_t, uint32_t> >& nodesList) {
  mNodesList = nodesList;
}

void Component::merge(Component& other) {
  mNodesList.merge(other.getNodesList());
}
