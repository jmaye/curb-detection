#include "BayesianEstimator.h"

#include <iostream>
#include <fstream>

using namespace std;

BayesianEstimator::BayesianEstimator() {
}

BayesianEstimator::~BayesianEstimator() {
}

void BayesianEstimator::read(istream& stream) {
}

void BayesianEstimator::write(ostream& stream) const {
}

void BayesianEstimator::read(ifstream& stream) {
}

void BayesianEstimator::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream,
  const BayesianEstimator& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream,
  BayesianEstimator& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream,
  const BayesianEstimator& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream,
  BayesianEstimator& obj) {
  obj.read(stream);
  return stream;
}
