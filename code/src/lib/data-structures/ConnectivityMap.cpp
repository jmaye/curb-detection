#include "ConnectivityMap.h"

#include <iostream>
#include <fstream>

using namespace std;

ConnectivityMap::ConnectivityMap(const DEM& dem,
  const multiset<Edge, EdgeCompare>& edgeSet) {
  multiset<Edge>::const_iterator it;
  for (it = edgeSet.begin(); it != edgeSet.end(); it++) {
    const Cell& cell1 = dem((*it).getNode1().first, (*it).getNode1().second);
    const Cell& cell2 = dem((*it).getNode2().first, (*it).getNode2().second);
    if (cell1.getInvalidFlag() == false && cell2.getInvalidFlag() == false) {
      Point3D point1(cell1.getCellCenter().mf64X, cell1.getCellCenter().mf64Y,
        cell1.getHeightDist().getMean());
      Point3D point2(cell2.getCellCenter().mf64X, cell2.getCellCenter().mf64Y,
        cell2.getHeightDist().getMean());
      mEdgePositionsVector.push_back(make_pair(point1, point2));
    }
  }
}

ConnectivityMap::~ConnectivityMap() {
}

void ConnectivityMap::read(istream& stream) {
}

void ConnectivityMap::write(ostream& stream) const {
}

void ConnectivityMap::read(ifstream& stream) {
}

void ConnectivityMap::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream,
  const ConnectivityMap& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream,
  ConnectivityMap& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream,
  const ConnectivityMap& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream,
  ConnectivityMap& obj) {
  obj.read(stream);
  return stream;
}

void ConnectivityMap::accept(ConnectivityMapVisitor& v) const {
  v.visit(this);
}

const vector<pair<Point3D, Point3D> >& ConnectivityMap::getEdgePositionsVector()
  const {
  return mEdgePositionsVector;
}
