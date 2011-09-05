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

/** \file EstimatorBayesLinearRegression.h
    \brief This file implements a Bayesian estimator for ordinary linear
           regression models with conjugate prior.
  */

#include "statistics/LinearRegression.h"
#include "statistics/LinearRegressionPred.h"
#include "statistics/StudentDistribution.h"
#include "statistics/ScaledInvChiSquareDistribution.h"

#include <vector>

/** The class EstimatorBayes is implemented for ordinary linear regression
    models.
    \brief Ordinary linear regresssion Bayesian estimator with conjugate prior
  */
template <size_t M> class EstimatorBayes<LinearRegression<M>, M> :
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  EstimatorBayes(const Eigen::Matrix<double, M, 1>& mu =
    Eigen::Matrix<double, M, 1>::Ones(), const Eigen::Matrix<double, M, M>& V =
    Eigen::Matrix<double, M, M>::Identity(), double nu = 1.0, double sigma =
    1.0);
  /// Copy constructor
  EstimatorBayes(const EstimatorBayes<LinearRegression<M>, M>& other);
  /// Assignment operator
  EstimatorBayes<LinearRegression<M>, M>& operator =
    (const EstimatorBayes<LinearRegression<M>, M>& other);
  /// Destructor
  virtual ~EstimatorBayes();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the posterior marginal coefficients distribution
  const StudentDistribution<M>& getPostCoeffDist() const;
  /// Returns the posterior marginal variance distribution
  const ScaledInvChiSquareDistribution& getPostVarianceDist() const;
  /// Returns the posterior predictive distribution
  const LinearRegressionPred<M>& getPostPredDist() const;
  /// Add point to the estimator
  void addPoint(const Eigen::Matrix<double, M, 1>& point);
  /// Add points to the estimator
  void addPoints(const std::vector<Eigen::Matrix<double, M, 1> >& points);
  /// Add points to the estimator with weights
  void addPoints(const std::vector<Eigen::Matrix<double, M, 1> >& points,
    const Eigen::Matrix<double, Eigen::Dynamic, 1>& weights);
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
  /// Posterior marginal coefficients distribution
  StudentDistribution<M> mPostCoeffDist;
  /// Posterior marginal variance distribution
  ScaledInvChiSquareDistribution mPostVarianceDist;
  /// Posterior predictive distribution
  LinearRegressionPred<M> mPostPredDist;
  /// Hyperparameter mu: prior coefficients mean
  Eigen::Matrix<double, M, 1> mMu;
  /// Hyperparameter V: prior coefficients covariance
  Eigen::Matrix<double, M, M> mV;
  /// Hyperparameter nu: prior degrees of freedom
  double mNu;
  /// Hyperparameter sigma: prior regression variance
  double mSigma;
  /** @}
    */

};

#include "statistics/EstimatorBayesLinearRegression.tpp"
