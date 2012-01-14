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

/** \file EstimatorBayesImproperLinearRegression.h
    \brief This file implements a Bayesian estimator for ordinary linear
           regression models with improper prior.
  */

#include "statistics/LinearRegression.h"
#include "statistics/LinearRegressionPred.h"
#include "statistics/ScaledInvChiSquareDistribution.h"

#include <vector>

/** The class EstimatorBayesImproper is implemented for ordinary linear
    regression models.
    \brief Ordinary linear regresssion Bayesian estimator with improper prior
  */
template <size_t M> class EstimatorBayesImproper<LinearRegression<M>, M> :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /// Point type
  typedef Eigen::Matrix<double, M, 1> Point;
  /// Points container
  typedef std::vector<Point> Container;
  /// Constant point iterator
  typedef typename Container::const_iterator ConstPointIterator;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  EstimatorBayesImproper();
  /// Copy constructor
  EstimatorBayesImproper(const EstimatorBayesImproper<LinearRegression<M>, M>&
    other);
  /// Assignment operator
  EstimatorBayesImproper<LinearRegression<M>, M>& operator =
    (const EstimatorBayesImproper<LinearRegression<M>, M>& other);
  /// Destructor
  virtual ~EstimatorBayesImproper();
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
  /// Returns the sample coefficients
  const Eigen::Matrix<double, M, 1>& getSampleCoeff() const;
  /// Returns the sample coefficients covariance
  const Eigen::Matrix<double, M, M>& getSampleCoeffCovariance() const;
  /// Returns the sample regression variance
  double getSampleRegressionVariance() const;
  /// Returns the number of points
  size_t getNumPoints() const;
  /// Returns the validity state of the estimator
  bool getValid() const;
  /// Add points to the estimator
  void addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd);
  /// Add points to the estimator with weights
  void addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd, const Eigen::Matrix<double, Eigen::Dynamic, 1>& weights);
  /// Reset the estimator
  void reset();
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
  /// Sample coefficients
  Eigen::Matrix<double, M, 1> mSampleCoeff;
  /// Sample coefficients covariance
  Eigen::Matrix<double, M, M> mSampleCoeffCovariance;
  /// Sample regression variance
  double mSampleRegressionVariance;
  /// Number of points in the estimator
  size_t mNumPoints;
  /// Valid flag
  bool mValid;
  /** @}
    */

};

#include "statistics/EstimatorBayesImproperLinearRegression.tpp"
