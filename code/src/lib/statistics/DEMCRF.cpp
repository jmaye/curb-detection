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
        for (uint32_t k = 0; k < dem.getLabelsNbr(); k++) {
          const vector<double>& coeffVector = coeffsMatrix[k];
          Map<VectorXd> coeffVectorMapped(&coeffVector[0], coeffVector.size());
          VectorXd dataVector(coeffVector.size());
          dataVector(0) = 1;
          dataVector(1) = cell.getCellCenter().mf64X;
          dataVector(2) = cell.getCellCenter().mf64Y;
          mDataMap[make_pair(u32NodeId, k)] = weightsVector[k] *
            UniGaussian(coeffVectorMapped.dot(dataVector),
            variancesVector[k] + cell.getHeightDist().getVariance()).
            pdf(cell.getHeightDist().getMean());
        }
      }
    }
  }
  multiset<Edge>::iterator setIt;
  for (setIt = edgeSet.begin(); setIt != edgeSet.end(); setIt++) {
    if (mIdMap.find((*setIt).getNode1()) == mIdMap.end() ||
      mIdMap.find((*setIt).getNode2()) == mIdMap.end())
      continue;
    AddEdge(mIdMap[(*setIt).getNode1()], mIdMap[(*setIt).getNode2()]);
    Vector featureVector1 = GetNodeFeatures(mIdMap[(*setIt).getNode1()]);
    Vector featureVector2 = GetNodeFeatures(mIdMap[(*setIt).getNode2()]);
    mDistanceMap[make_pair(mIdMap[(*setIt).getNode1()],
      mIdMap[(*setIt).getNode2()])] = 1 - (1 / (1 + exp((featureVector1[1] +
      featureVector2[1]) - fabs(featureVector1[0] - featureVector2[0]))));
    mDistanceMap[make_pair(mIdMap[(*setIt).getNode2()],
      mIdMap[(*setIt).getNode1()])] = 1 - (1 / (1 + exp((featureVector1[1] +
      featureVector2[1]) - fabs(featureVector1[0] - featureVector2[0]))));
  }
  mVariancesVector = variancesVector;
  mCoeffsMatrix = coeffsMatrix;
  mWeightsVector = weightsVector;
  if (GetNbClasses() > variancesVector.size() ||
    GetNbClasses() > coeffsMatrix.size() ||
    GetNbClasses() > weightsVector.size()) {
    cerr << "CRF number of classes: " << GetNbClasses() << endl;
    cerr << "Linear regression number of classes (variances): " << variancesVector.size() << endl;
    cerr << "Linear regression number of classes (coefficients): " << coeffsMatrix.size() << endl;
    cerr << "Linear regression number of classes (weights): " << weightsVector.size() << endl;
    throw OutOfBoundException("DEMCRF:DEMCRF(): inconsistent number of classes with respect to linear regression inputs");
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
  Vector value;
  value.PushBack((*mDataMap.find(make_pair(u32NodeId, i32Label))).second);
  return value;
}

Vector DEMCRF::FeatureFunction(uint32_t u32NodeId1, uint32_t u32NodeId2,
  int32_t i32Label1, int32_t i32Label2) const {
  Vector value;
  value.PushBack((*mDistanceMap.find(make_pair(u32NodeId1, u32NodeId2))).
    second);
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

void DEMCRF::updateNodesPotentials() {
  for(NodeIterator node = NodesBegin(); node != NodesEnd(); node++) {
    for (uint32_t i = 0; i < GetNbClasses(); i++) {
      const vector<double>& coeffVector = mCoeffsMatrix[i];
      if (coeffVector.size() == 0)
        mDataMap[make_pair(node->GetID(), i)] = 0;
      else {
        Map<VectorXd> coeffVectorMapped(&coeffVector[0], coeffVector.size());
        VectorXd dataVector(coeffVector.size());
        Vector featureVector = GetNodeFeatures(node->GetID());
        dataVector(0) = 1;
        dataVector(1) = featureVector[2];
        dataVector(2) = featureVector[3];
        mDataMap[make_pair(node->GetID(), i)] = mWeightsVector[i] *
          UniGaussian(coeffVectorMapped.dot(dataVector), mVariancesVector[i] +
          featureVector[1]).pdf(featureVector[0]);
      }
    }
  }
}

void DEMCRF::setCoeffsMatrix(const vector<vector<double> >& coeffsMatrix)
  throw (OutOfBoundException) {
 if (GetNbClasses() > coeffsMatrix.size()) {
    cerr << "CRF number of classes: " << GetNbClasses() << endl;
    cerr << "Linear regression number of classes (coefficients): " << coeffsMatrix.size() << endl;
    throw OutOfBoundException("DEMCRF:setCoeffsMatrix(): inconsistent number of classes with respect to linear regression inputs");
  }
  mCoeffsMatrix = coeffsMatrix;
}

void DEMCRF::setVariancesVector(const vector<double>& variancesVector)
  throw (OutOfBoundException) {
 if (GetNbClasses() > variancesVector.size()) {
    cerr << "CRF number of classes: " << GetNbClasses() << endl;
    cerr << "Linear regression number of classes (variances): " << variancesVector.size() << endl;
    throw OutOfBoundException("DEMCRF:setCoeffsMatrix(): inconsistent number of classes with respect to linear regression inputs");
  }
  mVariancesVector = variancesVector;
}

const vector<double>& DEMCRF::getWeightsVector() const {
  return mWeightsVector;
}

void DEMCRF::setWeightsVector(const vector<double>& weightsVector)
  throw (OutOfBoundException) {
  if (GetNbClasses() > weightsVector.size()) {
    cerr << "CRF number of classes: " << GetNbClasses() << endl;
    cerr << "Linear regression number of classes (weights): " << weightsVector.size() << endl;
    throw OutOfBoundException("DEMCRF:setCoeffsMatrix(): inconsistent number of classes with respect to linear regression inputs");
  }
  mWeightsVector = weightsVector;
}
