#ifndef LINEARREGRESSOR_H
#define LINEARREGRESSOR_H

#include "DEM.h"
#include "OutOfBoundException.h"

#include <iosfwd>
#include <vector>

class LinearRegressor {
  LinearRegressor();

public:
  static void estimate(const DEM& dem,
    std::vector<std::vector<double> >& coeffsMatrix,
    std::vector<double>& variancesVector, std::vector<double>& weightsVector,
    double f64Tol = 1e-6)
    throw (OutOfBoundException);

protected:

};

#endif // LINEARREGRESSOR_H
