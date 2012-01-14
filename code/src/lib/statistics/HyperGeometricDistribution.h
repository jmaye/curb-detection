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

/** \file HyperGeometricDistribution.h
    \brief This file defines the HyperGeometricDistribution class, which
           represents an hypergeometric distribution
  */

#ifndef HYPERGEOMETRICDISTRIBUTION_H
#define HYPERGEOMETRICDISTRIBUTION_H

#include "statistics/DiscreteDistribution.h"
#include "statistics/SampleDistribution.h"
#include "base/Serializable.h"
#include "exceptions/BadArgumentException.h"

/** The HyperGeometricDistribution class represents an hypergeometric
    distribution, i.e., a discrete distribution that models the number of
    successes in a sequence of N draws from a finite population without
    replacement.
    \brief Hypergeometric distribution
  */
template <size_t M> class HyperGeometricDistribution :
  public DiscreteDistribution<size_t, M>,
  public DiscreteDistribution<size_t, M - 1>,
  public SampleDistribution<Eigen::Matrix<size_t, M, 1> >,
  public virtual Serializable {
public:
  /** \name Traits
    @{
    */
  /// Support for the N - 1 simplex
  template <size_t N, size_t D = 0> struct Traits {
  public:
    /// Returns the probability mass function at a point
    static double pmf(const HyperGeometricDistribution<N>& distribution,
      const Eigen::Matrix<size_t, N - 1, 1>& value);
    /// Returns the log-probability mass function at a point
    static double logpmf(const HyperGeometricDistribution<N>& distribution,
      const Eigen::Matrix<size_t, N - 1, 1>& value);
  };
  /// Support for N = 2
  template <size_t D> struct Traits<2, D> {
  public:
    /// Returns the probability mass function at a point
    static double pmf(const HyperGeometricDistribution<2>& distribution,
      const size_t& value);
    /// Returns the log-probability mass function at a point
    static double logpmf(const HyperGeometricDistribution<2>& distribution,
      const size_t& value);
  };
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameters
  HyperGeometricDistribution(size_t numTrials = 1, const
    Eigen::Matrix<size_t, M, 1>&  marbles =
    Eigen::Matrix<size_t, M, 1>::Constant(1));
  /// Copy constructor
  HyperGeometricDistribution(const HyperGeometricDistribution& other);
  /// Assignment operator
  HyperGeometricDistribution& operator = (const HyperGeometricDistribution&
    other);
  /// Destructor
  virtual ~HyperGeometricDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the number of trials
  void setNumTrials(size_t numTrials) throw (BadArgumentException<size_t>);
  /// Returns the number of trials
  size_t getNumTrials() const;
  /// Sets the marbles
  void setMarbles(const Eigen::Matrix<size_t, M, 1>&  marbles);
  /// Returns the marbles
  const Eigen::Matrix<size_t, M, 1>& getMarbles() const;
  /// Returns the normalizer
  double getNormalizer() const;
  /// Returns the probability mass function at a point
  virtual double pmf(const Eigen::Matrix<size_t, M, 1>& value) const;
  /// Returns the probability mass function at a point
  virtual double pmf(const typename
    DiscreteDistribution<size_t, M - 1>::Domain& value) const;
  /// Returns the log-probability mass function at a point
  double logpmf(const Eigen::Matrix<size_t, M, 1>& value) const
    throw (BadArgumentException<Eigen::Matrix<size_t, M, 1> >);
  /// Returns the log-probability mass function at a point
  double logpmf(const typename
    DiscreteDistribution<size_t, M - 1>::Domain& value) const;
  /// Access a sample drawn from the distribution
  virtual Eigen::Matrix<size_t, M, 1> getSample() const;
  /** @}
    */

  using DiscreteDistribution<size_t, M>::operator();
  using DiscreteDistribution<size_t, M - 1>::operator();

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
  /// Marbles
  Eigen::Matrix<size_t, M, 1> mMarbles;
  /// Number of trials
  size_t mNumTrials;
  /// Normalizer
  double mNormalizer;
  /** @}
    */

};

#include "statistics/HyperGeometricDistribution.tpp"

#endif // HYPERGEOMETRICDISTRIBUTION_H
