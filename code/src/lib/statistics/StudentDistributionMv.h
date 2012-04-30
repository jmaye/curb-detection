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

/** \file StudentDistributionMv.h
    \brief This file defines the StudentDistributionMv class, which represents a
           multivariate Student's t-distribution
  */

#include <Eigen/Cholesky>

#include "statistics/ContinuousDistribution.h"
#include "statistics/SampleDistribution.h"
#include "base/Serializable.h"
#include "exceptions/BadArgumentException.h"
#include "exceptions/InvalidOperationException.h"

/** The StudentDistributionMv class represents a multivariate Student's
    t-distribution, i.e., a predictive distribution for a normal with unknown
    mean and covariance matrix.
    \brief Multivariate Student's t-distribution
  */
template <size_t M> class StudentDistribution :
  public ContinuousDistribution<double, M>,
  public SampleDistribution<Eigen::Matrix<double, M, 1> >,
  public virtual Serializable {
public:
  /** \name Types
    @{
    */
  /// Distribution type
  typedef ContinuousDistribution<double, M> DistributionType;
  /// Random variable type
  typedef typename DistributionType::RandomVariable RandomVariable;
  /// Mean type
  typedef typename DistributionType::Mean Mean;
  /// Mode type
  typedef typename DistributionType::Mode Mode;
  /// Covariance type
  typedef typename DistributionType::Covariance Covariance;
  /// Location type
  typedef Mean Location;
  /// Scale type
  typedef Covariance Scale;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs the distribution from the parameters
  StudentDistribution(double degrees = 1.0, const Location& location =
    Location::Zero(), const Scale& scale = Scale::Identity());
  /// Copy constructor
  StudentDistribution(const StudentDistribution& other);
  /// Assignment operator
  StudentDistribution& operator = (const StudentDistribution& other);
  /// Destructor
  virtual ~StudentDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the location of the distribution
  void setLocation(const Location& scale);
  /// Returns the location of the distribution
  const Location& getLocation() const;
  /// Sets the scale matrix of the distribution
  void setScale(const Scale& scale) throw (BadArgumentException<Scale>);
  /// Returns the scale matrix of the distribution
  const Scale& getScale() const;
  /// Sets the degrees of freedom of the distribution
  void setDegrees(double degrees) throw (BadArgumentException<double>);
  /// Returns the degrees of freedom of the distribution
  double getDegrees() const;
  /// Returns the inverse scale matrix of the distribution
  const Scale& getInverseScale() const;
  /// Returns the determinant of the scale matrix
  double getDeterminant() const;
  /// Returns the normalizer of the distribution
  double getNormalizer() const;
  /// Returns the cholesky decomposition of the scale matrix
  const Eigen::LLT<Scale>& getTransformation() const;
  /// Returns the mean of the distribution
  Mean getMean() const throw (InvalidOperationException);
  /// Returns the mode of the distribution
  Mode getMode() const;
  /// Returns the covariance of the distribution
  Covariance getCovariance() const throw (InvalidOperationException);
  /// Access the probability density function at the given value
  virtual double pdf(const RandomVariable& value) const;
  /// Access the log-probability density function at the given value
  double logpdf(const RandomVariable& value) const;
  /// Access a sample drawn from the distribution
  virtual RandomVariable getSample() const;
  /// Returns the squared Mahalanobis distance from a point
  double mahalanobisDistance(const RandomVariable& value) const;
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Compute normalizer
  void computeNormalizer();
  /** @}
    */

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
  /// Location of the distribution
  Location mLocation;
  /// Scale of the distribution
  Scale mScale;
  /// Degrees of freedom of the distribution
  double mDegrees;
  /// Inverse scale of the distribution
  Scale mInverseScale;
  /// Determinant of the scale matrix
  double mDeterminant;
  /// Normalizer of the distribution
  double mNormalizer;
  /// Cholesky decomposition of the scale matrix
  Eigen::LLT<Scale> mTransformation;
  /** @}
    */

};

#include "statistics/StudentDistributionMv.tpp"
