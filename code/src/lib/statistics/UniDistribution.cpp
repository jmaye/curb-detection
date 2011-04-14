#include "UniDistribution.h"

#include <iostream>
#include <fstream>

using namespace std;

UniDistribution::UniDistribution() {
}

UniDistribution::~UniDistribution() {
}

void UniDistribution::read(istream& stream) {
}

void UniDistribution::write(ostream& stream) const {
}

void UniDistribution::read(ifstream& stream) {
}

void UniDistribution::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream, const UniDistribution& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream, UniDistribution& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream, const UniDistribution& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream, UniDistribution& obj) {
  obj.read(stream);
  return stream;
}
