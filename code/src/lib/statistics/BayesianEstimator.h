#ifndef BAYESIANESTIMATOR_H
#define BAYESIANESTIMATOR_H

#include "UniGaussian.h"
#include "UniInverseGamma.h"

#include <iosfwd>

#include <stdint.h>

class BayesianEstimator {
  friend std::ostream& operator << (std::ostream& stream,
    const BayesianEstimator& obj);
  friend std::istream& operator >> (std::istream& stream,
    BayesianEstimator& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const BayesianEstimator& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    BayesianEstimator& obj);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  uint32_t mu32PointsNbr;

public:
  BayesianEstimator();
  BayesianEstimator(const BayesianEstimator& other);
  BayesianEstimator& operator = (const BayesianEstimator& other);
  ~BayesianEstimator();

  void addDataPoint(UniGaussian& dist, UniGaussian& meanPrior,
    UniInverseGamma& variancePrior, double f64DataPoint);

  uint32_t getPointsNbr() const;
  void setPointsNbr(uint32_t u32PointsNbr);

protected:

};

#endif // BAYESIANESTIMATOR_H
