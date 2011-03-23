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
    std::vector<double>& varianceVector);

protected:

};

#endif // LINEARREGRESSOR_H
