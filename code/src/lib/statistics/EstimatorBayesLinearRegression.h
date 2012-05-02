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

#include <vector>

#include "statistics/LinearRegression.h"
#include "statistics/LinearRegressionPred.h"
#include "statistics/NormalScaledInvChiSquareDistribution.h"

/** The class EstimatorBayes is implemented for ordinary linear regression
    models.
    \brief Ordinary linear regresssion Bayesian estimator with conjugate prior
  */
template <size_t M> class EstimatorBayes<LinearRegression<M>,
  NormalScaledInvChiSquareDistribution<M> > :
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
  EstimatorBayes(const NormalScaledInvChiSquareDistribution<M>& prior =
    NormalScaledInvChiSquareDistribution<M>());
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
  /// Returns the coefficients and variance distribution
  const NormalScaledInvChiSquareDistribution<M>& getDist() const;
  /// Returns the predictive distribution
  LinearRegressionPred<M> getPredDist() const;
  /// Add point to the estimator
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
  /// Coefficients and variance distribution
  NormalScaledInvChiSquareDistribution<M> mCoeffVarianceDist;
  /** @}
    */

};

#include "statistics/EstimatorBayesLinearRegression.tpp"
