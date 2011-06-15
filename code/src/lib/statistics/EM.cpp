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

#include "statistics/EM.h"

#include "statistics/LinearRegressor.h"
#include "statistics/BeliefPropagation.h"

#include <iostream>
#include <limits>

void EM::run(DEM& dem,
  const std::multiset<Edge, EdgeCompare>& edgeSet,
  std::vector<std::vector<double> >& coeffsMatrix,
  std::vector<double>& variancesVector, std::vector<double>& weightsVector,
  uint32_t u32MaxEMIterations, double f64EMTol, uint32_t u32MaxBPIterations,
  double f64BPTol) {
  double f64OldLogPartitionSum = -std::numeric_limits<double>::max();
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
