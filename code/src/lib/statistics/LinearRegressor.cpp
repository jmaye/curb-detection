#include "LinearRegressor.h"

#include "Cell.h"

#include <Eigen/Core>
#include <Eigen/LU>

#include <iostream>
#include <fstream>

#include <stdint.h>
#include <math.h>

using namespace Eigen;
using namespace std;

void LinearRegressor::estimate(const DEM& dem,
  vector<vector<double> >& coeffsMatrix, vector<double>& variancesVector) {
  const vector<Cell>& cellsVector = dem.getCellsVector();
  uint32_t u32ValidCellsNbr = dem.getValidCellsNbr();
  uint32_t u32LabelsNbr = dem.getLabelsNbr();
  VectorXd targetsVector(u32ValidCellsNbr);
  MatrixXd designMatrix(u32ValidCellsNbr, 3);
  MatrixXd weightsMatrix(u32LabelsNbr, (int)u32ValidCellsNbr);
  uint32_t i = 0;
  for (uint32_t j = 0; j < cellsVector.size(); j++) {
    if (cellsVector[j].getInvalidFlag() == false) {
      targetsVector(i) = cellsVector[j].getHeightDist().getMean();
      const Point2D& cellCenter = cellsVector[j].getCellCenter();
      designMatrix(i, 0) = 1;
      designMatrix(i, 1) = cellCenter.mf64X;
      designMatrix(i, 2) = cellCenter.mf64Y;
      const vector<double>& labelsDistVector =
        cellsVector[j].getLabelsDistVector();
      for (uint32_t k = 0; k < labelsDistVector.size(); k++) {
        weightsMatrix(k, i) = labelsDistVector[k];
      }
      i++;
    }
  }
  coeffsMatrix.clear();
  coeffsMatrix.resize(u32LabelsNbr);
  variancesVector.clear();
  variancesVector.resize(u32LabelsNbr);
  Map<VectorXd> variancesVectorMapped(&variancesVector[0], u32LabelsNbr);
  MatrixXd coeffsMatrixEigen(u32LabelsNbr, 3);
  for (uint32_t i = 0; i < u32LabelsNbr; i++) {
    coeffsMatrixEigen.row(i) = ((designMatrix.transpose() *
      weightsMatrix.row(i).asDiagonal() * designMatrix).inverse() *
      designMatrix.transpose() * weightsMatrix.row(i).asDiagonal() *
      targetsVector).transpose();
    variancesVectorMapped(i) = 0;
    for (uint32_t j = 0; j < u32ValidCellsNbr; j++)
      for (uint32_t k = 0; k < u32LabelsNbr; k++)
       variancesVectorMapped(i) += weightsMatrix(k, j) * pow(targetsVector(j) -
        coeffsMatrixEigen.row(i).transpose().dot(designMatrix.row(i)), 2);
    variancesVectorMapped(i) /= u32ValidCellsNbr;
    coeffsMatrix[i].resize(3);
    coeffsMatrix[i][0] = coeffsMatrixEigen(i, 0);
    coeffsMatrix[i][1] = coeffsMatrixEigen(i, 1);
    coeffsMatrix[i][2] = coeffsMatrixEigen(i, 2);
  }
}
