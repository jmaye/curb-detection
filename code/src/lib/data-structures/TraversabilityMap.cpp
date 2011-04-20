#include "TraversabilityMap.h"

#include <iostream>
#include <fstream>

using namespace std;

TraversabilityMap::TraversabilityMap() {
}

TraversabilityMap::~TraversabilityMap() {
}

void TraversabilityMap::read(istream& stream) {
}

void TraversabilityMap::write(ostream& stream) const {
}

void TraversabilityMap::read(ifstream& stream) {
}

void TraversabilityMap::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream,
  const TraversabilityMap& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream,
  TraversabilityMap& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream,
  const TraversabilityMap& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream,
  TraversabilityMap& obj) {
  obj.read(stream);
  return stream;
}
