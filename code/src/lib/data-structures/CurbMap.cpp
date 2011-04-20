#include "CurbMap.h"

#include <iostream>
#include <fstream>

using namespace std;

CurbMap::CurbMap(const DEM& dem) {
}

CurbMap::~CurbMap() {
}

void CurbMap::read(istream& stream) {
}

void CurbMap::write(ostream& stream) const {
}

void CurbMap::read(ifstream& stream) {
}

void CurbMap::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream,
  const CurbMap& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream,
  CurbMap& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream,
  const CurbMap& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream,
  CurbMap& obj) {
  obj.read(stream);
  return stream;
}
