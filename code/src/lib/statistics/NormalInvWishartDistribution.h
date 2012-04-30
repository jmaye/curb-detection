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

/** \file NormalInvWishartDistribution.h
    \brief This file defines the NormalNormalInvWishartDistribution class,
           which represents a normal scaled inverse chi-square distribution
  */

#ifndef NORMALINVWISHARTDISTRIBUTION_H
#define NORMALINVWISHARTDISTRIBUTION_H

#include "statistics/DistributionTuple.h"
#include "statistics/SampleDistribution.h"
#include "statistics/InvWishartDistribution.h"
#include "statistics/NormalDistribution.h"
#include "statistics/StudentDistribution.h"
#include "base/Serializable.h"

/** The NormalInvWishartDistribution class represents an normal scaled
    inverse chi-square distribution.
    \brief Normal scaled inverse chi-square distribution
  */
template <size_t M> class NormalInvWishartDistribution :
  public DistributionTuple<Eigen::Matrix<double, M, 1>,
    Eigen::Matrix<double, M, M> >,
  public SampleDistribution<std::tuple<Eigen::Matrix<double, M, 1>,
    Eigen::Matrix<double, M, M> > >,
  public virtual Serializable {
public:
  /** \name Types
    @{
    */
  /// Random variable type
  typedef typename DistributionTuple<Eigen::Matrix<double, M, 1>,
    Eigen::Matrix<double, M, M> >::RandomVariable RandomVariable;
  /// Mode type
  typedef RandomVariable Mode;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /*! \brief Constructs distribution from parameters
  *
  * Location of mean: mu
  * Scale of mean: sigma / kappa
  * Scale of variance: sigma
  * Degrees of freedom of variance: nu
  */
  NormalInvWishartDistribution(const Eigen::Matrix<double, M, 1>& mu =
    Eigen::Matrix<double, M, 1>::Zero(), double kappa = 1, double nu = M,
    const Eigen::Matrix<double, M, M>& sigma =
    Eigen::Matrix<double, M, M>::Identity());
  /// Copy constructor
  NormalInvWishartDistribution(const NormalInvWishartDistribution& other);
  /// Assignment operator
  NormalInvWishartDistribution& operator = (const
    NormalInvWishartDistribution& other);
  /// Destructor
  virtual ~NormalInvWishartDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the covariance distribution
  InvWishartDistribution<M> getCovarianceDist() const;
  /// Returns the marginal mean distribution
  StudentDistribution<M> getMargMeanDist() const;
  /// Returns mu parameter
  const Eigen::Matrix<double, M, 1>& getMu() const;
  /// Sets mu parameter
  void setMu(const Eigen::Matrix<double, M, 1>& mu);
  /// Returns kappa parameter
  double getKappa() const;
  /// Sets kappa parameter
  void setKappa(double kappa);
  /// Returns nu parameter
  double getNu() const;
  /// Sets nu parameter
  void setNu(double nu);
  /// Returns sigma parameter
  const Eigen::Matrix<double, M, M>& getSigma() const;
  /// Sets sigma parameter
  void setSigma(const Eigen::Matrix<double, M, M>& sigma);
  /// Returns the mode of the distribution
  Mode getMode() const;
  /// Access the probablity density function at the given value
  virtual double pdf(const RandomVariable& value) const;
  /// Access a sample drawn from the distribution
  virtual RandomVariable getSample() const;
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
  /// Mu parameter: prior mean
  Eigen::Matrix<double, M, 1> mMu;
  /// Kappa parameter: prior sample size
  double mKappa;
  /// Nu parameter: prior sample size
  double mNu;
  /// Sigma parameter: prior scale
  Eigen::Matrix<double, M, M> mSigma;
  /** @}
    */

};

#include "statistics/NormalInvWishartDistribution.tpp"

#endif // NORMALINVWISHARTDISTRIBUTION_H
