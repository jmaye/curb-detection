#ifndef EM_H
#define EM_H

#include "DEM.h"
#include "DEMCRF.h"
#include "BeliefPropagation.h"

#include <vector>

#include <stdint.h>

class EM {
  EM();

public:
  static void run(DEMCRF& crf, Vector& nodesWeightsVector,
    Vector& edgesWeightsVector, DEM& dem,
    std::vector<std::vector<double> >& coeffsMatrix,
    std::vector<double>& varianceVector, std::vector<double>& weightsVector,
    uint32_t u32Iterations);

  static void run(BeliefPropagation& bp, DEM& dem,
    const std::multiset<Edge, EdgeCompare>& edgeSet,
    std::vector<std::vector<double> >& coeffsMatrix,
    std::vector<double>& varianceVector, std::vector<double>& weightsVector,
    uint32_t u32Iterations);

protected:

};

#endif // EM_H
