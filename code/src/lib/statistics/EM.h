#ifndef EM_H
#define EM_H

#include "DEM.h"
#include "BeliefPropagation.h"
#include "Edge.h"

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
