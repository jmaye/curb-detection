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
  vector<vector<double> >& coeffsMatrix, vector<double>& variancesVector,
  vector<double>& weightsVector) {
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
      for (uint32_t k = 0; k < u32LabelsNbr; k++) {
        weightsMatrix(k, i) = labelsDistVector[k];
      }
      i++;
    }
  }
  coeffsMatrix.clear();
  coeffsMatrix.resize(u32LabelsNbr);
  variancesVector.clear();
  variancesVector.resize(u32LabelsNbr);
  weightsVector.clear();
  weightsVector.resize(u32LabelsNbr);
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
    weightsVector[i] = weightsMatrix.row(i).sum() / u32ValidCellsNbr;
  }
//  cout << endl << coeffsMatrixEigen << endl << endl;
//  cout << variancesVectorMapped << endl << endl;
//  for (uint32_t i = 0; i < u32LabelsNbr; i++) {
//    cout << weightsVector[i] << endl;
//  }
//  cout << endl;
}

void LinearRegressor::test(DEM& dem,
  const vector<vector<double> >& coeffsMatrix,
  const vector<double>& variancesVector, const vector<double>& weightsVector) {
  const vector<Cell>& cellsVector = dem.getCellsVector();
  for (uint32_t i = 0; i < cellsVector.size(); i++) {
    if (cellsVector[i].getInvalidFlag() == false) {
      vector<double> distVector(dem.getLabelsNbr());
      for (uint32_t j = 0; j < dem.getLabelsNbr(); j++) {
        const vector<double>& coeffVector = coeffsMatrix[j];
        Map<VectorXd> coeffVectorMapped(&coeffVector[0], coeffVector.size());
        VectorXd dataVector(coeffVector.size());
        dataVector(0) = 1;
        dataVector(1) = cellsVector[i].getCellCenter().mf64X;
        dataVector(2) = cellsVector[i].getCellCenter().mf64Y;
        distVector[j] = weightsVector[j] *
          UniGaussian(cellsVector[i].getHeightDist().getMean(),
          cellsVector[i].getHeightDist().getVariance()).pdf(coeffVectorMapped.dot(dataVector));
//          UniGaussian(coeffVectorMapped.dot(dataVector),
//          cellsVector[i].getHeightDist().getVariance() +
//          variancesVector[j]).pdf(cellsVector[i].getHeightDist().getMean());
      }
      dem.test(i, distVector);
    }
  }
}
