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

/** \file NormalDistributionMv.h
    \brief This file defines the NormalDistributionMv class, which represents a
           multivariate normal distribution
  */

#include "statistics/ContinuousDistribution.h"
#include "statistics/SampleDistribution.h"
#include "base/Serializable.h"
#include "exceptions/BadArgumentException.h"

#include <Eigen/Cholesky>

/** The NormalDistributionMv class represents a multivariate normal
    distribution.
    \brief Multivariate normal distribution
  */
template <size_t M> class NormalDistribution :
  public ContinuousDistribution<double, M>,
  public SampleDistribution<Eigen::Matrix<double, M, 1> >,
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the distribution from the parameters
  NormalDistribution(const Eigen::Matrix<double, M, 1>& mean =
    Eigen::Matrix<double, M, 1>::Zero(), const Eigen::Matrix<double, M, M>&
    covariance = Eigen::Matrix<double, M, M>::Identity());
  /// Copy constructor
  NormalDistribution(const NormalDistribution<M>& other);
  /// Assignment operator
  NormalDistribution<M>& operator = (const NormalDistribution<M>& other);
  /// Destructor
  virtual ~NormalDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the mean of the distribution
  void setMean(const Eigen::Matrix<double, M, 1>& mean);
  /// Returns the mean of the distribution
  const Eigen::Matrix<double, M, 1>& getMean() const;
  /// Sets the covariance matrix of the distribution
  void setCovariance(const Eigen::Matrix<double, M, M>& covariance)
    throw (BadArgumentException<Eigen::Matrix<double, M, M> >);
  /// Returns the covariance matrix of the distribution
  const Eigen::Matrix<double, M, M>& getCovariance() const;
  /// Returns the precision matrix of the distribution
  const Eigen::Matrix<double, M, M>& getPrecision() const;
  /// Returns the determinant of the covariance matrix
  double getDeterminant() const;
  /// Returns the normalizer of the distribution
  double getNormalizer() const;
  /// Returns the mode of the distribution
  const Eigen::Matrix<double, M, 1>& getMode() const;
  /// Returns the cholesky decomposition of the covariance matrix
  const Eigen::LLT<Eigen::Matrix<double, M, M> >& getTransformation() const;
  /// Access the probability density function at the given value
  virtual double pdf(const Eigen::Matrix<double, M, 1>& value) const;
  /// Access the log-probability density function at the given value
  double logpdf(const Eigen::Matrix<double, M, 1>& value) const;
  /// Access a sample drawn from the distribution
  virtual Eigen::Matrix<double, M, 1> getSample() const;
  /// Returns the KL-divergence with another distribution
  double KLDivergence(const NormalDistribution<M>& other) const;
  /// Returns the squared Mahalanobis distance from a point
  double mahalanobisDistance(const Eigen::Matrix<double, M, 1>& value) const;
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
  /// Mean of the normal distribution
  Eigen::Matrix<double, M, 1> mMean;
  /// Covariance matrix of the normal distribution
  Eigen::Matrix<double, M, M> mCovariance;
  /// Precision matrix of the normal distribution
  Eigen::Matrix<double, M, M> mPrecision;
  /// Determinant of the covariance matrix
  double mDeterminant;
  /// Normalizer of the distribution
  double mNormalizer;
  /// Cholesky decomposition of the covariance matrix
  Eigen::LLT<Eigen::Matrix<double, M, M> > mTransformation;
  /** @}
    */

};

#include "statistics/NormalDistributionMv.tpp"
