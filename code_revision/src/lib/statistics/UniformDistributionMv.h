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

/** \file UniformDistributionMv.h
    \brief This file contains an interface to the multivariate uniform
           distributions
  */

#ifndef UNIFORMDISTRIBUTIONMV_H
#define UNIFORMDISTRIBUTIONMV_H

#include "statistics/ContinuousDistribution.h"
#include "statistics/DiscreteDistribution.h"
#include "statistics/SampleDistribution.h"
#include "base/Serializable.h"
#include "exceptions/BadArgumentException.h"
#include "utils/IfThenElse.h"
#include "utils/IsReal.h"

/** The UniformDistributionMv class represents an interface to the multivariate
    uniform distributions.
    \brief Multivariate uniform distribution
  */
template <typename X, size_t M> class UniformDistribution:
  public IfThenElse<typename IsReal<X>::Result,
    ContinuousDistribution<X, M>, DiscreteDistribution<X, M> >::Result,
  public SampleDistribution<Eigen::Matrix<X, M, 1> >,
  public virtual Serializable {
public:
  /** \name Traits
    @{
    */
  /// Mapping in case one calls the pdf instead of pmf
  template <typename U, size_t D = 0> struct Traits {
  public:
    /// Access the probablity density function at the given value
    static double pdf(const UniformDistribution<U, M>& distribution, const Eigen::Matrix<U, M, 1>& value);
    /// Access the probablity mass function at the given value
    static double pmf(const UniformDistribution<U, M>& distribution, const Eigen::Matrix<U, M, 1>& value);
  };
  /// Mapping in case one calls the pmf instead of pdf
  template <size_t D> struct Traits<float, D> {
  public:
    /// Access the probablity density function at the given value
    static double pdf(const UniformDistribution<float, M>& distribution,
      const Eigen::Matrix<float, M, 1>&);
    /// Access the probablity mass function at the given value
    static double pmf(const UniformDistribution<float, M>& distribution,
      const Eigen::Matrix<float, M, 1>&);
  };
  /// Mapping in case one calls the pmf instead of pdf
  template <size_t D> struct Traits<double, D> {
  public:
    /// Access the probablity density function at the given value
    static double pdf(const UniformDistribution<double, M>& distribution,
      const Eigen::Matrix<double, M, 1>&);
    /// Access the probablity mass function at the given value
    static double pmf(const UniformDistribution<double, M>& distribution,
      const Eigen::Matrix<double, M, 1>&);
  };
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameters
  UniformDistribution(const Eigen::Matrix<X, M, 1>& minSupport =
    Eigen::Matrix<X, M, 1>::Zero(), const Eigen::Matrix<X, M, 1>&
    maxSupport = Eigen::Matrix<X, M, 1>::Ones());
  /// Copy constructor
  UniformDistribution(const UniformDistribution<X, M>& other);
  /// Assignment operator
  UniformDistribution& operator = (const UniformDistribution<X, M>& other);
  /// Destructor
  virtual ~UniformDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the support of the distribution
  void setSupport(const Eigen::Matrix<X, M, 1>& minSupport, const
    Eigen::Matrix<X, M, 1>& maxSupport)
    throw (BadArgumentException<Eigen::Matrix<X, M, 1> >);
  /// Sets the minimum support
  void setMinSupport(const Eigen::Matrix<X, M, 1>& minSupport);
  /// Returns the minimum support
  const Eigen::Matrix<X, M, 1>& getMinSupport() const;
  /// Sets the maximum support
  void setMaxSupport(const Eigen::Matrix<X, M, 1>& maxSupport);
  /// Returns the maximum support
  const Eigen::Matrix<X, M, 1>& getMaxSupport() const;
  /// Access the multivariate uniform distribution's support area
  X getSupportArea() const;
  /// Access the probablity density function at the given value
  virtual double pdf(const Eigen::Matrix<X, M, 1>& value) const;
  /// Access the probablity mass function at the given value
  virtual double pmf(const Eigen::Matrix<X, M, 1>& value) const;
  /// Access a sample drawn from the distribution
  virtual Eigen::Matrix<X, M, 1> getSample() const;
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
  /// Minimum support of the distribution
  Eigen::Matrix<X, M, 1> mMinSupport;
  /// Maximum support of the distribution
  Eigen::Matrix<X, M, 1> mMaxSupport;
  /// Support area
  X mSupportArea;
  /** @}
    */

};

#include "statistics/UniformDistributionMv.tpp"

#endif // UNIFORMDISTRIBUTIONMV_H
