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

/** \file BeliefPropagation.h
    \brief This file defines the BeliefPropagation class, which implements the
           belief propagation algorithm
  */

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

/** The class BeliefPropagation implements the belief propagation algorithm
    \brief Belief propagation algorithm
  */
class BeliefPropagation {
  friend std::ostream& operator << (std::ostream& stream,
    const BeliefPropagation& obj);
  friend std::istream& operator >> (std::istream& stream,
    BeliefPropagation& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const BeliefPropagation& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    BeliefPropagation& obj);

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  BeliefPropagation(const BeliefPropagation& other);
  /// Assignment operator
  BeliefPropagation& operator = (const BeliefPropagation& other);
  /** @}
    */

  /** \name Streaming methods
    @{
    */
  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Private members
    @{
    */
  /// Mapping between DEM nodes and BP nodes
  std::map<std::pair<uint32_t, uint32_t>, uint32_t> mIdMap;
  /// Factor graph representation of the CRF
  dai::FactorGraph mFactorGraph;
  /// Inference engine
  dai::BP mBP;
  /// True when the inference has run
  bool mbInferenceDone;
  /// True whem the max-product algorithm has run
  bool mbMaxProductDone;
  /// MAP state after BP
  std::vector<size_t> mMAPStateVector;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  BeliefPropagation();
  /// Destructor
  ~BeliefPropagation();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Runs belief propagation
  void infer(const DEM& dem,
    const std::multiset<Edge, EdgeCompare>& edgeSet,
    const std::vector<std::vector<double> >& coeffsMatrix,
    const std::vector<double>& variancesVector,
    const std::vector<double>& weightsVector,
    uint32_t u32MaxIter = 10000, double f64Tol = 1e-9, bool bMaxProd = false)
    throw (OutOfBoundException);
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns node distribution (after sum-product run)
  std::vector<double>
    getNodeDistribution(const std::pair<uint32_t, uint32_t>& nodeCoordinates)
    const throw (OutOfBoundException, InvalidOperationException);
  /// Returns MAP state (after max-product run)
  uint32_t getMAPState(const std::pair<uint32_t, uint32_t>& nodeCoordinates)
    const throw (OutOfBoundException, InvalidOperationException);
  /// Returns log partition sum after BP run
  double getLogPartitionSum() const throw (InvalidOperationException);
  /** @}
    */

protected:

};

#endif // BELIEFPROPAGATION_H
