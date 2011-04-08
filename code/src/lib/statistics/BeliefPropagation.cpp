#include "BeliefPropagation.h"

#include "UniGaussian.h"

#include <Eigen/Core>

#include <iostream>

#include <stdint.h>
#include <math.h>

using namespace Eigen;
using namespace std;

BeliefPropagation::BeliefPropagation(const DEM& dem) {
  mNodesEvidenceMatrix.resize(dem.getCellsNbrX());
  mNodesUpMatrix.resize(dem.getCellsNbrX());
  mNodesDownMatrix.resize(dem.getCellsNbrX());
  mNodesLeftMatrix.resize(dem.getCellsNbrX());
  mNodesRightMatrix.resize(dem.getCellsNbrX());
  mDataMatrix.resize(dem.getCellsNbrX());
  mDistanceMatrix.resize(dem.getCellsNbrX());
  for (uint32_t i = 0; i < dem.getCellsNbrX(); i++) {
    mNodesEvidenceMatrix[i].resize(dem.getCellsNbrX());
    mNodesUpMatrix[i].resize(dem.getCellsNbrY());
    mNodesDownMatrix[i].resize(dem.getCellsNbrY());
    mNodesLeftMatrix[i].resize(dem.getCellsNbrY());
    mNodesRightMatrix[i].resize(dem.getCellsNbrY());
    mDataMatrix[i].resize(dem.getCellsNbrY());
    mDistanceMatrix[i].resize(dem.getCellsNbrY());
    for (uint32_t j = 0; j < dem.getCellsNbrY(); j++) {
      mNodesUpMatrix[i][j].resize(dem.getLabelsNbr());
      mNodesDownMatrix[i][j].resize(dem.getLabelsNbr());
      mNodesLeftMatrix[i][j].resize(dem.getLabelsNbr());
      mNodesRightMatrix[i][j].resize(dem.getLabelsNbr());
      for (uint32_t k = 0; k < dem.getLabelsNbr(); k++) {
        mNodesUpMatrix[i][j][k] = 0;
        mNodesDownMatrix[i][j][k] = 0;
        mNodesLeftMatrix[i][j][k] = 0;
        mNodesRightMatrix[i][j][k] = 0;
      }
      if (dem(i, j).getInvalidFlag() == false) {
        mNodesEvidenceMatrix[i][j].resize(dem.getLabelsNbr());
        mDataMatrix[i][j].resize(5);
        mDataMatrix[i][j][0] = 1;
        mDataMatrix[i][j][1] = dem(i, j).getCellCenter().mf64X;
        mDataMatrix[i][j][2] = dem(i, j).getCellCenter().mf64Y;
        mDataMatrix[i][j][3] = dem(i, j).getHeightDist().getMean();
        mDataMatrix[i][j][4] = dem(i, j).getHeightDist().getVariance();
        mDistanceMatrix[i][j].resize(4);
        if (i != dem.getCellsNbrX() - 1) {
          mDistanceMatrix[i][j][0] = (1 / (1 + exp(dem(i, j).getHeightDist().
            getVariance() + dem(i+1, j).getHeightDist().getVariance() -
            fabs(dem(i, j).getHeightDist().getMean() - dem(i+1, j).
            getHeightDist().getMean()))));
        }
        if (i != 0) {
          mDistanceMatrix[i][j][1] = (1 / (1 + exp(dem(i, j).getHeightDist().
            getVariance() + dem(i-1, j).getHeightDist().getVariance() -
            fabs(dem(i, j).getHeightDist().getMean() - dem(i-1, j).
            getHeightDist().getMean()))));
        }
        if (j != dem.getCellsNbrY() - 1) {
          mDistanceMatrix[i][j][2] = (1 / (1 + exp(dem(i, j).getHeightDist().
            getVariance() + dem(i, j+1).getHeightDist().getVariance() -
            fabs(dem(i, j).getHeightDist().getMean() - dem(i, j+1).
            getHeightDist().getMean()))));
        }
        if (j != 0) {
          mDistanceMatrix[i][j][3] = (1 / (1 + exp(dem(i, j).getHeightDist().
            getVariance() + dem(i, j-1).getHeightDist().getVariance() -
            fabs(dem(i, j).getHeightDist().getMean() - dem(i, j-1).
            getHeightDist().getMean()))));
        }
      }
    }
  }
}

