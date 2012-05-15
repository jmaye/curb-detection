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
    \brief This file implements a batch ML estimator for mixture of linear
           regressions with BP in the E-step.
  */

#ifndef ESTIMATORMLBP_H
#define ESTIMATORMLBP_H

#include <vector>

#include "statistics/MixtureDistribution.h"
#include "statistics/LinearRegression.h"
#include "data-structures/Grid.h"
#include "data-structures/Cell.h"
#include "data-structures/DEMGraph.h"
#include "data-structures/FactorGraph.h"

template <typename D> class EstimatorMLBP;

/** The class EstimatorMLBP is implemented for mixture of linear regressions.
    \brief Mixture distributions ML estimator with BP
  */
template <size_t N, size_t M>
  class EstimatorMLBP<MixtureDistribution<LinearRegression<N>, M> > :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /// Point type
  typedef typename LinearRegression<N>::RandomVariable Point;
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
  EstimatorMLBP(const MixtureDistribution<LinearRegression<N>, M>& initDist,
    const Grid<double, Cell, 2>& dem, const DEMGraph& graph,
    std::vector<DEMGraph::VertexDescriptor>& pointsMapping,
    size_t maxNumIter = 200, double tol = 1e-6);
  /// Copy constructor
  EstimatorMLBP(const EstimatorMLBP& other);
  /// Assignment operator
  EstimatorMLBP& operator = (const EstimatorMLBP& other);
  /// Destructor
  virtual ~EstimatorMLBP();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the estimated mixture distribution
  const MixtureDistribution<LinearRegression<N>, M>& getMixtureDist() const;
  /// Returns the number of points
  size_t getNumPoints() const;
  /// Returns the validity state of the estimator
  bool getValid() const;
  /// Returns the estimated responsibilities
  const Eigen::Matrix<double, Eigen::Dynamic, M>& getResponsibilities() const;
  /// Returns the vertices labels
  DEMGraph::VertexContainer getVerticesLabels();
  /// Returns the log-likelihood of the data
  double getLogLikelihood() const;
  /// Returns the tolerance of the estimator
  double getTolerance() const;
  /// Sets the tolerance of the estimator
  void setTolerance(double tol);
  /// Returns the maximum number of iterations for EM
  size_t getMaxNumIter() const;
  /// Sets the maximum number of iterations for EM
  void setMaxNumIter(size_t maxNumIter);
  /// Add points to the estimator / Returns number of EM iterationss
  size_t addPointsEM(const ConstPointIterator& itStart, const
    ConstPointIterator& itEnd);
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
  /// Estimated distribution
  MixtureDistribution<LinearRegression<N>, M>  mMixtureDist;
  /// DEM
  Grid<double, Cell, 2> mDEM;
  /// DEM graph
  DEMGraph mGraph;
  /// Points mapping
  std::vector<DEMGraph::VertexDescriptor> mPointsMapping;
  /// Factor graph
  FactorGraph mFactorGraph;
  /// Factor graph mapping
  DEMGraph::VertexContainer mFgMapping;
  /// Estimated responsibilities
  Eigen::Matrix<double, Eigen::Dynamic, M> mResponsibilities;
  /// Log-likelihood of the data
  double mLogLikelihood;
  /// Maximum number of iterations for EM
  size_t mMaxNumIter;
  /// Tolerance for the determinant
  double mTol;
  /// Number of points in the estimator
  size_t mNumPoints;
  /// Valid flag
  bool mValid;
  /** @}
    */

};

#include "statistics/EstimatorMLBPMixtureLinearRegression.tpp"

#endif // ESTIMATORMLBP_H
