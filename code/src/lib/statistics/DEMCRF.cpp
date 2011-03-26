#include "DEMCRF.h"

#include "Cell.h"
#include "UniGaussian.h"

#include <Eigen/Core>

#include <iostream>
#include <fstream>

#include <math.h>

using namespace Eigen;
using namespace std;

DEMCRF::DEMCRF(const DEM& dem, const multiset<Edge, EdgeCompare>& edgeSet,
  const vector<vector<double> >& coeffsMatrix,
  const vector<double>& variancesVector) {
  vector<Cell> cellsVector = dem.getCellsVector();
  SetNbFeatures(4);
  SetNbParameters(4, 4);
  for (uint32_t i = 0; i < cellsVector.size(); i++) {
    if (cellsVector[i].getInvalidFlag() == false) {
      Vector featureVector;
      featureVector.PushBack(cellsVector[i].getHeightDist().getMean());
      featureVector.PushBack(cellsVector[i].getHeightDist().getVariance());
      featureVector.PushBack(cellsVector[i].getCellCenter().mf64X);
      featureVector.PushBack(cellsVector[i].getCellCenter().mf64Y);
      uint32_t u32NodeId =
        AddNode(featureVector, cellsVector[i].getMAPLabelsDist());
      SetLabelDistribution(u32NodeId, Vector(&(cellsVector[i].
        getLabelsDistVector()[0]), cellsVector[i].
        getLabelsDistVector().size()));
      mIdMap[i] = u32NodeId;
    }
  }
  multiset<Edge>::iterator it;
  for (it = edgeSet.begin(); it != edgeSet.end(); it++) {
    AddEdge(mIdMap[(*it).getNode1Idx()], mIdMap[(*it).getNode2Idx()]);
  }
  mVariancesVector = variancesVector;
  mCoeffsMatrix = coeffsMatrix;
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
  Vector featureVector = GetNodeFeatures(u32NodeId);
  UniGaussian pointGaussian(featureVector[0], featureVector[1]);
  const vector<double>& coeffVector = mCoeffsMatrix[i32Label];
  Map<VectorXd> coeffVectorMapped(&coeffVector[0], coeffVector.size());
  VectorXd dataVector(coeffVector.size());
  dataVector(0) = 1;
  dataVector(1) = featureVector[2];
  dataVector(2) = featureVector[3];
  UniGaussian planeGaussian(coeffVectorMapped.dot(dataVector),
    mVariancesVector[i32Label]);
  Vector value;
  value.PushBack(pointGaussian.KLDivergence(planeGaussian));
  return value;
}

Vector DEMCRF::FeatureFunction(uint32_t u32NodeId1, uint32_t u32NodeId2,
  int32_t i32Label1, int32_t i32Label2) const {
  Vector featureVector1 = GetNodeFeatures(u32NodeId1);
  Vector featureVector2 = GetNodeFeatures(u32NodeId2);
  Vector value;
  UniGaussian point1Gaussian(featureVector1[0], featureVector1[1]);
  UniGaussian point2Gaussian(featureVector2[0], featureVector2[1]);
  if (i32Label1 == i32Label2) {
    value.PushBack(1 / (point1Gaussian.KLDivergence(point2Gaussian) +
      point2Gaussian.KLDivergence(point1Gaussian)));
  }
  else {
    value.PushBack((point1Gaussian.KLDivergence(point2Gaussian) +
      point2Gaussian.KLDivergence(point1Gaussian)));
  }
  return value;
}

const map<uint32_t, uint32_t>& DEMCRF::getIdMap() const {
  return mIdMap;
}

void DEMCRF::setIdMap(const map<uint32_t, uint32_t>& idMap) {
  mIdMap = idMap;
}

const vector<vector<double> >& DEMCRF::getCoeffsMatrix() const {
  return mCoeffsMatrix;
}

const vector<double>& DEMCRF::getVariancesVector() const {
  return mVariancesVector;
}

void DEMCRF::setCoeffsMatrix(const vector<vector<double> >& coeffsMatrix) {
  mCoeffsMatrix = coeffsMatrix;
}

void DEMCRF::setVariancesVector(const vector<double>& variancesVector) {
  mVariancesVector = variancesVector;
}
