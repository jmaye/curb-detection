#include "BeliefPropagation.h"

#include "Cell.h"
#include "UniGaussian.h"

#include <Eigen/Core>

#include <iostream>
#include <fstream>

using namespace Eigen;
using namespace std;

BeliefPropagation::BeliefPropagation() : mbInferenceDone(false),
                                         mbMaxProductDone(false) {
}

BeliefPropagation::~BeliefPropagation() {
}

void BeliefPropagation::read(istream& stream) {
}

void BeliefPropagation::write(ostream& stream) const {
}

void BeliefPropagation::read(ifstream& stream) {
}

void BeliefPropagation::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream, const BeliefPropagation& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream, BeliefPropagation& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream, const BeliefPropagation& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream, BeliefPropagation& obj) {
  obj.read(stream);
  return stream;
}

void BeliefPropagation::infer(const DEM& dem,
  const multiset<Edge, EdgeCompare>& edgeSet,
  const vector<vector<double> >& coeffsMatrix,
  const vector<double>& variancesVector,
  const vector<double>& weightsVector, uint32_t u32MaxIter, double f64Tol,
    bool bMaxProd)
  throw (OutOfBoundException) {
  if (dem.getLabelsNbr() != coeffsMatrix.size() ||
    dem.getLabelsNbr() != variancesVector.size() ||
    dem.getLabelsNbr() != weightsVector.size())
    throw OutOfBoundException("BeliefPropagation::infer(): incompatible dem");
  vector<dai::Var> varsVector;
  varsVector.resize(dem.getValidCellsNbr());
  vector<dai::Factor> factorsVector;
  factorsVector.reserve(dem.getValidCellsNbr() + edgeSet.size());
  uint32_t u32NodeIdx = 0;
  for (uint32_t i = 0; i < dem.getCellsNbrX(); i++) {
    for (uint32_t j = 0; j < dem.getCellsNbrY(); j++) {
      const Cell& cell = dem(i, j);
      if (cell.getInvalidFlag() == false) {
        varsVector[u32NodeIdx] = dai::Var(u32NodeIdx, dem.getLabelsNbr());
        dai::Factor fac(varsVector[u32NodeIdx]);
        for (uint32_t k = 0; k < dem.getLabelsNbr(); k++) {
          if (weightsVector[k] != 0) {
            const vector<double>& coeffVector = coeffsMatrix[k];
            Map<VectorXd> coeffVectorMapped(&coeffVector[0],
              coeffVector.size());
            VectorXd dataVector(coeffVector.size());
            dataVector(0) = 1;
            dataVector(1) = cell.getCellCenter().mf64X;
            dataVector(2) = cell.getCellCenter().mf64Y;
            fac.set(k, weightsVector[k] *
              UniGaussian(coeffVectorMapped.dot(dataVector),
              variancesVector[k] + cell.getHeightDist().getVariance()).
              pdf(cell.getHeightDist().getMean()));
          }
          else
            fac.set(k, 0);
        }
        factorsVector.push_back(fac);
        mIdMap[make_pair(i, j)] = u32NodeIdx;
        u32NodeIdx++;
      }
    }
  }
  multiset<Edge>::iterator setIt;
  for (setIt = edgeSet.begin(); setIt != edgeSet.end(); setIt++) {
    if (mIdMap.find((*setIt).getNode1()) == mIdMap.end() ||
      mIdMap.find((*setIt).getNode2()) == mIdMap.end())
      continue;
    double f64Variance1 = dem((*setIt).getNode1().first,
      (*setIt).getNode1().second).getHeightDist().getVariance();
    double f64Variance2 = dem((*setIt).getNode2().first,
      (*setIt).getNode2().second).getHeightDist().getVariance();
    double f64Mean1 = dem((*setIt).getNode1().first,
      (*setIt).getNode1().second).getHeightDist().getMean();
    double f64Mean2 = dem((*setIt).getNode2().first,
      (*setIt).getNode2().second).getHeightDist().getMean();
    double f64Diff = (1 / (1 + exp(f64Variance1 +
        f64Variance2 - fabs(f64Mean1 - f64Mean2))));
    dai::Factor fac(dai::VarSet(varsVector[mIdMap[(*setIt).getNode1()]],
      varsVector[mIdMap[(*setIt).getNode2()]]), 1e-12);
    for(uint32_t i = 0; i < dem.getLabelsNbr(); i++)
      fac.set(i * (dem.getLabelsNbr() + 1), 1 - f64Diff);
    factorsVector.push_back(fac);
  }
  mFactorGraph = dai::FactorGraph(factorsVector);
  size_t maxiter = u32MaxIter;
  dai::Real tol = f64Tol;
  size_t verb = 0;
  dai::PropertySet opts;
  opts.set("maxiter", maxiter);
  opts.set("tol", tol);
  opts.set("verbose", verb);
  opts.set("updates", string("SEQRND"));
  opts.set("logdomain", false);
  if (bMaxProd == false)
    opts.set("inference", string("SUMPROD"));
  else
    opts.set("inference", string("MAXPROD"));
  mBP = dai::BP(mFactorGraph, opts);
  mBP.init();
  mBP.run();
  mbInferenceDone = true;
  if (bMaxProd == true) {
    mMAPStateVector = mBP.findMaximum();
    mbMaxProductDone = true;
  }
}

vector<double> BeliefPropagation::
  getNodeDistribution(const pair<uint32_t, uint32_t>& nodeCoordinates) const
  throw (OutOfBoundException, InvalidOperationException) {
  if (mbInferenceDone == false)
    throw InvalidOperationException("BeliefPropagation::getNodeDistribution(): inference has to run first");
  map<pair<uint32_t, uint32_t>, uint32_t>::const_iterator it =
    mIdMap.find(nodeCoordinates);
  if (it == mIdMap.end()) {
    cerr << "Requesting: (" << nodeCoordinates.first << ","
         << nodeCoordinates.second << ")";
    throw OutOfBoundException("BeliefPropagation::getNodeDistribution(): invalid indices");
  }
  return mBP.beliefV((*it).second).p().p();
}

uint32_t BeliefPropagation::
  getMAPState(const pair<uint32_t, uint32_t>& nodeCoordinates) const
  throw (OutOfBoundException, InvalidOperationException) {
  if (mbInferenceDone == false || mbMaxProductDone == false)
    throw InvalidOperationException("BeliefPropagation::getMAPState(): inference with max-prod has to run first");
  map<pair<uint32_t, uint32_t>, uint32_t>::const_iterator it =
    mIdMap.find(nodeCoordinates);
  if (it == mIdMap.end()) {
    cerr << "Requesting: (" << nodeCoordinates.first << ","
         << nodeCoordinates.second << ")";
    throw OutOfBoundException("BeliefPropagation::getMAPState(): invalid indices");
  }
  return mMAPStateVector[(*it).second];
}

double BeliefPropagation::getLogPartitionSum() const
  throw (InvalidOperationException) {
  if (mbInferenceDone == false)
    throw InvalidOperationException("BeliefPropagation::getLogPartitionSum(): inference has to run first");
  return mBP.logZ();
}
