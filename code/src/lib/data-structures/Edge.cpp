#include "Edge.h"

#include <iostream>
#include <fstream>

using namespace std;

Edge::Edge(double f64Weight, const pair<uint32_t, uint32_t>& node1,
  const pair<uint32_t, uint32_t>& node2) throw (OutOfBoundException)
  : mf64Weight(f64Weight),
    mNode1(node1),
    mNode2(node2) {
  if (f64Weight <= 0) {
    cerr << "f64Weight: " << f64Weight << endl;
    throw OutOfBoundException("Edge::Edge(): weight must be greater than 0");
  }
}

Edge::Edge(const Edge& other) : mf64Weight(other.mf64Weight),
                                mNode1(other.mNode1),
                                mNode2(other.mNode2) {
}

Edge& Edge::operator = (const Edge& other) {
  mf64Weight = other.mf64Weight;
  mNode1 = other.mNode1;
  mNode2 = other.mNode2;
  return *this;
}

Edge::~Edge() {
}

void Edge::read(istream& stream) {
}

void Edge::write(ostream& stream) const {
}

void Edge::read(ifstream& stream) {
}

void Edge::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream,
  const Edge& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream,
  Edge& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream,
  const Edge& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream,
  Edge& obj) {
  obj.read(stream);
  return stream;
}

double Edge::getWeight() const {
  return mf64Weight;
}

const pair<uint32_t, uint32_t>& Edge::getNode1() const {
  return mNode1;
}

const pair<uint32_t, uint32_t>& Edge::getNode2() const {
  return mNode2;
}

void Edge::setWeight(double f64Weight) throw (OutOfBoundException) {
  if (f64Weight <= 0) {
    cerr << "f64Weight: " << f64Weight << endl;
    throw OutOfBoundException("Edge::setWeight(): weight must be greater than 0");
  }
  mf64Weight = f64Weight;
}

void Edge::setNode1(const pair<uint32_t, uint32_t>& node1) {
  mNode1 = node1;
}

void Edge::setNode2(const pair<uint32_t, uint32_t>& node2) {
  mNode2 = node2;
}
