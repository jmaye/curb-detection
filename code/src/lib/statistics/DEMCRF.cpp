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
  const vector<double>& variancesVector, const vector<double>& weightsVector)
  throw (OutOfBoundException) {
  vector<Cell> cellsVector = dem.getCellsVector();
  SetNbFeatures(5);
  SetNbParameters(5, 5);
  for (uint32_t i = 0; i < cellsVector.size(); i++) {
    if (cellsVector[i].getInvalidFlag() == false) {
      Vector featureVector;
      featureVector.PushBack(cellsVector[i].getHeightDist().getMean());
      featureVector.PushBack(cellsVector[i].getHeightDist().getVariance());
      featureVector.PushBack(cellsVector[i].getCellCenter().mf64X);
      featureVector.PushBack(cellsVector[i].getCellCenter().mf64Y);
      featureVector.PushBack(cellsVector[i].getMAPLabelsDist());
      uint32_t u32NodeId =
        AddNode(featureVector, cellsVector[i].getMAPLabelsDist());
      mIdMap[i] = u32NodeId;
    }
  }
  for (uint32_t i = 0; i < cellsVector.size(); i++) {
    if (cellsVector[i].getInvalidFlag() == false) {
      Vector labelsDistVectorCRF(GetNbClasses());
      const vector<double>& labelsDistVector =
        cellsVector[i].getLabelsDistVector();
      map<int, uint>const& labelMap = GetLabelMap();
      map<int, uint>::const_iterator it;
      for (uint32_t j = 0; j < GetNbClasses(); j++) {
        it = labelMap.find(j);
        labelsDistVectorCRF[(*it).second] = labelsDistVector[j];
      }
      SetLabelDistribution(mIdMap[i], labelsDistVectorCRF);
    }
  }
  multiset<Edge>::iterator setIt;
  for (setIt = edgeSet.begin(); setIt != edgeSet.end(); setIt++) {
    if (mIdMap.find((*setIt).getNode1Idx()) == mIdMap.end() ||
      mIdMap.find((*setIt).getNode2Idx()) == mIdMap.end())
      continue;
    AddEdge(mIdMap[(*setIt).getNode1Idx()], mIdMap[(*setIt).getNode2Idx()]);
  }
  mVariancesVector = variancesVector;
  mCoeffsMatrix = coeffsMatrix;
  mWeightsVector = weightsVector;
  if (GetNbClasses() > variancesVector.size() ||
    GetNbClasses() > coeffsMatrix.size() ||
    GetNbClasses() > weightsVector.size())
    throw OutOfBoundException("DEMCRF:DEMCRF(): invalid input arguments");
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
  const vector<double>& coeffVector = mCoeffsMatrix[i32Label];
  Map<VectorXd> coeffVectorMapped(&coeffVector[0], coeffVector.size());
  VectorXd dataVector(coeffVector.size());
  Vector featureVector = GetNodeFeatures(u32NodeId);
  dataVector(0) = 1;
  dataVector(1) = featureVector[2];
  dataVector(2) = featureVector[3];
  Vector value;
  value.PushBack(mWeightsVector[i32Label] *
    UniGaussian(featureVector[0], featureVector[1]).
    pdf(coeffVectorMapped.dot(dataVector)));
  return value;
}

Vector DEMCRF::FeatureFunction(uint32_t u32NodeId1, uint32_t u32NodeId2,
  int32_t i32Label1, int32_t i32Label2) const {
  Vector featureVector1 = GetNodeFeatures(u32NodeId1);
  Vector featureVector2 = GetNodeFeatures(u32NodeId2);
  Vector value;
  if (i32Label1 == i32Label2) {
    value.PushBack(1 - (1 / (1 + exp(featureVector1[1] + featureVector2[1] -
      fabs(featureVector1[0] - featureVector2[0])))));
  }
  else {
    value.PushBack(1 / (1 + exp(featureVector1[1] + featureVector2[1] -
      fabs(featureVector1[0] - featureVector2[0]))));
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

void DEMCRF::setCoeffsMatrix(const vector<vector<double> >& coeffsMatrix)
  throw (OutOfBoundException) {
 if (GetNbClasses() > coeffsMatrix.size())
    throw OutOfBoundException("DEMCRF:setCoeffsMatrix(): invalid input arguments");
  mCoeffsMatrix = coeffsMatrix;
}

void DEMCRF::setVariancesVector(const vector<double>& variancesVector)
  throw (OutOfBoundException) {
 if (GetNbClasses() > variancesVector.size())
    throw OutOfBoundException("DEMCRF:setCoeffsMatrix(): invalid input arguments");
  mVariancesVector = variancesVector;
}

const vector<double>& DEMCRF::getWeightsVector() const {
  return mWeightsVector;
}

void DEMCRF::setWeightsVector(const vector<double>& weightsVector)
  throw (OutOfBoundException) {
  if (GetNbClasses() > weightsVector.size())
    throw OutOfBoundException("DEMCRF:setCoeffsMatrix(): invalid input arguments");
  mWeightsVector = weightsVector;
}