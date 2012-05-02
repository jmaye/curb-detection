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

/** \file Normal1vScaledInvChiSquareDistribution.h
    \brief This file defines the Normal1vScaledInvChiSquareDistribution class,
           which represents a univariate normal scaled inverse chi-square
           distribution
  */

#include "statistics/DistributionTuple.h"
#include "statistics/SampleDistribution.h"
#include "statistics/ScaledInvChiSquareDistribution.h"
#include "statistics/NormalDistribution.h"
#include "statistics/StudentDistribution.h"
#include "base/Serializable.h"

/** The Normal1vScaledInvChiSquareDistribution class represents a univariate
    normal scaled inverse chi-square distribution.
    \brief Univariate normal scaled inverse chi-square distribution
  */
template <> class NormalScaledInvChiSquareDistribution<1> :
  public DistributionTuple<double, double>,
  public SampleDistribution<std::tuple<double, double> >,
  public virtual Serializable {
public:
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
  inline NormalScaledInvChiSquareDistribution(double mu = 0.0, double kappa = 1,
    double nu = 1, double sigma = 1.0);
  /// Copy constructor
  inline NormalScaledInvChiSquareDistribution(const
    NormalScaledInvChiSquareDistribution& other);
  /// Assignment operator
  inline NormalScaledInvChiSquareDistribution& operator = (const
    NormalScaledInvChiSquareDistribution& other);
  /// Destructor
  inline virtual ~NormalScaledInvChiSquareDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the variance distribution
  inline ScaledInvChiSquareDistribution getVarianceDist() const;
  /// Returns the marginal mean distribution
  inline StudentDistribution<1> getMargMeanDist() const;
  /// Returns mu parameter
  inline double getMu() const;
  /// Sets mu parameter
  inline void setMu(double mu);
  /// Returns kappa parameter
  inline double getKappa() const;
  /// Sets kappa parameter
  inline void setKappa(double kappa);
  /// Returns nu parameter
  inline double getNu() const;
  /// Sets nu parameter
  inline void setNu(double nu);
  /// Returns sigma parameter
  inline double getSigma() const;
  /// Sets sigma parameter
  inline void setSigma(double sigma);
  /// Returns the mode of the distribution
  inline Mode getMode() const;
  /// Access the probablity density function at the given value
  inline virtual double pdf(const RandomVariable& value) const;
  /// Access a sample drawn from the distribution
  inline virtual RandomVariable getSample() const;
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  inline virtual void read(std::istream& stream);
  /// Writes to standard output
  inline virtual void write(std::ostream& stream) const;
  /// Reads from a file
  inline virtual void read(std::ifstream& stream);
  /// Writes to a file
  inline virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Mu parameter: prior mean
  double mMu;
  /// Kappa parameter: prior sample size
  double mKappa;
  /// Nu parameter: prior sample size
  double mNu;
  /// Sigma parameter: prior scale
  double mSigma;
  /** @}
    */

};

#include "statistics/Normal1vScaledInvChiSquareDistribution.tpp"
