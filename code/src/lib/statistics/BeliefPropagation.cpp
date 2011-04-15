#include "BeliefPropagation.h"

#include "Cell.h"
#include "UniGaussian.h"

#include <Eigen/Core>

#include <iostream>
#include <fstream>

using namespace Eigen;
using namespace std;

BeliefPropagation::BeliefPropagation(const DEM& dem,
  const multiset<Edge, EdgeCompare>& edgeSet) : mbInferenceDone(false) {
  vector<dai::Var> vars;
  vars.resize(dem.getValidCellsNbr());
  vector<dai::Factor> factors;
  factors.reserve(dem.getValidCellsNbr() + edgeSet.size());
  uint32_t u32NodeIdx = 0;
  for (uint32_t i = 0; i < dem.getCellsNbrX(); i++) {
    for (uint32_t j = 0; j < dem.getCellsNbrY(); j++) {
      const Cell& cell = dem(i, j);
      if (cell.getInvalidFlag() == false) {
        vars[u32NodeIdx] = dai::Var(u32NodeIdx, dem.getLabelsNbr());
        dai::Factor fac(vars[u32NodeIdx]);
        factors.push_back(fac);
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
    dai::Factor fac(dai::VarSet(vars[mIdMap[(*setIt).getNode1()]],
      vars[mIdMap[(*setIt).getNode2()]]), 1e-12);
    for(uint32_t i = 0; i < dem.getLabelsNbr(); i++)
      fac.set(i * (dem.getLabelsNbr() + 1), 1 - f64Diff);
    factors.push_back(fac);
  }
  mFactorGraph = dai::FactorGraph(factors.begin(), factors.end(), vars.begin(),
    vars.end(), factors.size(), vars.size());
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
  const vector<vector<double> >& coeffsMatrix,
  const vector<double>& variancesVector,
  const vector<double>& weightsVector) throw (OutOfBoundException) {
  if (dem.getLabelsNbr() != coeffsMatrix.size() ||
    dem.getLabelsNbr() != variancesVector.size() ||
    dem.getLabelsNbr() != weightsVector.size())
    throw OutOfBoundException("BeliefPropagation::infer(): incompatible dem");
  for (uint32_t i = 0; i < dem.getCellsNbrX(); i++) {
    for (uint32_t j = 0; j < dem.getCellsNbrY(); j++) {
      const Cell& cell = dem(i, j);
      if (cell.getInvalidFlag() == false) {
        map<pair<uint32_t, uint32_t>, uint32_t>::const_iterator it =
          mIdMap.find(make_pair(i, j));
        if (it == mIdMap.end())
          throw OutOfBoundException("BeliefPropagation::infer(): incompatible dem");
        dai::Factor fac = mFactorGraph.factor((*it).second);
        for (uint32_t k = 0; k < dem.getLabelsNbr(); k++) {
          const vector<double>& coeffVector = coeffsMatrix[k];
          if (coeffVector.size() == 0)
            fac.set(k, 0);
          else {
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
        }
        mFactorGraph.setFactor((*it).second, fac);
      }
    }
  }
  size_t maxiter = 10000;
  dai::Real tol = 1e-9;
  size_t verb = 1;
  dai::PropertySet opts;
  opts.set("maxiter", maxiter);
  opts.set("tol", tol);
  opts.set("verbose", verb);
  opts.set("updates", string("SEQRND"));
  opts.set("logdomain", false);
  opts.set("inference", string("SUMPROD"));
  mBP = dai::BP(mFactorGraph, opts);
  mBP.init();
  mBP.run();
  mbInferenceDone = true;
  cout << mBP.logZ() << endl;
}

vector<double> BeliefPropagation::
  getNodeDistribution(pair<uint32_t, uint32_t> nodeCoordinates) const
  throw (OutOfBoundException) {
  if (mbInferenceDone == false)
    throw OutOfBoundException("BeliefPropagation::getNodeDistribution(): inference has to run first");
  map<pair<uint32_t, uint32_t>, uint32_t>::const_iterator it =
    mIdMap.find(nodeCoordinates);
  if (it == mIdMap.end()) {
    cerr << "Requesting: (" << nodeCoordinates.first << ","
         << nodeCoordinates.second << ")";
    throw OutOfBoundException("BeliefPropagation::getNodeDistribution(): invalid indices");
  }
  return mBP.beliefV((*it).second).p().p();
}
