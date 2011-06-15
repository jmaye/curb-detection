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

#ifndef EM_H
#define EM_H

#include "data-structures/DEM.h"
#include "statistics/BeliefPropagation.h"
#include "data-structures/Edge.h"

#include <vector>
#include <set>

#include <stdint.h>

class EM {
  EM();

public:
  static void run(DEM& dem,
    const std::multiset<Edge, EdgeCompare>& edgeSet,
    std::vector<std::vector<double> >& coeffsMatrix,
    std::vector<double>& varianceVector, std::vector<double>& weightsVector,
    uint32_t u32MaxEMIterations = 15, double f64EMTol = 1e-6,
    uint32_t u32MaxBPIterations = 10000, double f64BPTol = 1e-9);

protected:

};

#endif // EM_H
