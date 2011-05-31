#include "statistics/UniDistribution.h"

#include <iostream>
#include <fstream>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

UniDistribution::UniDistribution() {
}

UniDistribution::~UniDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void UniDistribution::read(std::istream& stream) {
}

void UniDistribution::write(std::ostream& stream) const {
}

void UniDistribution::read(std::ifstream& stream) {
}

void UniDistribution::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream, const UniDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, UniDistribution& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream, const UniDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, UniDistribution& obj) {
  obj.read(stream);
  return stream;
}
