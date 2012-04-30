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

/** \file InvWishartDistribution.h
    \brief This file defines the InvWishartDistribution class, which represents
           an inverse Wishart distribution
  */

#ifndef INVWISHARTDISTRIBUTION_H
#define INVWISHARTDISTRIBUTION_H

#include <Eigen/Cholesky>

#include "statistics/ContinuousDistribution.h"
#include "statistics/SampleDistribution.h"
#include "base/Serializable.h"
#include "exceptions/BadArgumentException.h"
#include "exceptions/InvalidOperationException.h"

/** The InvWishartDistribution class represents an inverse Wishart distribution.
    \brief Inverse Wishart distribution
  */
template <size_t M> class InvWishartDistribution :
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
  InvWishartDistribution(double degrees = M, const Scale&
    scale = Scale::Identity());
  /// Copy constructor
  InvWishartDistribution(const InvWishartDistribution& other);
  /// Assignment operator
  InvWishartDistribution& operator = (const InvWishartDistribution& other);
  /// Destructor
  virtual ~InvWishartDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the degrees of freedom of the distribution
  void setDegrees(double degrees) throw (BadArgumentException<double>);
  /// Returns the degrees of freedom of the distribution
  double getDegrees() const;
  /// Sets the scale matrix of the distribution
  void setScale(const Scale& scale) throw (BadArgumentException<Scale>);
  /// Returns the scale matrix of the distribution
  const Scale& getScale() const;
  /// Returns the determinant of the scale matrix
  double getDeterminant() const;
  /// Returns the normalizer of the distribution
  double getNormalizer() const;
  /// Returns the cholesky decomposition of the scale matrix
  const Eigen::LLT<Scale>& getTransformation() const;
  /// Returns the mean of the distribution
  Mean getMean() const throw (InvalidOperationException);
  /// Returns the mode of the distribution
  Mode getMode() const;
  /// Returns the covariance of the distribution
  Covariance getCovariance() const throw (InvalidOperationException);
  /// Access the probability density function at the given value
  virtual double pdf(const RandomVariable& value) const;
  /// Access the log-probability density function at the given value
  double logpdf(const RandomVariable& value) const 
    throw (BadArgumentException<RandomVariable>);
  /// Access a sample drawn from the distribution
  virtual RandomVariable getSample() const;
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Compute normalizer
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

#include "statistics/InvWishartDistribution.tpp"

#endif // INVWISHARTDISTRIBUTION_H
