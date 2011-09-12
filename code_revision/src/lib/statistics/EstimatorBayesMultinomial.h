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

#include "statistics/MultinomialDistribution.h"
#include "statistics/DirichletDistribution.h"
#include "statistics/DCMDistribution.h"

#include <vector>

/** The class EstimatorBayes is implemented for multinomial
    distributions with conjugate prior.
    \brief Multinomial distribution Bayesian estimator
  */
template <size_t M> class EstimatorBayes<MultinomialDistribution<M>, M> :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /// Point type
  typedef Eigen::Matrix<size_t, M, 1> Point;
  /// Points container
  typedef std::vector<Point> Container;
  /// Constant point iterator
  typedef typename Container::const_iterator ConstPointIterator;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs estimator with hyperparameters prior
  EstimatorBayes(size_t numTrials = 1, const Eigen::Matrix<double, M, 1>&
    alpha = Eigen::Matrix<double, M, 1>::Ones());
  /// Copy constructor
  EstimatorBayes(const EstimatorBayes<MultinomialDistribution<M>, M>& other);
  /// Assignment operator
  EstimatorBayes<MultinomialDistribution<M>, M>& operator =
    (const EstimatorBayes<MultinomialDistribution<M>, M>& other);
  /// Destructor
  virtual ~EstimatorBayes();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the number of trials
  size_t getNumTrials() const;
  /// Returns the posterior success probablities distribution
  const DirichletDistribution<M>& getPostSuccessDist() const;
  /// Returns the posterior predictive distribution
  const DCMDistribution<M>& getPostPredDist() const;
  /// Returns the validity state of the estimator
  bool getValid() const;
  /// Add a point to the estimator
  void addPoint(const Point& point);
  /// Add points to the estimator
  void addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd);
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
  /// Number of trials
  size_t mNumTrials;
  /// Posterior success probablities distribution
  DirichletDistribution<M> mPostSuccessDist;
  /// Posterior predictive distribution
  DCMDistribution<M> mPostPredDist;
  /// Hyperparameter alpha (alpha_i - 1 pseudo-counts for i, alpha.sum = conf.)
  Eigen::Matrix<double, M, 1> mAlpha;
  /** @}
    */

};

#include "statistics/EstimatorBayesMultinomial.tpp"
