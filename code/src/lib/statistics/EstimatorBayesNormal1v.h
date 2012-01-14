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

#include "statistics/NormalDistribution.h"
#include "statistics/StudentDistribution.h"
#include "statistics/ScaledInvChiSquareDistribution.h"

#include <vector>

/** The class EstimatorBayes is implemented for univariate normal
    distributions with conjugate prior.
    \brief Univariate normal distribution Bayesian estimator
  */
template <> class EstimatorBayes<NormalDistribution<1> > :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /// Point type
  typedef double Point;
  /// Points container
  typedef std::vector<Point> Container;
  /// Constant point iterator
  typedef Container::const_iterator ConstPointIterator;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs estimator with hyperparameters prior
  inline EstimatorBayes(double mu = 0.0, double kappa = 1.0, double nu = 1.0,
    double sigma = 1.0);
  /// Copy constructor
  inline EstimatorBayes(const EstimatorBayes<NormalDistribution<1> >& other);
  /// Assignment operator
  inline EstimatorBayes<NormalDistribution<1> >& operator =
    (const EstimatorBayes<NormalDistribution<1> >& other);
  /// Destructor
  inline virtual ~EstimatorBayes();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the posterior marginal mean distribution
  inline const StudentDistribution<1>& getPostMeanDist() const;
  /// Returns the posterior marginal variance distribution
  inline const ScaledInvChiSquareDistribution& getPostVarianceDist() const;
  /// Returns the posterior predictive distribution
  inline const StudentDistribution<1>& getPostPredDist() const;
  /// Add a point to the estimator
  inline void addPoint(const Point& point);
  /// Add points to the estimator
  inline void addPoints(const ConstPointIterator& itStart, const
    ConstPointIterator& itEnd);
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
  /// Posterior marginal mean distribution
  StudentDistribution<1> mPostMeanDist;
  /// Posterior marginal variance distribution
  ScaledInvChiSquareDistribution mPostVarianceDist;
  /// Posterior predictive distribution
  StudentDistribution<1> mPostPredDist;
  /// Hyperparameter mu (location of the mean)
  double mMu;
  /// Hyperparameter kappa (scale of the mean: mSigma/mKappa)
  double mKappa;
  /// Hyperparameter nu (degrees of freedom of the variance)
  double mNu;
  /// Hyperparameter sigma (scale of the variance)
  double mSigma;
  /** @}
    */

};

#include "statistics/EstimatorBayesNormal1v.tpp"
