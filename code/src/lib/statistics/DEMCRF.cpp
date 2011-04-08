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
  SetNbFeatures(4);
  SetNbParameters(4, 4);
  for (uint32_t i = 0; i < dem.getCellsNbrX(); i++) {
    for (uint32_t j = 0; j < dem.getCellsNbrY(); j++) {
      const Cell& cell = dem(i, j);
      if (cell.getInvalidFlag() == false) {
        Vector featureVector;
        featureVector.PushBack(cell.getHeightDist().getMean());
        featureVector.PushBack(cell.getHeightDist().getVariance());
        featureVector.PushBack(cell.getCellCenter().mf64X);
        featureVector.PushBack(cell.getCellCenter().mf64Y);
        uint32_t u32NodeId = AddNode(featureVector, cell.getMAPLabelsDist());
        mIdMap[make_pair(i, j)] = u32NodeId;
      }
    }
  }
//  for (uint32_t i = 0; i < dem.getCellsNbrX(); i++) {
//    for (uint32_t j = 0; j < dem.getCellsNbrY(); j++) {
//      const Cell& cell = dem(i, j);
//      if (cell.getInvalidFlag() == false) {
//        Vector labelsDistVectorCRF(GetNbClasses());
//        const vector<double>& labelsDistVector = cell.getLabelsDistVector();
//        map<int, uint>const& labelMap = GetLabelMap();
//        map<int, uint>::const_iterator it;
//        for (uint32_t k = 0; k < GetNbClasses(); k++) {
//          it = labelMap.find(k);
//          labelsDistVectorCRF[(*it).second] = labelsDistVector[k];
//        }
//        SetLabelDistribution(mIdMap[make_pair(i, j)],
//          labelsDistVectorCRF);
//      }
//    }
//  }
  multiset<Edge>::iterator setIt;
  for (setIt = edgeSet.begin(); setIt != edgeSet.end(); setIt++) {
    if (mIdMap.find((*setIt).getNode1()) == mIdMap.end() ||
      mIdMap.find((*setIt).getNode2()) == mIdMap.end())
      continue;
    AddEdge(mIdMap[(*setIt).getNode1()], mIdMap[(*setIt).getNode2()]);
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
  value.PushBack(1 - 1 / (1 +
    UniGaussian(coeffVectorMapped.dot(dataVector),
    featureVector[1]).pdf(featureVector[0])));
  return value;
}

Vector DEMCRF::FeatureFunction(uint32_t u32NodeId1, uint32_t u32NodeId2,
  int32_t i32Label1, int32_t i32Label2) const {
  Vector featureVector1 = GetNodeFeatures(u32NodeId1);
  Vector featureVector2 = GetNodeFeatures(u32NodeId2);
  Vector value;
  if (i32Label1 == i32Label2) {
    value.PushBack(1 - (1 / (1 + exp((featureVector1[1] + featureVector2[1]) -
      fabs(featureVector1[0] - featureVector2[0])))));
  }
  else {
    value.PushBack((1 / (1 + exp((featureVector1[1] + featureVector2[1]) -
      fabs(featureVector1[0] - featureVector2[0])))));
  }
  return value;
}

const map<pair<uint32_t, uint32_t>, uint32_t>& DEMCRF::getIdMap() const {
  return mIdMap;
}

void DEMCRF::setIdMap(const map<pair<uint32_t, uint32_t>, uint32_t>& idMap) {
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
