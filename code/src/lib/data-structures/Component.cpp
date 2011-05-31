#include "data-structures/Component.h"

#include <iostream>
#include <fstream>

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Component::Component() : mf64Int(0) {
}

Component::Component(const std::pair<uint32_t, uint32_t>& nodeCoordinates) :
  mf64Int(0) {
  mNodesList.push_back(nodeCoordinates);
}

Component::Component(const Component& other) : mf64Int(other.mf64Int),
                                               mNodesList(other.mNodesList) {
}

Component& Component::operator = (const Component& other) {
  mf64Int = other.mf64Int;
  mNodesList = other.mNodesList;
  return *this;
}

Component::~Component() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Component::read(std::istream& stream) {
}

void Component::write(std::ostream& stream) const {
}

void Component::read(std::ifstream& stream) {
}

void Component::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream, const Component& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, Component& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream, const Component& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, Component& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

double Component::getInt() const {
  return mf64Int;
}

std::list<std::pair<uint32_t, uint32_t> >& Component::getNodesList() {
  return mNodesList;
}

void Component::setInt(double f64Int) throw (OutOfBoundException) {
  if (f64Int < 0) {
    std::cerr << "f64Int: " << f64Int << std::endl;
    throw OutOfBoundException("Component::setInt(): value must be greater than 0");
  }
  mf64Int = f64Int;
}

void Component::setNodesList(const std::list<std::pair<uint32_t, uint32_t> >&
  nodesList) {
  mNodesList = nodesList;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void Component::merge(Component& other) {
  mNodesList.merge(other.getNodesList());
}

double Component::compare(const Component& other, uint32_t u32K) const
  throw (InvalidOperationException){
  if (mNodesList.size() == 0 || other.mNodesList.size() == 0)
    throw InvalidOperationException("Component::compare(): one of the component is empty");
  return fmin(mf64Int +
    (double)u32K / (double)mNodesList.size(),
    other.mf64Int +
    (double)u32K / (double)other.mNodesList.size());
}
