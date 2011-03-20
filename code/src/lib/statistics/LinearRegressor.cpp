#include "LinearRegressor.h"

#include <Eigen/Core>
#include <Eigen/LU>

#include <iostream>
#include <fstream>

#include <stdint.h>
#include <math.h>

using namespace Eigen;
using namespace std;

void LinearRegressor::estimate(const vector<vector<double> >& inputsMatrix,
  const vector<double>& targetsVector, vector<double>& weightsVector,
  double& f64Variance) {
  Map<MatrixXd> designMatrixMapped(&inputsMatrix[0][0], inputsMatrix.size(), inputsMatrix[0].size());
  Map<VectorXd> targetsVectorMapped(&targetsVector[0], targetsVector.size());
  Map<VectorXd> weightsVectorMapped(&weightsVector[0], weightsVector.size());

  weightsVectorMapped = (designMatrixMapped.transpose() *
    designMatrixMapped).inverse() *
    designMatrixMapped.transpose() * targetsVectorMapped;

  f64Variance = 0;
  for (uint32_t i = 0; i < inputsMatrix.size(); i++)
    f64Variance += pow(targetsVectorMapped(i) -
      weightsVectorMapped.dot(designMatrixMapped.row(i)), 2);
  f64Variance /= inputsMatrix.size();
}
