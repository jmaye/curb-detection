/******************************************************************************
 * Copyright (C) 2011 by Jerome Maye                                          *
 * jerome.maye@gmail.com                                                      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

#include "statistics/LinearRegressor.h"

#include "data-structures/Cell.h"

#include <Eigen/Core>
#include <Eigen/LU>

#include <iostream>
#include <fstream>

#include <stdint.h>
#include <math.h>

void LinearRegressor::estimate(const DEM& dem,
  std::vector<std::vector<double> >& coeffsMatrix,
  std::vector<double>& variancesVector,
  std::vector<double>& weightsVector, double f64Tol)
  throw (OutOfBoundException) {
  uint32_t u32ValidCellsNbr = dem.getValidCellsNbr();
  uint32_t u32LabelsNbr = dem.getLabelsNbr();
  if (u32ValidCellsNbr == 0 || u32LabelsNbr == 0) {
    std::cerr << "u32ValidCellsNbr: " << u32ValidCellsNbr << std::endl;
    std::cerr << "u32LabelsNbr: " << u32LabelsNbr << std::endl;
    throw OutOfBoundException("LinearRegressor::estimate(): valid cells and labels number must be greater than 0");
  }
  Eigen::VectorXd targetsVector(u32ValidCellsNbr);
  Eigen::MatrixXd designMatrix(u32ValidCellsNbr, 3);
  Eigen::MatrixXd weightsMatrix(u32LabelsNbr, (int)u32ValidCellsNbr);
  uint32_t i = 0;
  for (uint32_t j = 0; j < dem.getCellsNbrX(); j++) {
    for (uint32_t k = 0; k < dem.getCellsNbrY(); k++) {
      const Cell& cell = dem(j, k);
      if (cell.getInvalidFlag() == false) {
        targetsVector(i) = cell.getHeightDist().getMean();
        const Point2D& cellCenter = cell.getCellCenter();
        designMatrix(i, 0) = 1.0;
        designMatrix(i, 1) = cellCenter.mf64X;
        designMatrix(i, 2) = cellCenter.mf64Y;
        const std::vector<double>& labelsDistVector = cell.getLabelsDistVector();
        for (uint32_t l = 0; l < u32LabelsNbr; l++) {
          weightsMatrix(l, i) = labelsDistVector[l];
        }
        i++;
      }
    }
  }
  coeffsMatrix.clear();
  coeffsMatrix.resize(u32LabelsNbr);
  variancesVector.clear();
  variancesVector.resize(u32LabelsNbr);
  weightsVector.clear();
  weightsVector.resize(u32LabelsNbr);
  Eigen::Map<Eigen::VectorXd> variancesVectorMapped(&variancesVector[0],
    u32LabelsNbr);
  Eigen::MatrixXd coeffsMatrixEigen(u32LabelsNbr, 3);
  for (uint32_t i = 0; i < u32LabelsNbr; i++) {
    Eigen::MatrixXd invCheckMatrix = designMatrix.transpose() *
      weightsMatrix.row(i).asDiagonal() * designMatrix;
    if (invCheckMatrix.determinant() > f64Tol) {
      coeffsMatrixEigen.row(i) = (invCheckMatrix.inverse() *
        designMatrix.transpose() * weightsMatrix.row(i).asDiagonal() *
        targetsVector).transpose();
      variancesVectorMapped(i) = 0;
      for (uint32_t j = 0; j < u32ValidCellsNbr; j++)
        variancesVectorMapped(i) += weightsMatrix(i, j) * pow(targetsVector(j) -
          coeffsMatrixEigen.row(i).transpose().dot(designMatrix.row(j)), 2);
      variancesVectorMapped(i) /= u32ValidCellsNbr;
      coeffsMatrix[i].resize(3);
      coeffsMatrix[i][0] = coeffsMatrixEigen(i, 0);
      coeffsMatrix[i][1] = coeffsMatrixEigen(i, 1);
      coeffsMatrix[i][2] = coeffsMatrixEigen(i, 2);
      weightsVector[i] = weightsMatrix.row(i).sum() / u32ValidCellsNbr;
    }
    else {
      variancesVector[i] = 0.0;
      weightsVector[i] = 0.0;
      coeffsMatrix[i].resize(3);
      coeffsMatrix[i][0] = 0.0;
      coeffsMatrix[i][1] = 0.0;
      coeffsMatrix[i][2] = 0.0;
    }
  }
}
