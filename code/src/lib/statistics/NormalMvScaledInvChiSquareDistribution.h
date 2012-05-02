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

/** \file NormalMvScaledInvChiSquareDistribution.h
    \brief This file defines the NormalMvScaledInvChiSquareDistribution class,
           which represents a multivariate normal scaled inverse chi-square
           distribution
  */

#include "statistics/DistributionTuple.h"
#include "statistics/SampleDistribution.h"
#include "statistics/ScaledInvChiSquareDistribution.h"
#include "statistics/NormalDistribution.h"
#include "statistics/StudentDistribution.h"
#include "base/Serializable.h"

/** The NormalMvScaledInvChiSquareDistribution class represents a multivariate
    normal scaled inverse chi-square distribution.
    \brief Multivariate normal scaled inverse chi-square distribution
  */
template <size_t M> class NormalScaledInvChiSquareDistribution :
  public DistributionTuple<typename NormalDistribution<M>::RandomVariable,
    double>,
  public SampleDistribution<std::tuple<typename
    NormalDistribution<M>::RandomVariable, double> >,
  public virtual Serializable {
public:
  /** \name Types
    @{
    */
  /// Distribution type
  typedef DistributionTuple<typename NormalDistribution<M>::RandomVariable,
    double> DistributionType;
  /// Random variable type
  typedef typename DistributionType::RandomVariable RandomVariable;
  /// Mode type
  typedef typename DistributionType::Mode Mode;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  ///Constructs distribution from parameters
  NormalScaledInvChiSquareDistribution(Eigen::Matrix<double, M, 1> mu =
    Eigen::Matrix<double, M, 1>::Zero(), Eigen::Matrix<double, M, M> kappa =
    Eigen::Matrix<double, M, M>::Identity(),
    double nu = M, double sigma = 1.0);
  /// Copy constructor
  NormalScaledInvChiSquareDistribution(const
    NormalScaledInvChiSquareDistribution& other);
  /// Assignment operator
  NormalScaledInvChiSquareDistribution& operator = (const
    NormalScaledInvChiSquareDistribution& other);
  /// Destructor
  virtual ~NormalScaledInvChiSquareDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the variance distribution
  ScaledInvChiSquareDistribution getVarianceDist() const;
  /// Returns the marginal mean distribution
  StudentDistribution<M> getMargMeanDist() const;
  /// Returns mu parameter
  const Eigen::Matrix<double, M, 1>& getMu() const;
  /// Sets mu parameter
  void setMu(const Eigen::Matrix<double, M, 1>& mu);
  /// Returns kappa parameter
  const Eigen::Matrix<double, M, M>& getKappa() const;
  /// Sets kappa parameter
  void setKappa(const Eigen::Matrix<double, M, M>& kappa);
  /// Returns nu parameter
  double getNu() const;
  /// Sets nu parameter
  void setNu(double nu);
  /// Returns sigma parameter
  double getSigma() const;
  /// Sets sigma parameter
  void setSigma(double sigma);
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
  /// Mu parameter
  Eigen::Matrix<double, M, 1> mMu;
  /// Kappa parameter
  Eigen::Matrix<double, M, M> mKappa;
  /// Nu parameter: prior sample size
  double mNu;
  /// Sigma parameter: prior scale
  double mSigma;
  /** @}
    */

};

#include "statistics/NormalMvScaledInvChiSquareDistribution.tpp"
