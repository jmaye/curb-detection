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

/** \file EstimatorBayesImproperNormalMv.h
    \brief This file implements a Bayesian estimator for multivariate normal
           distributions with improper prior.
  */

#include "statistics/NormalDistribution.h"
#include "statistics/StudentDistribution.h"
#include "statistics/InvWishartDistribution.h"

#include <vector>

/** The class EstimatorBayesImproper is implemented for multivariate normal
    distributions.
    \brief Multivariate normal distribution Bayesian estimator with improper
           prior
  */
template <size_t M> class EstimatorBayesImproper<NormalDistribution<M>, M> :
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
  EstimatorBayesImproper(const EstimatorBayesImproper<NormalDistribution<M>, M>&
    other);
  /// Assignment operator
  EstimatorBayesImproper<NormalDistribution<M>, M>& operator =
    (const EstimatorBayesImproper<NormalDistribution<M>, M>& other);
  /// Destructor
  virtual ~EstimatorBayesImproper();
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
  /// Returns the sample mean
  const Eigen::Matrix<double, M, 1>& getSampleMean() const;
  /// Returns the sample covariance
  const Eigen::Matrix<double, M, M>& getSampleCovariance() const;
  /// Returns the number of points
  size_t getNumPoints() const;
  /// Returns the validity state of the estimator
  bool getValid() const;
  /// Add a point to the estimator
  void addPoint(const Point& point);
  /// Add points to the estimator
  void addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd);
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
  /// Posterior marginal mean distribution
  StudentDistribution<M> mPostMeanDist;
  /// Posterior marginal covariance distribution
  InvWishartDistribution<M> mPostCovarianceDist;
  /// Posterior predictive distribution
  StudentDistribution<M> mPostPredDist;
  /// Sample mean
  Eigen::Matrix<double, M, 1> mSampleMean;
  /// Sample covariance
  Eigen::Matrix<double, M, M> mSampleCovariance;
  /// Number of points in the estimator
  size_t mNumPoints;
  /// Valid flag
  bool mValid;
  /// Sum of the values
  Eigen::Matrix<double, M, 1> mValuesSum;
  /// Squared sum of the values
  Eigen::Matrix<double, M, M> mSquaredValuesSum;
  /** @}
    */

};

#include "statistics/EstimatorBayesImproperNormalMv.tpp"
