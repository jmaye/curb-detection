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

/** \file EstimatorBayesNormalMv.h
    \brief This file implements a Bayesian estimator for multivariate normal
           distributions with conjugate prior
  */

#include "statistics/NormalDistribution.h"
#include "statistics/StudentDistribution.h"
#include "statistics/InvWishartDistribution.h"

#include <vector>

/** The class EstimatorBayes is implemented for multivariate normal
    distributions with conjugate prior.
    \brief Multivariate normal distribution Bayesian estimator
  */
template <size_t M> class EstimatorBayes<NormalDistribution<M>, M> :
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs estimator with hyperparameters prior
  EstimatorBayes(const Eigen::Matrix<double, M, 1>& mu =
    Eigen::Matrix<double, M, 1>::Zero(), double kappa = 1.0, double nu =
    M + 1.0, const Eigen::Matrix<double, M, M>& sigma =
    Eigen::Matrix<double, M, M>::Identity());
  /// Copy constructor
  EstimatorBayes(const EstimatorBayes<NormalDistribution<M>, M>& other);
  /// Assignment operator
  EstimatorBayes<NormalDistribution<M>, M>& operator =
    (const EstimatorBayes<NormalDistribution<M>, M>& other);
  /// Destructor
  virtual ~EstimatorBayes();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the posterior marginal mean distribution
  const StudentDistribution<M>& getPostMeanDist() const;
  /// Returns the posterior marginal covariance distribution
  const InvWishartDistribution<M>& getPostCovarianceDist() const;
  /// Returns the posterior predictive distribution
  const StudentDistribution<M>& getPostPredDist() const;
  /// Add a point to the estimator
  void addPoint(const Eigen::Matrix<double, M, 1>& point);
  /// Add points to the estimator
  void addPoints(const std::vector<Eigen::Matrix<double, M, 1> >& points);
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
  /// Posterior marginal mean distribution
  StudentDistribution<M> mPostMeanDist;
  /// Posterior marginal covariance distribution
  InvWishartDistribution<M> mPostCovarianceDist;
  /// Posterior predictive distribution
  StudentDistribution<M> mPostPredDist;
  /// Hyperparameter mu (location of the mean)
  Eigen::Matrix<double, M, 1> mMu;
  /// Hyperparameter kappa (scale of the mean: mSigma/mKappa)
  double mKappa;
  /// Hyperparameter nu (degrees of freedom of the variance)
  double mNu;
  /// Hyperparameter sigma (scale of the variance)
  Eigen::Matrix<double, M, M> mSigma;
  /** @}
    */

};

#include "statistics/EstimatorBayesNormalMv.tpp"
