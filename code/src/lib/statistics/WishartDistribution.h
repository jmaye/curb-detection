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

#include "statistics/ContinuousDistribution.h"
#include "statistics/SampleDistribution.h"
#include "base/Serializable.h"
#include "exceptions/BadArgumentException.h"

#include <Eigen/Cholesky>

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
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the distribution from the parameters
  WishartDistribution(double degrees = M, const Eigen::Matrix<double, M, M>&
    scale = Eigen::Matrix<double, M, M>::Identity());
  /// Copy constructor
  WishartDistribution(const WishartDistribution<M>& other);
  /// Assignment operator
  WishartDistribution<M>& operator = (const WishartDistribution<M>& other);
  /// Destructor
  virtual ~WishartDistribution();
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
  void setScale(const Eigen::Matrix<double, M, M>& covariance)
    throw (BadArgumentException<Eigen::Matrix<double, M, M> >);
  /// Returns the scale matrix of the distribution
  const Eigen::Matrix<double, M, M>& getScale() const;
  /// Returns the inverse scale matrix of the distribution
  const Eigen::Matrix<double, M, M>& getInverseScale() const;
  /// Returns the determinant of the scale matrix
  double getDeterminant() const;
  /// Returns the normalizer of the distribution
  double getNormalizer() const;
  /// Returns the cholesky decomposition of the scale matrix
  const Eigen::LLT<Eigen::Matrix<double, M, M> >& getTransformation() const;
  /// Returns the mean of the distribution
  Eigen::Matrix<double, M, M> getMean() const;
  /// Returns the mode of the distribution
  Eigen::Matrix<double, M, M> getMode() const;
  /// Access the probability density function at the given value
  virtual double pdf(const Eigen::Matrix<double, M, M>& value) const;
  /// Access the log-probability density function at the given value
  double logpdf(const Eigen::Matrix<double, M, M>& value) const 
    throw (BadArgumentException<Eigen::Matrix<double, M, M> >);
  /// Access a sample drawn from the distribution
  virtual Eigen::Matrix<double, M, M> getSample() const;
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
  /// Degrees of freedom
  double mDegrees;
  /// Scale
  Eigen::Matrix<double, M, M> mScale;
  /// Inverse scale
  Eigen::Matrix<double, M, M> mInverseScale;
  /// Scale determinant
  double mDeterminant;
  /// Normalizer
  double mNormalizer;
  /// Cholesky decomposition of the scale matrix
  Eigen::LLT<Eigen::Matrix<double, M, M> > mTransformation;
  /** @}
    */

};

#include "statistics/WishartDistribution.tpp"

#endif // WISHARTDISTRIBUTION_H
