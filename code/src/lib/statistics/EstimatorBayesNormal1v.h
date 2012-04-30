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

/** \file EstimatorBayesNormal1v.h
    \brief This file implements a Bayesian estimator for univariate normal
           distributions with conjugate prior
  */

#include <vector>

#include "statistics/NormalDistribution.h"
#include "statistics/StudentDistribution.h"
#include "statistics/ScaledInvChiSquareDistribution.h"
#include "statistics/NormalScaledInvChiSquareDistribution.h"

/** The class EstimatorBayes is implemented for univariate normal
    distributions with conjugate prior for the mean
    \brief Univariate normal distribution Bayesian estimator for the mean
  */
template <>
class EstimatorBayes<NormalDistribution<1>, NormalDistribution<1> > :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /// Point type
  typedef NormalDistribution<1>::RandomVariable Point;
  /// Points container
  typedef std::vector<Point> Container;
  /// Constant point iterator
  typedef Container::const_iterator ConstPointIterator;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs estimator with prior
  inline EstimatorBayes(double variance = 1.0, const NormalDistribution<1>&
    prior = NormalDistribution<1>());
  /// Copy constructor
  inline EstimatorBayes(const EstimatorBayes& other);
  /// Assignment operator
  inline EstimatorBayes& operator = (const EstimatorBayes& other);
  /// Destructor
  inline virtual ~EstimatorBayes();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the mean distribution
  inline const NormalDistribution<1>& getDist() const;
  /// Returns the predictive distribution
  inline NormalDistribution<1> getPredDist() const;
  /// Add a point to the estimator
  inline void addPoint(const Point& point);
  /// Add points to the estimator
  inline void addPoints(const ConstPointIterator& itStart, const
    ConstPointIterator& itEnd);
  /// Add points to the estimator
  inline void addPoints(const Container& points);
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
  /// Mean distribution
  NormalDistribution<1> mMeanDist;
  /// Variance
  double mVariance;
  /// Precision
  double mPrecision;
  /** @}
    */

};

/** The class EstimatorBayes is implemented for univariate normal
    distributions with conjugate prior for the variance
    \brief Univariate normal distribution Bayesian estimator for the variance
  */
template <>
class EstimatorBayes<NormalDistribution<1>, ScaledInvChiSquareDistribution> :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /// Point type
  typedef NormalDistribution<1>::RandomVariable Point;
  /// Points container
  typedef std::vector<Point> Container;
  /// Constant point iterator
  typedef Container::const_iterator ConstPointIterator;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs estimator with prior
  inline EstimatorBayes(double mean = 0.0, const
    ScaledInvChiSquareDistribution& prior = ScaledInvChiSquareDistribution());
  /// Copy constructor
  inline EstimatorBayes(const EstimatorBayes& other);
  /// Assignment operator
  inline EstimatorBayes& operator = (const EstimatorBayes& other);
  /// Destructor
  inline virtual ~EstimatorBayes();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the variance distribution
  inline const ScaledInvChiSquareDistribution& getDist() const;
  /// Add a point to the estimator
  inline void addPoint(const Point& point);
  /// Add points to the estimator
  inline void addPoints(const ConstPointIterator& itStart, const
    ConstPointIterator& itEnd);
  /// Add points to the estimator
  inline void addPoints(const Container& points);
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
  /// Variance distribution
  ScaledInvChiSquareDistribution mVarianceDist;
  /// Mean
  double mMean;
  /** @}
    */

};

/** The class EstimatorBayes is implemented for univariate normal
    distributions with conjugate prior for the mean and variance
    \brief Univariate normal distribution Bayesian estimator for the mean and
           variance
  */
template <>
class EstimatorBayes<NormalDistribution<1>,
  NormalScaledInvChiSquareDistribution> :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /// Point type
  typedef NormalDistribution<1>::RandomVariable Point;
  /// Points container
  typedef std::vector<Point> Container;
  /// Constant point iterator
  typedef Container::const_iterator ConstPointIterator;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs estimator with prior
  inline EstimatorBayes(const NormalScaledInvChiSquareDistribution& prior =
    NormalScaledInvChiSquareDistribution());
  /// Copy constructor
  inline EstimatorBayes(const EstimatorBayes& other);
  /// Assignment operator
  inline EstimatorBayes& operator = (const EstimatorBayes& other);
  /// Destructor
  inline virtual ~EstimatorBayes();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the mean and variance distribution
  inline const NormalScaledInvChiSquareDistribution& getDist() const;
  /// Returns the predictive distribution
  inline StudentDistribution<1> getPredDist() const;
  /// Add a point to the estimator
  inline void addPoint(const Point& point);
  /// Add points to the estimator
  inline void addPoints(const ConstPointIterator& itStart, const
    ConstPointIterator& itEnd);
  /// Add points to the estimator
  inline void addPoints(const Container& points);
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
  /// Mean and variance distribution
  NormalScaledInvChiSquareDistribution mMeanVarianceDist;
  /** @}
    */

};

#include "statistics/EstimatorBayesNormal1v.tpp"
