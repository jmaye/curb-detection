#include "EM.h"

#include "LinearRegressor.h"

#include <iostream>

using namespace std;

void EM::run(DEMCRF& crf, Vector& nodesWeightsVector,
  Vector& edgesWeightsVector, DEM& dem,
  vector<vector<double> >& coeffsMatrix,
  vector<double>& variancesVector, vector<double>& weightsVector,
  uint32_t u32Iterations) {
  cout << "Initial: " << endl;
  for (uint32_t j = 0; j < crf.GetNbClasses(); j++) {
   cout << "Plane: " << j << ", Variance: " << variancesVector[j]
        << ", Weight: " << weightsVector[j] << endl;
  }
  for (uint32_t i = 0; i < u32Iterations; i++) {
    crf.Inference(nodesWeightsVector, edgesWeightsVector, crf.GetNbClasses());
    dem.setLabelsDist(crf);
    //LinearRegressor::estimate(dem, coeffsMatrix, variancesVector,
      //weightsVector);
    //crf.setCoeffsMatrix(coeffsMatrix);
    //crf.setVariancesVector(variancesVector);
    //crf.setWeightsVector(weightsVector);
    //crf.updateNodesPotentials();
    cout << "Iteration: " << i << endl;
    for (uint32_t j = 0; j < crf.GetNbClasses(); j++) {
      cout << "Plane: " << j << ", Variance: " << variancesVector[j]
           << ", Weight: " << weightsVector[j] << endl;
    }
  }
}

void EM::run(BeliefPropagation& bp, DEM& dem,
  const multiset<Edge, EdgeCompare>& edgeSet,
  vector<vector<double> >& coeffsMatrix,
  vector<double>& variancesVector, vector<double>& weightsVector,
  uint32_t u32Iterations) {
  cout << "Initial: " << endl;
  for (uint32_t j = 0; j < coeffsMatrix.size(); j++) {
   cout << "Plane: " << j << ", Variance: " << variancesVector[j]
        << ", Weight: " << weightsVector[j] << endl;
  }
  for (uint32_t i = 0; i < u32Iterations; i++) {
    bp.infer(dem, edgeSet, coeffsMatrix, variancesVector, weightsVector);
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