void BeliefPropagation::infer(const vector<vector<double> >& coeffsMatrix,
  const vector<double>& variancesVector,
  const vector<double>& weightsVector) {
  for (uint32_t i = 0; i < mDataMatrix.size(); i++) {
    for (uint32_t j = 0; j < mDataMatrix[0].size(); j++) {
      if (mDataMatrix[i][j].size() != 0) {
        VectorXd dataVector(3);
        dataVector(0) = mDataMatrix[i][j][0];
        dataVector(1) = mDataMatrix[i][j][1];
        dataVector(2) = mDataMatrix[i][j][2];
        for (uint32_t k = 0; k < mNodesEvidenceMatrix[i][j].size(); k++) {
          const vector<double>& coeffVector = coeffsMatrix[k];
          Map<VectorXd> coeffVectorMapped(&coeffVector[0], coeffVector.size());
          mNodesEvidenceMatrix[i][j][k] = 1 / (UniGaussian(coeffVectorMapped.
            dot(dataVector), mDataMatrix[i][j][4]+ variancesVector[k]).
            pdf(mDataMatrix[i][j][3]));
        }
      }
    }
  }
  for (uint32_t it = 0; it < 5; it++) {
    for (uint32_t i = 0; i < mDataMatrix.size(); i++) {
      for (uint32_t j = 0; j < mDataMatrix[0].size(); j++) {
        vector<double> emptyVector;
        if (mDataMatrix[i][j].size() != 0) {
          if (i > 0 && i < mDataMatrix.size() - 1 &&
            j > 0 && j < mDataMatrix[0].size() - 1) {
            computeMsg(mNodesUpMatrix[i+1][j], mNodesLeftMatrix[i][j+1],
              mNodesRightMatrix[i][j-1], mNodesEvidenceMatrix[i][j],
              mNodesUpMatrix[i][j], mDistanceMatrix[i][j][0]);
            computeMsg(mNodesDownMatrix[i-1][j], mNodesLeftMatrix[i][j+1],
              mNodesRightMatrix[i][j-1], mNodesEvidenceMatrix[i][j],
              mNodesDownMatrix[i][j], mDistanceMatrix[i][j][1]);
            computeMsg(mNodesUpMatrix[i+1][j], mNodesDownMatrix[i-1][j],
              mNodesRightMatrix[i][j-1], mNodesEvidenceMatrix[i][j],
              mNodesRightMatrix[i][j], mDistanceMatrix[i][j][2]);
            computeMsg(mNodesUpMatrix[i+1][j], mNodesDownMatrix[i-1][j],
              mNodesLeftMatrix[i][j+1], mNodesEvidenceMatrix[i][j],
              mNodesLeftMatrix[i][j], mDistanceMatrix[i][j][3]);
          }
          else if (i == 0 && j > 0 && j < mDataMatrix[0].size() - 1) {
            computeMsg(emptyVector, mNodesLeftMatrix[i][j+1],
              mNodesRightMatrix[i][j-1], mNodesEvidenceMatrix[i][j],
              mNodesDownMatrix[i][j], mDistanceMatrix[i][j][1]);
            computeMsg(mNodesUpMatrix[i+1][j], emptyVector,
              mNodesRightMatrix[i][j-1], mNodesEvidenceMatrix[i][j],
              mNodesRightMatrix[i][j], mDistanceMatrix[i][j][2]);
            computeMsg(mNodesUpMatrix[i+1][j], emptyVector,
              mNodesLeftMatrix[i][j+1], mNodesEvidenceMatrix[i][j],
              mNodesLeftMatrix[i][j], mDistanceMatrix[i][j][3]);
          }
          else if (i == mDataMatrix.size() - 1 && j > 0 &&
            j < mDataMatrix[0].size() - 1) {
            computeMsg(emptyVector, mNodesLeftMatrix[i][j+1],
              mNodesRightMatrix[i][j-1], mNodesEvidenceMatrix[i][j],
              mNodesUpMatrix[i][j], mDistanceMatrix[i][j][0]);
            computeMsg(emptyVector, mNodesDownMatrix[i-1][j],
              mNodesRightMatrix[i][j-1], mNodesEvidenceMatrix[i][j],
              mNodesRightMatrix[i][j], mDistanceMatrix[i][j][2]);
            computeMsg(emptyVector, mNodesDownMatrix[i-1][j],
              mNodesLeftMatrix[i][j+1], mNodesEvidenceMatrix[i][j],
              mNodesLeftMatrix[i][j], mDistanceMatrix[i][j][3]);
          }
          else if (j == 0 && i > 0 && i < mDataMatrix.size() - 1) {
            computeMsg(mNodesUpMatrix[i+1][j], mNodesLeftMatrix[i][j+1],
             emptyVector, mNodesEvidenceMatrix[i][j],
              mNodesUpMatrix[i][j], mDistanceMatrix[i][j][0]);
            computeMsg(mNodesDownMatrix[i-1][j], mNodesLeftMatrix[i][j+1],
              emptyVector, mNodesEvidenceMatrix[i][j],
              mNodesDownMatrix[i][j], mDistanceMatrix[i][j][1]);
            computeMsg(mNodesUpMatrix[i+1][j], mNodesDownMatrix[i-1][j],
              emptyVector, mNodesEvidenceMatrix[i][j],
              mNodesRightMatrix[i][j], mDistanceMatrix[i][j][2]);
          }
          else if (j == mDataMatrix[0].size() -1 && i > 0 &&
            i < mDataMatrix.size() - 1) {
            computeMsg(mNodesUpMatrix[i+1][j], emptyVector,
              mNodesRightMatrix[i][j-1], mNodesEvidenceMatrix[i][j],
              mNodesUpMatrix[i][j], mDistanceMatrix[i][j][0]);
            computeMsg(mNodesDownMatrix[i-1][j], emptyVector,
              mNodesRightMatrix[i][j-1], mNodesEvidenceMatrix[i][j],
              mNodesDownMatrix[i][j], mDistanceMatrix[i][j][1]);
            computeMsg(mNodesUpMatrix[i+1][j], mNodesDownMatrix[i-1][j],
              emptyVector, mNodesEvidenceMatrix[i][j],
              mNodesLeftMatrix[i][j], mDistanceMatrix[i][j][3]);
          }
          else if (i == 0 && j == 0) {
            computeMsg(emptyVector, mNodesLeftMatrix[i][j+1],
              emptyVector, mNodesEvidenceMatrix[i][j],
              mNodesDownMatrix[i][j], mDistanceMatrix[i][j][1]);
            computeMsg(mNodesUpMatrix[i+1][j], emptyVector,
              emptyVector, mNodesEvidenceMatrix[i][j],
              mNodesRightMatrix[i][j], mDistanceMatrix[i][j][2]);
          }
          else if (i == mDataMatrix.size() - 1 && j == 0) {
            computeMsg(emptyVector, mNodesLeftMatrix[i][j+1],
              emptyVector, mNodesEvidenceMatrix[i][j],
              mNodesUpMatrix[i][j], mDistanceMatrix[i][j][0]);
            computeMsg(emptyVector, mNodesDownMatrix[i-1][j],
              emptyVector, mNodesEvidenceMatrix[i][j],
              mNodesRightMatrix[i][j], mDistanceMatrix[i][j][2]);
          }
          else if (i == 0 && j == mDataMatrix[0].size() - 1) {
            computeMsg(emptyVector, emptyVector,
              mNodesRightMatrix[i][j-1], mNodesEvidenceMatrix[i][j],
              mNodesDownMatrix[i][j], mDistanceMatrix[i][j][1]);
            computeMsg(mNodesUpMatrix[i+1][j], emptyVector,
              emptyVector, mNodesEvidenceMatrix[i][j],
              mNodesLeftMatrix[i][j], mDistanceMatrix[i][j][3]);
          }
          else if (i == mDataMatrix.size() - 1 &&
            j  == mDataMatrix[0].size() - 1) {
            computeMsg(emptyVector, emptyVector,
              mNodesRightMatrix[i][j-1], mNodesEvidenceMatrix[i][j],
              mNodesUpMatrix[i][j], mDistanceMatrix[i][j][0]);
            computeMsg(emptyVector, mNodesDownMatrix[i-1][j],
              emptyVector, mNodesEvidenceMatrix[i][j],
              mNodesLeftMatrix[i][j], mDistanceMatrix[i][j][3]);
          }
        }
      }
    }
  }
  for (uint32_t i = 1; i < mNodesEvidenceMatrix.size() - 1; i++) {
    for (uint32_t j = 1; j < mNodesEvidenceMatrix[0].size() - 1; j++) {
      if (mNodesEvidenceMatrix[i][j].size() != 0) {
        uint32_t u32BestIdx = 0;
        double f64BestVal = INFINITY;
        for (uint32_t k = 0; k < mNodesEvidenceMatrix[i][j].size(); k++) {
          double f64Val =
            mNodesUpMatrix[i+1][j][k] + mNodesDownMatrix[i-1][j][k] +
            mNodesLeftMatrix[i][j+1][k] + mNodesRightMatrix[i][j-1][k];
          if (f64Val < f64BestVal) {
            f64BestVal = f64Val;
            u32BestIdx = k;
          }
        }
        cout << u32BestIdx << " ";
      }
      else
        cout << "  ";
    }
    cout << endl;
  }
}

