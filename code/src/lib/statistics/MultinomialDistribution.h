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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file MultinomialDistribution.h
    \brief This file defines the MultinomialDistribution class, which represents
           a multinomial distribution
  */

#ifndef MULTINOMIALDISTRIBUTION_H
#define MULTINOMIALDISTRIBUTION_H

#include "statistics/DiscreteDistribution.h"
#include "statistics/SampleDistribution.h"
#include "base/Serializable.h"

/** The MultinomialDistribution class represents a multinomial distribution,
    i.e., the discrete distribution of N independent categorical distribution
    draws.
    \brief Multinomial distribution
  */
template <size_t M> class MultinomialDistribution :
  public DiscreteDistribution<int, M>,
  public DiscreteDistribution<int, M - 1>,
  public SampleDistribution<Eigen::Matrix<int, M, 1> >,
  public virtual Serializable {
public:
  /** \name Types
    @{
    */
  /// Distribution type
  typedef DiscreteDistribution<int, M> DistributionType;
  /// Random variable type
  typedef typename DistributionType::RandomVariable RandomVariable;
  /// Mean type
  typedef typename DistributionType::Mean Mean;
  /// Mode type
  typedef typename DistributionType::Mode Mode;
  /// Covariance type
  typedef typename DistributionType::Covariance Covariance;
  /** @}
    */

  /** \name Traits
    @{
    */
  /// Support for the N - 1 simplex
  template <size_t N, size_t D = 0> struct Traits {
  public:
    /// Returns the probability mass function at a point
    static double pmf(const MultinomialDistribution<N>& distribution,
      const Eigen::Matrix<int, N - 1, 1>& value);
    /// Returns the log-probability mass function at a point
    static double logpmf(const MultinomialDistribution<N>& distribution,
      const Eigen::Matrix<int, N - 1, 1>& value);
  };
  /// Support for N = 2
  template <size_t D> struct Traits<2, D> {
  public:
    /// Returns the probability mass function at a point
    static double pmf(const MultinomialDistribution<2>& distribution,
      const int& value);
    /// Returns the log-probability mass function at a point
    static double logpmf(const MultinomialDistribution<2>& distribution,
      const int& value);
  };
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs the distribution from the parameters
  MultinomialDistribution(size_t numTrials = 1, const
    Eigen::Matrix<double, M, 1>& probabilities =
    Eigen::Matrix<double, M, 1>::Constant(1.0 / M));
  /// Copy constructor
  MultinomialDistribution(const MultinomialDistribution& other);
  /// Assignment operator
  MultinomialDistribution& operator = (const MultinomialDistribution& other);
  /// Destructor
  virtual ~MultinomialDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the success probabilities
  void setProbabilities(const Eigen::Matrix<double, M, 1>& probabilities);
  /// Returns the success probabilities
  const Eigen::Matrix<double, M, 1>& getProbabilities() const;
  /// Returns a success probability by index
  double getProbability(size_t idx) const;
  /// Sets the number of trials
  virtual void setNumTrials(size_t numTrials);
  /// Returns the number of trials
  size_t getNumTrials() const;
  /// Returns the mean of the distribution
  Mean getMean() const;
  /// Returns the mode of the distribution
  Mode getMode() const;
  /// Returns the covariance of the distribution
  Covariance getCovariance() const;
  /// Returns the probability mass function at a point
  virtual double pmf(const RandomVariable& value) const;
  /// Returns the probability mass function at a point
  virtual double pmf(const typename
    DiscreteDistribution<int, M - 1>::Domain& value) const;
  /// Returns the log-probability mass function at a point
  double logpmf(const RandomVariable& value) const;
  /// Returns the log-probability mass function at a point
  double logpmf(const typename DiscreteDistribution<int, M - 1>::Domain&
    value) const;
  /// Access a sample drawn from the distribution
  virtual RandomVariable getSample() const;
  /** @}
    */

  using DiscreteDistribution<int, M>::operator();
  using DiscreteDistribution<int, M - 1>::operator();

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
  /// Success probabilities
  Eigen::Matrix<double, M, 1> mProbabilities;
  /// Number of trials
  size_t mNumTrials;
  /** @}
    */

};

#include "statistics/MultinomialDistribution.tpp"

#endif // MULTINOMIALDISTRIBUTION_H
