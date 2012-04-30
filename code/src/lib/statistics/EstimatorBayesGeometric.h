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

/** \file EstimatorBayesGeometric.h
    \brief This file implements a Bayesian estimator for geometric distributions
           with conjugate prior
  */

#include <vector>

#include "statistics/GeometricDistribution.h"
#include "statistics/BetaDistribution.h"

/** The class EstimatorBayes is implemented for geometric distributions with
    conjugate prior.
    \brief Geometric distribution Bayesian estimator
  */
template <> class EstimatorBayes<GeometricDistribution, BetaDistribution> :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /// Point type
  typedef GeometricDistribution::RandomVariable Point;
  /// Points container
  typedef std::vector<Point> Container;
  /// Constant point iterator
  typedef Container::const_iterator ConstPointIterator;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs estimator with prior
  EstimatorBayes(const BetaDistribution& prior = BetaDistribution());
  /// Copy constructor
  EstimatorBayes(const EstimatorBayes& other);
  /// Assignment operator
  EstimatorBayes& operator = (const EstimatorBayes& other);
  /// Destructor
  virtual ~EstimatorBayes();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the probabiliy distribution
  const BetaDistribution& getDist() const;
  /// Add a point to the estimator
  void addPoint(const Point& point);
  /// Add points to the estimator
  void addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd);
  /// Add points to the estimator
  void addPoints(const Container& points);
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream);
  /// Writes to standard output
  virtual void write(std::ostream& stream) const;
  /// Reads from a file
  virtual void read(std::ifstream& stream);
  /// Writes to a file
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Protected members
    @{
    */
  /*! \brief Probability distribution
  *
  * Hyperparameter alpha (prior success) and
  * hyperparameter beta (prior failure)
  */
  BetaDistribution mProbDist;
  /** @}
    */

};

#include "statistics/EstimatorBayesGeometric.tpp"
