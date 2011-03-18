#ifndef MLESTIMATOR_H
#define MLESTIMATOR_H

#include "Estimator.h"
#include "UniGaussian.h"

#include <iosfwd>

#include <stdint.h>

class MLEstimator : public Estimator {
  friend std::ostream& operator << (std::ostream& stream,
    const MLEstimator& obj);
  friend std::istream& operator >> (std::istream& stream,
    MLEstimator& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const MLEstimator& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    MLEstimator& obj);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  uint32_t mu32PointsNbr;

public:
  MLEstimator();
  MLEstimator(const MLEstimator& other);
  MLEstimator& operator = (const MLEstimator& other);
  ~MLEstimator();

  void addDataPoint(UniGaussian& dist, double f64DataPoint);

  uint32_t getPointsNbr() const;
  void setPointsNbr(uint32_t u32PointsNbr);

protected:

};

#endif // MLESTIMATOR_H
