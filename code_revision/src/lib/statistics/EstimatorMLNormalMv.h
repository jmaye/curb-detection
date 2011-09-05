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

/** \file EstimatorMLNormalMv.h
    \brief This file implements an ML estimator for multivariate normal
           distributions.
  */

#include "statistics/NormalDistribution.h"
#include "base/Serializable.h"

#include <vector>

/** The class EstimatorML is implemented for multivariate normal distributions.
    \brief Multivariate normal distribution ML estimator
  */
template <size_t M> class EstimatorML<NormalDistribution<M>, M> :
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  EstimatorML();
  /// Copy constructor
  EstimatorML(const EstimatorML<NormalDistribution<M>, M>& other);
  /// Assignment operator
  EstimatorML<NormalDistribution<M>, M>& operator =
    (const EstimatorML<NormalDistribution<M>, M>& other);
  /// Destructor
  virtual ~EstimatorML();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the number of points
  size_t getNumPoints() const;
  /// Returns the validity state of the estimator
  bool getValid() const;
  /// Returns the estimated mean
  const Eigen::Matrix<double, M, 1>& getMean() const;
  /// Returns the estimated covariance
  const Eigen::Matrix<double, M, M>& getCovariance() const;
  /// Add a point to the estimator
  void addPoint(const Eigen::Matrix<double, M, 1>& point);
  /// Add points to the estimator
  void addPoints(const std::vector<Eigen::Matrix<double, M, 1> >& points);
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
  /// Estimated mean
  Eigen::Matrix<double, M, 1> mMean;
  /// Estimated covariance
  Eigen::Matrix<double, M, M> mCovariance;
  /// Number of points in the estimator
  size_t mNumPoints;
  /// Valid flag
  bool mValid;
  /** @}
    */

};

#include "statistics/EstimatorMLNormalMv.tpp"
