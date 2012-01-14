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
    \brief This file defines the LinearRegressionPred class, which represents
           a predictive multivariate linear regression
  */

#ifndef LINEARREGRESSIONPRED_H
#define LINEARREGRESSIONPRED_H

#include "statistics/StudentDistribution.h"
#include "base/Serializable.h"
#include "exceptions/BadArgumentException.h"

/** The LinearRegressionPred class represents a multivariate predictive linear
    regression.
    \brief Multivariate predictive linear regression
  */
template <size_t M> class LinearRegressionPred :
  public StudentDistribution<1>,
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs linear regression from parameters
  LinearRegressionPred(double degrees = 1.0, const Eigen::Matrix<double, M, 1>&
    coefficients = Eigen::Matrix<double, M, 1>::Ones(), const
    Eigen::Matrix<double, M, M>& coeffCovariance =
    Eigen::Matrix<double, M, M>::Identity(), double regressionVariance = 1.0,
    const Eigen::Matrix<double, M, 1>& basis =
    Eigen::Matrix<double, M, 1>::Zero());
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
  /// Sets the coefficients
  void setCoefficients(const Eigen::Matrix<double, M, 1>& coefficients);
  /// Returns the coefficients
  const Eigen::Matrix<double, M, 1>& getCoefficients() const;
  /// Sets the coefficients covariance
  void setCoeffCovariance(const Eigen::Matrix<double, M, M>& coeffCovariance);
  /// Returns the coefficients covariance
  const Eigen::Matrix<double, M, M>& getCoeffCovariance() const;
  /// Sets the regression variance
  void setRegressionVariance(double variance);
  /// Returns the regression variance
  double getRegressionVariance() const;
  /// Sets the basis
  void setBasis(const Eigen::Matrix<double, M, 1>& basis);
  /// Returns the basis
  const Eigen::Matrix<double, M, 1>& getBasis() const;
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
  /// Regression weights
  Eigen::Matrix<double, M, 1> mCoefficients;
  /// Regression weights covariance
  Eigen::Matrix<double, M, M> mCoeffCovariance;
  /// Regression variance
  double mRegressionVariance;
  /// Basis
  Eigen::Matrix<double, M, 1> mBasis;
  /** @}
    */

};

#include "statistics/LinearRegressionPred.tpp"

#endif // LINEARREGRESSIONPRED_H
