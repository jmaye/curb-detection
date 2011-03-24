#include "DEMCRF.h"

#include "Cell.h"

#include <iostream>
#include <fstream>
#include <map>

using namespace std;

DEMCRF::DEMCRF(const DEM& dem, const multiset<Edge, EdgeCompare>& edgeSet,
  const vector<vector<double> >& coeffsMatrix,
  const vector<double>& variancesVector) {
  vector<Cell> cellsVector = dem.getCellsVector();
  SetNbFeatures(2);
  SetNbParameters(2, 2);
  map<uint32_t,uint32_t> idMap;
  for (uint32_t i = 0; i < cellsVector.size(); i++) {
    if (cellsVector[i].getInvalidFlag() == false) {
      Vector featureVector;
      featureVector.PushBack(cellsVector[i].getHeightDist().getMean());
      featureVector.PushBack(cellsVector[i].getHeightDist().getVariance());
      uint32_t u32NodeID =
        AddNode(featureVector, cellsVector[i].getMAPLabelsDist());
      SetLabelDistribution(u32NodeID, Vector(&(cellsVector[i].
        getLabelsDistVector()[0]), cellsVector[i].
        getLabelsDistVector().size()));
      idMap[i] = u32NodeID;
    }
  }
  std::multiset<Edge>::iterator it;
  for (it = edgeSet.begin(); it != edgeSet.end(); it++) {
    AddEdge(idMap[(*it).getNode1Idx()], idMap[(*it).getNode2Idx()]);
  }
}

DEMCRF::~DEMCRF() {
}

void DEMCRF::read(istream& stream) {
}

void DEMCRF::write(ostream& stream) const {
}

void DEMCRF::read(ifstream& stream) {
}

void DEMCRF::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream,
  const DEMCRF& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream,
  DEMCRF& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream,
  const DEMCRF& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream,
  DEMCRF& obj) {
  obj.read(stream);
  return stream;
}

Vector DEMCRF::FeatureFunction(uint32_t u32NodeId, int32_t i32Label) const {
  return Vector(1);
}

Vector DEMCRF::FeatureFunction(uint32_t u32NodeId1, uint32_t u32NodeId2,
  int32_t i32Label1, int32_t i32Label2) const {
  return Vector(1);
}
