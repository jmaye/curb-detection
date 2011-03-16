#include "Edge.h"

#include <iostream>
#include <fstream>

using namespace std;

Edge::Edge() {
}

Edge::Edge(const Edge& other) : mf64Weight(other.mf64Weight),
                                mu32Node1Idx(other.mu32Node1Idx),
                                mu32Node2Idx(other.mu32Node2Idx) {
}

Edge& Edge::operator = (const Edge& other) {
  mf64Weight = other.mf64Weight;
  mu32Node1Idx = other.mu32Node1Idx;
  mu32Node2Idx = other.mu32Node2Idx;
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
