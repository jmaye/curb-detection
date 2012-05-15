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

/** \file WishartDistribution.h
    \brief This file defines the WishartDistribution class, which represents a
           Wishart distribution
  */

#ifndef WISHARTDISTRIBUTION_H
#define WISHARTDISTRIBUTION_H

#include <Eigen/Cholesky>

#include "statistics/ContinuousDistribution.h"
#include "statistics/SampleDistribution.h"
#include "base/Serializable.h"

/** The WishartDistribution class represents a Wishart distribution, i.e., a
    continuous distribution that is a conjugate prior for precision matrix in a
    multivariate normal distribution.
    \brief Wishart distribution
  */
template <size_t M> class WishartDistribution :
  public ContinuousDistribution<double, M, M>,
  public SampleDistribution<Eigen::Matrix<double, M, M> >,
  public virtual Serializable {
public:
  /** \name Types
    @{
    */
  /// Distribution type
  typedef ContinuousDistribution<double, M, M> DistributionType;
  /// Random variable type
  typedef typename DistributionType::RandomVariable RandomVariable;
  /// Mean type
  typedef typename DistributionType::Mean Mean;
  /// Mode type
  typedef typename DistributionType::Mode Mode;
  /// Covariance type
  typedef typename DistributionType::Covariance Covariance;
  /// Scale type
  typedef typename DistributionType::Covariance Scale;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs the distribution from the parameters
  WishartDistribution(double degrees = M, const Scale& scale =
    Scale::Identity());
  /// Copy constructor
  WishartDistribution(const WishartDistribution& other);
  /// Assignment operator
  WishartDistribution& operator = (const WishartDistribution& other);
  /// Destructor
  virtual ~WishartDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the degrees of freedom of the distribution
  void setDegrees(double degrees);
  /// Returns the degrees of freedom of the distribution
  double getDegrees() const;
  /// Sets the scale matrix of the distribution
  void setScale(const Scale& scale);
  /// Returns the scale matrix of the distribution
  const Scale& getScale() const;
  /// Returns the inverse scale matrix of the distribution
  const Scale& getInverseScale() const;
  /// Returns the determinant of the scale matrix
  double getDeterminant() const;
  /// Returns the normalizer of the distribution
  double getNormalizer() const;
  /// Returns the cholesky decomposition of the scale matrix
  const Eigen::LLT<Scale>& getTransformation() const;
  /// Returns the mean of the distribution
  Mean getMean() const;
  /// Returns the mode of the distribution
  Mode getMode() const;
  /// Returns the covariance of the distribution
  Covariance getCovariance() const;
  /// Access the probability density function at the given value
  virtual double pdf(const RandomVariable& value) const;
  /// Access the log-probability density function at the given value
  double logpdf(const RandomVariable& value) const;
  /// Access a sample drawn from the distribution
  virtual RandomVariable getSample() const;
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Compute nornalizer
  void computeNormalizer();
  /** @}
    */

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
  /// Degrees of freedom
  double mDegrees;
  /// Scale
  Scale mScale;
  /// Inverse scale
  Scale mInverseScale;
  /// Scale determinant
  double mDeterminant;
  /// Normalizer
  double mNormalizer;
  /// Cholesky decomposition of the scale matrix
  Eigen::LLT<Scale> mTransformation;
  /** @}
    */

};

#include "statistics/WishartDistribution.tpp"

#endif // WISHARTDISTRIBUTION_H
