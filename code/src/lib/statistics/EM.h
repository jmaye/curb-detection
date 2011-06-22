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

/** \file EM.h
    \brief This file defines the EM class, which implements the
           expectation-maximization algorithm
  */

#ifndef EM_H
#define EM_H

#include "data-structures/DEM.h"
#include "statistics/BeliefPropagation.h"
#include "data-structures/Edge.h"

#include <vector>
#include <set>

#include <stdint.h>

/** The class EM implements the expectation-maximization algorithm
    \brief Expectation-Maximization algorithm
  */
class EM {
  /** \name Private constructor (not to be instantiated)
    @{
    */
  /// Default constructor
  EM();
  /** @}
    */

public:
  /** \name Methods
    @{
    */
  /// Runs the EM algorithm
  static void run(DEM& dem,
    const std::multiset<Edge, EdgeCompare>& edgeSet,
    std::vector<std::vector<double> >& coeffsMatrix,
    std::vector<double>& varianceVector, std::vector<double>& weightsVector,
    uint32_t u32MaxEMIterations = 15, double f64EMTol = 1e-6,
    uint32_t u32MaxBPIterations = 10000, double f64BPTol = 1e-9);
  /** @}
    */

protected:

};

#endif // EM_H
