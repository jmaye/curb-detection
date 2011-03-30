#ifndef LINEARREGRESSOR_H
#define LINEARREGRESSOR_H

#include "DEM.h"

#include <iosfwd>
#include <vector>

class LinearRegressor {
  LinearRegressor();

public:
  static void estimate(const DEM& dem,
    std::vector<std::vector<double> >& weightsMatrix,
    std::vector<double>& varianceVector, std::vector<double>& weightsVector);
  static void test(DEM& dem,
    const std::vector<std::vector<double> >& coeffsMatrix,
    const std::vector<double>& variancesVector,
    const std::vector<double>& weightsVector);

protected:

};

#endif // LINEARREGRESSOR_H