void BeliefPropagation::computeMsg(const vector<double>& node1Vector,
  const vector<double>& node2Vector, const vector<double>& node3Vector,
  const vector<double>& nodeEvidenceVector, vector<double>& msgVector,
  double f64Distance) {
  double f64Minimum = INFINITY;
  for (uint32_t i = 0; i < nodeEvidenceVector.size(); i++) {
    msgVector[i] = nodeEvidenceVector[i];
    if (node1Vector.size() != 0)
      msgVector[i] += node1Vector[i];
    if (node2Vector.size() != 0)
      msgVector[i] += node2Vector[i];
    if (node3Vector.size() != 0)
      msgVector[i] += node3Vector[i];
    if (msgVector[i] < f64Minimum)
      f64Minimum = msgVector[i];
  }
  for (uint32_t i = 0; i < nodeEvidenceVector.size(); i++) {
    msgVector[i] = fmin(f64Distance + msgVector[i],
      1 - f64Distance + f64Minimum);
  }
  double f64Sum = 0;
  for (uint32_t i = 0; i < nodeEvidenceVector.size(); i++)
    f64Sum += msgVector[i];
  f64Sum /= nodeEvidenceVector.size();
  for (uint32_t i = 0; i < nodeEvidenceVector.size(); i++)
    msgVector[i] -= f64Sum;
}
