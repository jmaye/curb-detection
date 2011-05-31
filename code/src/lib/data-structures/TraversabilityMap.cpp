#include "data-structures/TraversabilityMap.h"

#include <iostream>
#include <fstream>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

TraversabilityMap::TraversabilityMap() {
}

TraversabilityMap::~TraversabilityMap() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void TraversabilityMap::read(std::istream& stream) {
}

void TraversabilityMap::write(std::ostream& stream) const {
}

void TraversabilityMap::read(std::ifstream& stream) {
}

void TraversabilityMap::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream, const TraversabilityMap& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, TraversabilityMap& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream,
  const TraversabilityMap& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, TraversabilityMap& obj) {
  obj.read(stream);
  return stream;
}
