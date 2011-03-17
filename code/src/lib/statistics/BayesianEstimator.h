#ifndef BAYESIANESTIMATOR_H
#define BAYESIANESTIMATOR_H

#include "Estimator.h"

#include <iosfwd>

class BayesianEstimator : public Estimator {
  friend std::ostream& operator << (std::ostream& stream,
    const BayesianEstimator& obj);
  friend std::istream& operator >> (std::istream& stream,
    BayesianEstimator& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const BayesianEstimator& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    BayesianEstimator& obj);

  BayesianEstimator(const BayesianEstimator& other);
  BayesianEstimator& operator = (const BayesianEstimator& other);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

public:
  BayesianEstimator();
  ~BayesianEstimator();

protected:

};

#endif // BAYESIANESTIMATOR_H
