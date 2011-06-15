/******************************************************************************
 * Copyright (C) 2011 by Jerome Maye                                          *
 * jerome.maye@gmail.com                                                      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

#ifndef BELIEFPROPAGATION_H
#define BELIEFPROPAGATION_H

#include "data-structures/DEM.h"
#include "data-structures/Edge.h"
#include "exceptions/OutOfBoundException.h"
#include "exceptions/InvalidOperationException.h"

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
  bool mbMaxProductDone;
  std::vector<size_t> mMAPStateVector;

public:
  BeliefPropagation();
  ~BeliefPropagation();

  void infer(const DEM& dem,
    const std::multiset<Edge, EdgeCompare>& edgeSet,
    const std::vector<std::vector<double> >& coeffsMatrix,
    const std::vector<double>& variancesVector,
    const std::vector<double>& weightsVector,
    uint32_t u32MaxIter = 10000, double f64Tol = 1e-9, bool bMaxProd = false)
    throw (OutOfBoundException);

  std::vector<double>
    getNodeDistribution(const std::pair<uint32_t, uint32_t>& nodeCoordinates)
    const throw (OutOfBoundException, InvalidOperationException);

  uint32_t getMAPState(const std::pair<uint32_t, uint32_t>& nodeCoordinates)
    const throw (OutOfBoundException, InvalidOperationException);

  double getLogPartitionSum() const throw (InvalidOperationException);

protected:

};

#endif // BELIEFPROPAGATION_H
