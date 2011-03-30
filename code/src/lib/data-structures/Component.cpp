#include "Component.h"

#include <iostream>
#include <fstream>

#include <math.h>

using namespace std;

Component::Component() : mf64Int(0) {
}

Component::Component(uint32_t u32Idx) : mf64Int(0) {
  mNodesIndexList.push_back(u32Idx);
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

double Component::compare(const Component& other, uint32_t u32K) const
  throw (InvalidOperationException){
  if (mNodesIndexList.size() == 0 || other.mNodesIndexList.size() == 0)
    throw InvalidOperationException("Component::compare(): one of the component is empty");
  return fmin(mf64Int +
    (double)u32K / (double)mNodesIndexList.size(),
    other.mf64Int +
    (double)u32K / (double)other.mNodesIndexList.size());
}

double Component::getInt() const {
  return mf64Int;
}

list<uint32_t>& Component::getNodesIndexList() {
  return mNodesIndexList;
}

void Component::setInt(double f64Int) throw (OutOfBoundException) {
  if (f64Int < 0)
    throw OutOfBoundException("Component::setInt(): value must be greater than 0");
  mf64Int = f64Int;
}

void Component::setNodesIndexList(const list<uint32_t>& nodesIndexList) {
  mNodesIndexList = nodesIndexList;
}

void Component::merge(Component& other) {
  mNodesIndexList.merge(other.getNodesIndexList());
}
