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

#include <vector>

#include "statistics/NormalDistribution.h"
#include "statistics/StudentDistribution.h"
#include "statistics/InvWishartDistribution.h"
#include "statistics/NormalInvWishartDistribution.h"

/** The class EstimatorBayes is implemented for multivariate normal
    distributions with conjugate prior for the mean
    \brief Multivariate normal distribution Bayesian estimator for the mean
  */
template <size_t M>
class EstimatorBayes<NormalDistribution<M>, NormalDistribution<M> > :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /// Point type
  typedef typename NormalDistribution<M>::RandomVariable Point;
  /// Points container
  typedef std::vector<Point> Container;
  /// Constant point iterator
  typedef typename Container::const_iterator ConstPointIterator;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs estimator with prior
  EstimatorBayes(const Eigen::Matrix<double, M, M>& covariance =
    Eigen::Matrix<double, M, M>::Identity(), const NormalDistribution<M>&
    prior = NormalDistribution<M>());
  /// Copy constructor
  EstimatorBayes(const EstimatorBayes& other);
  /// Assignment operator
  EstimatorBayes& operator = (const EstimatorBayes& other);
  /// Destructor
  virtual ~EstimatorBayes();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the mean distribution
  const NormalDistribution<M>& getDist() const;
  /// Returns the predictive distribution
  NormalDistribution<M> getPredDist() const;
  /// Add a point to the estimator
  void addPoint(const Point& point);
  /// Add points to the estimator
  void addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd);
  /// Add points to the estimator
  void addPoints(const Container& points);
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
  /// Mean distribution
  NormalDistribution<M> mMeanDist;
  /// Covariance
  Eigen::Matrix<double, M, M> mCovariance;
  /// Precision
  Eigen::Matrix<double, M, M> mPrecision;
  /** @}
    */

};

/** The class EstimatorBayes is implemented for multivariate normal
    distributions with conjugate prior for the covariance
    \brief Multivariate normal distribution Bayesian estimator for the
           covariance
  */
template <size_t M>
class EstimatorBayes<NormalDistribution<M>, InvWishartDistribution<M> > :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /// Point type
  typedef typename NormalDistribution<M>::RandomVariable Point;
  /// Points container
  typedef std::vector<Point> Container;
  /// Constant point iterator
  typedef typename Container::const_iterator ConstPointIterator;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs estimator with prior
  EstimatorBayes(const Eigen::Matrix<double, M, 1>& mean =
    Eigen::Matrix<double, M, M>::Zero(), const
    InvWishartDistribution<M>& prior = InvWishartDistribution<M>());
  /// Copy constructor
  EstimatorBayes(const EstimatorBayes& other);
  /// Assignment operator
  EstimatorBayes& operator = (const EstimatorBayes& other);
  /// Destructor
  virtual ~EstimatorBayes();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the covariance distribution
  const InvWishartDistribution<M>& getDist() const;
  /// Add a point to the estimator
  void addPoint(const Point& point);
  /// Add points to the estimator
  void addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd);
  /// Add points to the estimator
  void addPoints(const Container& points);
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
  /// Covariance distribution
  InvWishartDistribution<M> mCovarianceDist;
  /// Mean
  Eigen::Matrix<double, M, 1> mMean;
  /** @}
    */

};

/** The class EstimatorBayes is implemented for multivariate normal
    distributions with conjugate prior for the mean and covariance
    \brief Multivariate normal distribution Bayesian estimator for the mean and
           covariance
  */
template <size_t M>
class EstimatorBayes<NormalDistribution<M>, NormalInvWishartDistribution<M> > :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /// Point type
  typedef typename NormalDistribution<M>::RandomVariable Point;
  /// Points container
  typedef std::vector<Point> Container;
  /// Constant point iterator
  typedef typename Container::const_iterator ConstPointIterator;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs estimator with prior
  EstimatorBayes(const NormalInvWishartDistribution<M>& prior =
    NormalInvWishartDistribution<M>());
  /// Copy constructor
  EstimatorBayes(const EstimatorBayes& other);
  /// Assignment operator
  EstimatorBayes& operator = (const EstimatorBayes& other);
  /// Destructor
  virtual ~EstimatorBayes();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the mean and covariance distribution
  const NormalInvWishartDistribution<M>& getDist() const;
  /// Returns the predictive distribution
  StudentDistribution<M> getPredDist() const;
  /// Add a point to the estimator
  void addPoint(const Point& point);
  /// Add points to the estimator
  void addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd);
  /// Add points to the estimator
  void addPoints(const Container& points);
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
  /// Mean and covariance distribution
  NormalInvWishartDistribution<M> mMeanCovarianceDist;
  /** @}
    */

};

#include "statistics/EstimatorBayesNormalMv.tpp"
