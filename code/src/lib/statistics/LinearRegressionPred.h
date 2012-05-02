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

/** \file LinearRegressionPred.h
    \brief This file defines the LinearRegressionPred class, which represents a
           multivariate predictive linear regression
  */

#ifndef LINEARREGRESSIONPRED_H
#define LINEARREGRESSIONPRED_H

#include "statistics/ContinuousDistribution.h"
#include "functions/LinearBasisFunction.h"
#include "statistics/SampleDistribution.h"
#include "base/Serializable.h"

/** The LinearRegressionPred class represents a multivariate predictive linear
    regression.
    \brief Multivariate predictive linear regression
  */
template <size_t M> class LinearRegressionPred :
  public ContinuousDistribution<double, M>,
  public SampleDistribution<Eigen::Matrix<double, M, 1> >,
  public virtual Serializable {
public:
  /** \name Types
    @{
    */
  /// Distribution type
  typedef ContinuousDistribution<double, M> DistributionType;
  /// Random variable type
  typedef typename DistributionType::RandomVariable RandomVariable;
  /** @}
    */

  /** \name Traits
    @{
    */
  /// Normal case
  template <size_t N, size_t D = 0> struct Traits {
  public:
    /// Returns the pdf
    static double pdf(const LinearRegressionPred<N>& linearRegression,
      const Eigen::Matrix<double, N, 1>& value);
    /// Returns the log-pdf
    static double logpdf(const LinearRegressionPred<N>& linearRegression,
      const Eigen::Matrix<double, N, 1>& value);
    /// Returns a sample
    static Eigen::Matrix<double, N, 1> getSample(const LinearRegressionPred<N>&
      linearRegression);
    /// Returns the predictive mean
    static double getPredMean(const LinearRegressionPred<N>& linearRegression);
    /// Returns the predictive variance
    static double getPredVariance(const LinearRegressionPred<N>&
      linearRegression);
  };
  /// Support for N = 2
  template <size_t D> struct Traits<2, D> {
  public:
    /// Returns the pdf
    static double pdf(const LinearRegressionPred<2>& linearRegression,
      const Eigen::Matrix<double, 2, 1>& value);
    /// Returns the log-pdf
    static double logpdf(const LinearRegressionPred<2>& linearRegression,
      const Eigen::Matrix<double, 2, 1>& value);
    /// Returns a sample
    static Eigen::Matrix<double, 2, 1> getSample(const LinearRegressionPred<2>&
      linearRegression);
    /// Returns the predictive mean
    static double getPredMean(const LinearRegressionPred<2>& linearRegression);
    /// Returns the predictive variance
    static double getPredVariance(const LinearRegressionPred<2>&
      linearRegression);
  };
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs linear regression from parameters
  LinearRegressionPred(double degrees = 1, const LinearBasisFunction<double, M>&
    linearBasisFunction = LinearBasisFunction<double, M>(), const
    Eigen::Matrix<double, M, M> coeffsCovariance =
    Eigen::Matrix<double, M, M>::Identity(),
    double variance = 1.0, const Eigen::Matrix<double, M - 1, 1>& basis =
    Eigen::Matrix<double, M - 1, 1>::Ones());
  /// Copy constructor
  LinearRegressionPred(const LinearRegressionPred& other);
  /// Assignment operator
  LinearRegressionPred& operator = (const LinearRegressionPred& other);
  /// Destructor
  ~LinearRegressionPred();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the degrees of freedom
  double getDegrees() const;
  /// Sets the degrees of freedom
  void setDegrees(double degrees);
  /// Returns the linear basis function
  const LinearBasisFunction<double, M>& getLinearBasisFunction() const;
  /// Sets the linear basis function
  void setLinearBasisFunction(const LinearBasisFunction<double, M>&
    linearBasisFunction);
  /// Returns the coefficients covariance
  const Eigen::Matrix<double, M, M>& getCoeffsCovariance() const;
  /// Sets the coefficients covariance
  void setCoeffsCovariance(const Eigen::Matrix<double, M, M>& coeffsCovariance);
  /// Returns the variance
  double getVariance() const;
  /// Sets the variance
  void setVariance(double variance);
  /// Returns the basis
  const Eigen::Matrix<double, M - 1, 1>& getBasis() const;
  /// Sets the basis
  void setBasis(const Eigen::Matrix<double, M - 1, 1>& basis);
  /// Returns the predictive mean
  double getPredMean() const;
  /// Returns the predictive variance
  double getPredVariance() const;
  /// Access the probability density function at the given value
  virtual double pdf(const RandomVariable& value) const;
  /// Access the log-probability density function at the given value
  double logpdf(const RandomVariable& value) const;
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
  /// Degrees of freedom
  double mDegrees;
  /// Linear basis function
  LinearBasisFunction<double, M> mLinearBasisFunction;
  /// Covariance on the coefficients
  Eigen::Matrix<double, M, M> mCoeffsCovariance;
  /// Variance
  double mVariance;
  /// Current basis
  Eigen::Matrix<double, M - 1, 1> mBasis;
  /** @}
    */

};

#include "statistics/LinearRegressionPred.tpp"

#endif // LINEARREGRESSIONPRED_H
