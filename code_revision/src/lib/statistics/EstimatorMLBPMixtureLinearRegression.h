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

/** \file EstimatorMLBPMixtureLinearRegression.h
    \brief This file implements an ML-BP estimator for mixture of linear
           regression models
  */

#ifndef ESTIMATORMLBP_H
#define ESTIMATORMLBP_H

#include "statistics/LinearRegression.h"
#include "statistics/MixtureDistribution.h"
#include "data-structures/Grid.h"
#include "data-structures/Cell.h"
#include "data-structures/DEMGraph.h"

#include <vector>

template <typename D, size_t M = 1, size_t N = 1> class EstimatorMLBP;

/** The class EstimatorMLBP is implemented for mixtures of linear regressions.
    \brief Mixture of linear regression ML estimator with BP
  */
template <size_t M, size_t N>
class EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N> :
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
  /// Constructs estimator with initial guess of the parameters
  EstimatorMLBP(const Eigen::Matrix<double, N, M>& coefficients, const
    Eigen::Matrix<double, N, 1>& variances, const Eigen::Matrix<double, N, 1>&
    weights, size_t maxNumIterEM = 200, double tolEM = 1e-6, size_t
    maxNumIterBP = 200, double tolBP = 1e-6);
  /// Copy constructor
  EstimatorMLBP(const
    EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>& other);
  /// Assignment operator
  EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>& operator =
    (const EstimatorMLBP<MixtureDistribution<LinearRegression<M>, N>, M, N>&
    other);
  /// Destructor
  virtual ~EstimatorMLBP();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the number of points
  size_t getNumPoints() const;
  /// Returns the validity state of the estimator
  bool getValid() const;
  /// Returns the estimated coefficients
  const Eigen::Matrix<double, N, M>& getCoefficients() const;
  /// Returns the estimated variances
  const Eigen::Matrix<double, N, 1>& getVariances() const;
  /// Returns the estimated responsibilities
  const Eigen::Matrix<double, Eigen::Dynamic, N>& getResponsibilities() const;
  /// Returns the estimated component weights
  const Eigen::Matrix<double, N, 1>& getWeights() const;
  /// Returns the log-likelihood of the data
  double getLogLikelihood() const;
  /// Returns the tolerance of the estimator
  double getToleranceEM() const;
  /// Sets the tolerance of the estimator
  void setToleranceEM(double tol);
  /// Returns the maximum number of iterations for EM
  size_t getMaxNumIterEM() const;
  /// Sets the maximum number of iterations for EM
  void setMaxNumIterEM(size_t maxNumIter);
  /// Returns the tolerance of BP
  double getToleranceBP() const;
  /// Sets the tolerance of BP
  void setToleranceBP(double tol);
  /// Returns the maximum number of iterations for BP
  size_t getMaxNumIterBP() const;
  /// Sets the maximum number of iterations for BP
  void setMaxNumIterBP(size_t maxNumIter);
  /// Returns the MAP state
  const std::vector<size_t>& getMAPState() const;
  /// Returns the Factor graph mapping
  const DEMGraph::VertexContainer& getFgMapping() const;
  /// Add points to the estimator / Returns number of EM iterationss
  size_t addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd, const Grid<double, Cell, 2>& dem, const DEMGraph& graph,
    const std::vector<DEMGraph::VertexDescriptor>& pointsMapping);
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
  /// Estimated regression coefficients
  Eigen::Matrix<double, N, M> mCoefficients;
  /// Estimated variances
  Eigen::Matrix<double, N, 1> mVariances;
  /// Estimated responsibilities
  Eigen::Matrix<double, Eigen::Dynamic, N> mResponsibilities;
  /// Estimated component weights
  Eigen::Matrix<double, N, 1> mWeights;
  /// Log-likelihood of the data
  double mLogLikelihood;
  /// Maximum number of iterations for EM
  size_t mMaxNumIterEM;
  /// Tolerance for the EM convergence
  double mTolEM;
  /// Maximum number of iterations for BP
  size_t mMaxNumIterBP;
  /// Tolerance for the BP convergence
  double mTolBP;
  /// Number of points in the estimator
  size_t mNumPoints;
  /// Valid flag
  bool mValid;
  /// FG mapping
  DEMGraph::VertexContainer mFgMapping;
  /// MAP state
  std::vector<size_t> mMapState;
  /** @}
    */

};

#include "statistics/EstimatorMLBPMixtureLinearRegression.tpp"

#endif // ESTIMATORMLBP_H
