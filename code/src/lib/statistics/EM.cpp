#include "EM.h"

#include "LinearRegressor.h"
#include "BeliefPropagation.h"

#include <iostream>
#include <limits>

using namespace std;

void EM::run(DEM& dem,
  const multiset<Edge, EdgeCompare>& edgeSet,
  vector<vector<double> >& coeffsMatrix,
  vector<double>& variancesVector, vector<double>& weightsVector,
  uint32_t u32MaxEMIterations, double f64EMTol, uint32_t u32MaxBPIterations,
  double f64BPTol) {
  double f64OldLogPartitionSum = -numeric_limits<double>::max();
  for (uint32_t i = 0; i < u32MaxEMIterations; i++) {
    BeliefPropagation bp;
    bp.infer(dem, edgeSet, coeffsMatrix, variancesVector, weightsVector,
      u32MaxBPIterations, f64BPTol);
    dem.setLabelsDist(bp);
    LinearRegressor::estimate(dem, coeffsMatrix, variancesVector,
      weightsVector);
    double f64LogPartitionSum = bp.getLogPartitionSum();
    if (fabs(f64LogPartitionSum - f64OldLogPartitionSum) < f64EMTol)
      break;
    f64OldLogPartitionSum = f64LogPartitionSum;
  }
  BeliefPropagation bp;
  bp.infer(dem, edgeSet, coeffsMatrix, variancesVector, weightsVector,
    u32MaxBPIterations, f64BPTol, true);
  dem.setMAPState(bp);
}
