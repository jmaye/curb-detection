#include "Estimator.h"

#include <iostream>
#include <fstream>

using namespace std;

Estimator::Estimator() {
}

Estimator::~Estimator() {
}

void Estimator::read(istream& stream) {
}

void Estimator::write(ostream& stream) const {
}

void Estimator::read(ifstream& stream) {
}

void Estimator::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream,
  const Estimator& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream,
  Estimator& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream,
  const Estimator& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream,
  Estimator& obj) {
  obj.read(stream);
  return stream;
}
