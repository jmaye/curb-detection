#include "EM.h"

#include "LinearRegressor.h"

#include <iostream>

using namespace std;

void EM::run(BeliefPropagation& bp, DEM& dem,
  vector<vector<double> >& coeffsMatrix,
  vector<double>& variancesVector, vector<double>& weightsVector,
  uint32_t u32Iterations) {
  cout << "Initial: " << endl;
  for (uint32_t j = 0; j < coeffsMatrix.size(); j++) {
   cout << "Plane: " << j << ", Variance: " << variancesVector[j]
        << ", Weight: " << weightsVector[j] << endl;
  }
  for (uint32_t i = 0; i < u32Iterations; i++) {
    bp.infer(dem, coeffsMatrix, variancesVector, weightsVector);
    dem.setLabelsDist(bp);
    LinearRegressor::estimate(dem, coeffsMatrix, variancesVector,
      weightsVector);
    cout << "Iteration: " << i << endl;
    for (uint32_t j = 0; j < coeffsMatrix.size(); j++) {
      cout << "Plane: " << j << ", Variance: " << variancesVector[j]
           << ", Weight: " << weightsVector[j] << endl;
    }
  }
}
