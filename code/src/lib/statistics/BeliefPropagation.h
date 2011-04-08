#ifndef BELIEFPROPAGATION_H
#define BELIEFPROPAGATION_H

#include "DEM.h"

#include <vector>

class BeliefPropagation {

  std::vector<std::vector<std::vector<double> > > mNodesEvidenceMatrix;
  std::vector<std::vector<std::vector<double> > > mNodesUpMatrix;
  std::vector<std::vector<std::vector<double> > > mNodesDownMatrix;
  std::vector<std::vector<std::vector<double> > > mNodesLeftMatrix;
  std::vector<std::vector<std::vector<double> > > mNodesRightMatrix;
  std::vector<std::vector<std::vector<double> > > mDataMatrix;
  std::vector<std::vector<std::vector<double> > > mDistanceMatrix;

  void computeMsg(const std::vector<double>& node1Vector,
    const std::vector<double>& node2Vector,
    const std::vector<double>& node3Vector,
    const std::vector<double>& nodeEvidenceVector,
    std::vector<double>& msgVector,
    double f64Distance);

public:
  BeliefPropagation(const DEM& dem);

  void infer(const std::vector<std::vector<double> >& coeffsMatrix,
    const std::vector<double>& variancesVector,
    const std::vector<double>& weightsVector);

protected:

};

#endif // BELIEFPROPAGATION_H
