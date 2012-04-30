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

/** \file EstimatorBayesMultinomial.h
    \brief This file implements a Bayesian estimator for multinomial
           distributions with conjugate prior
  */

#include <vector>

#include "statistics/MultinomialDistribution.h"
#include "statistics/DirichletDistribution.h"
#include "statistics/DCMDistribution.h"

/** The class EstimatorBayes is implemented for multinomial
    distributions with conjugate prior.
    \brief Multinomial distribution Bayesian estimator
  */
template <size_t M>
class EstimatorBayes<MultinomialDistribution<M>, DirichletDistribution<M> > :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /// Point type
  typedef typename MultinomialDistribution<M>::RandomVariable Point;
  /// Points container
  typedef std::vector<Point> Container;
  /// Constant point iterator
  typedef typename Container::const_iterator ConstPointIterator;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs estimator with prior
  EstimatorBayes(const DirichletDistribution<M>& prior =
    DirichletDistribution<M>());
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
  /// Returns the probabilities distribution
  const DirichletDistribution<M>& getDist() const;
  /// Returns the predictive distribution
  DCMDistribution<M> getPredDist() const;
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
  /*! \brief Probabilities distribution
  *
  * Hyperparameter alpha (alpha_i - 1 pseudo-counts for i, alpha.sum = conf.)
  */
  DirichletDistribution<M> mProbDist;
  /// Number of trials
  size_t mNumTrials;
  /** @}
    */

};

#include "statistics/EstimatorBayesMultinomial.tpp"
