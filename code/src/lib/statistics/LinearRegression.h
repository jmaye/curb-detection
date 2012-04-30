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

/** \file LinearRegression.h
    \brief This file defines the LinearRegression class, which represents a
           multivariate linear regression
  */

#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H

#include "statistics/ContinuousDistribution.h"
#include "functions/LinearBasisFunction.h"
#include "statistics/SampleDistribution.h"
#include "base/Serializable.h"

/** The LinearRegression class represents a multivariate linear regression.
    \brief Multivariate linear regression
  */
template <size_t M> class LinearRegression :
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
    static double pdf(const LinearRegression<N>& linearRegression,
      const Eigen::Matrix<double, N, 1>& value);
    /// Returns the log-pdf
    static double logpdf(const LinearRegression<N>& linearRegression,
      const Eigen::Matrix<double, N, 1>& value);
    /// Returns a sample
    static Eigen::Matrix<double, N, 1> getSample(const LinearRegression<N>&
      linearRegression);
  };
  /// Support for N = 2
  template <size_t D> struct Traits<2, D> {
  public:
    /// Returns the pdf
    static double pdf(const LinearRegression<2>& linearRegression,
      const Eigen::Matrix<double, 2, 1>& value);
    /// Returns the log-pdf
    static double logpdf(const LinearRegression<2>& linearRegression,
      const Eigen::Matrix<double, 2, 1>& value);
    /// Returns a sample
    static Eigen::Matrix<double, 2, 1> getSample(const LinearRegression<2>&
      linearRegression);
  };
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs linear regression from parameters
  LinearRegression(const LinearBasisFunction<double, M>& linearBasisFunction =
    LinearBasisFunction<double, M>(), double variance = 1.0,
    const Eigen::Matrix<double, M - 1, 1>& basis =
    Eigen::Matrix<double, M - 1, 1>::Ones());
  /// Copy constructor
  LinearRegression(const LinearRegression& other);
  /// Assignment operator
  LinearRegression& operator = (const LinearRegression& other);
  /// Destructor
  ~LinearRegression();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the linear basis function
  const LinearBasisFunction<double, M>& getLinearBasisFunction() const;
  /// Sets the linear basis function
  void setLinearBasisFunction(const LinearBasisFunction<double, M>&
    linearBasisFunction);
  /// Returns the variance
  double getVariance() const;
  /// Sets the variance
  void setVariance(double variance);
  /// Returns the basis
  const Eigen::Matrix<double, M - 1, 1>& getBasis() const;
  /// Sets the basis
  void setBasis(const Eigen::Matrix<double, M - 1, 1>& basis);
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
  /// Linear basis function
  LinearBasisFunction<double, M> mLinearBasisFunction;
  /// Variance
  double mVariance;
  /// Current basis
  Eigen::Matrix<double, M - 1, 1> mBasis;
  /** @}
    */

};

#include "statistics/LinearRegression.tpp"

#endif // LINEARREGRESSION_H
