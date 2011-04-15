#ifndef BELIEFPROPAGATION_H
#define BELIEFPROPAGATION_H

#include "DEM.h"
#include "Edge.h"
#include "OutOfBoundException.h"

#include <dai/bp.h>
#include <dai/factorgraph.h>

#include <set>
#include <vector>
#include <map>
#include <iosfwd>

#include <stdint.h>

class BeliefPropagation {
  friend std::ostream& operator << (std::ostream& stream,
    const BeliefPropagation& obj);
  friend std::istream& operator >> (std::istream& stream,
    BeliefPropagation& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const BeliefPropagation& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    BeliefPropagation& obj);

  BeliefPropagation(const BeliefPropagation& other);
  BeliefPropagation& operator = (const BeliefPropagation& other);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  std::map<std::pair<uint32_t, uint32_t>, uint32_t> mIdMap;
  dai::FactorGraph mFactorGraph;
  dai::BP mBP;
  bool mbInferenceDone;

public:
  BeliefPropagation(const DEM& dem,
    const std::multiset<Edge, EdgeCompare>& edgeSet);
  ~BeliefPropagation();

  void infer(const DEM& dem,
    const std::vector<std::vector<double> >& coeffsMatrix,
    const std::vector<double>& variancesVector,
    const std::vector<double>& weightsVector) throw (OutOfBoundException);

  std::vector<double>
    getNodeDistribution(std::pair<uint32_t, uint32_t> nodeCoordinates) const
    throw (OutOfBoundException);

protected:

};

#endif // BELIEFPROPAGATION_H
