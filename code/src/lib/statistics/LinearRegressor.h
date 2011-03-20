#ifndef LINEARREGRESSOR_H
#define LINEARREGRESSOR_H

#include <iosfwd>
#include <vector>

class LinearRegressor {
  LinearRegressor();

public:
  static void estimate(const std::vector<std::vector<double> >& inputsMatrix,
    const std::vector<double>& targetsVector,
    std::vector<double>& weightsVector, double& f64Variance);

protected:

};

#endif // LINEARREGRESSOR_H
