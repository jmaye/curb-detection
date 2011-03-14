#include "DEM.h"

#include <iostream>
#include <fstream>

using namespace std;

DEM::DEM() {
}

DEM::~DEM() {
}

void DEM::read(istream& stream) {
}

void DEM::write(ostream& stream) const {
}

void DEM::read(ifstream& stream) {
}

void DEM::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream,
  const DEM& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream,
  DEM& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream,
  const DEM& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream,
  DEM& obj) {
  obj.read(stream);
  return stream;
}
