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

#include "statistics/ContinuousDistribution.h"
#include "statistics/SampleDistribution.h"
#include "base/Serializable.h"
#include "exceptions/BadArgumentException.h"

#include <Eigen/Cholesky>

/** The InvWishartDistribution class represents an inverse Wishart distribution.
    \brief Inverse Wishart distribution
  */
template <size_t M> class InvWishartDistribution :
  public ContinuousDistribution<double, M, M>,
  public SampleDistribution<Eigen::Matrix<double, M, M> >,
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the distribution from the parameters
  InvWishartDistribution(double degrees = M, const Eigen::Matrix<double, M, M>&
    scale = Eigen::Matrix<double, M, M>::Identity());
  /// Copy constructor
  InvWishartDistribution(const InvWishartDistribution<M>& other);
  /// Assignment operator
  InvWishartDistribution<M>& operator = (const InvWishartDistribution<M>&
    other);
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
  void setScale(const Eigen::Matrix<double, M, M>& covariance)
    throw (BadArgumentException<Eigen::Matrix<double, M, M> >);
  /// Returns the scale matrix of the distribution
  const Eigen::Matrix<double, M, M>& getScale() const;
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
  /// Scale determinant
  double mDeterminant;
  /// Normalizer
  double mNormalizer;
  /// Cholesky decomposition of the scale matrix
  Eigen::LLT<Eigen::Matrix<double, M, M> > mTransformation;
  /** @}
    */

};

#include "statistics/InvWishartDistribution.tpp"

#endif // INVWISHARTDISTRIBUTION_H
