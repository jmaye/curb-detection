#include "data-structures/CurbMap.h"

#include <iostream>
#include <fstream>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

CurbMap::CurbMap() {
}

CurbMap::~CurbMap() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void CurbMap::read(std::istream& stream) {
}

void CurbMap::write(std::ostream& stream) const {
}

void CurbMap::read(std::ifstream& stream) {
}

void CurbMap::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream, const CurbMap& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, CurbMap& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream, const CurbMap& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, CurbMap& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

const std::vector<Point3D>& CurbMap::getCurbPointsVector() const {
  return mCurbPointsVector;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void CurbMap::insert(Point3D curbPoint) {
  mCurbPointsVector.push_back(curbPoint);
}
