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
           multivariate Student distribution
  */

#include "statistics/ContinuousDistribution.h"
#include "statistics/SampleDistribution.h"
#include "base/Serializable.h"
#include "exceptions/BadArgumentException.h"

#include <Eigen/Cholesky>

/** The StudentDistributionMv class represents a multivariate Student
    distribution.
    \brief Multivariate Student distribution
  */
template <size_t M> class StudentDistribution :
  public ContinuousDistribution<double, M>,
  public SampleDistribution<Eigen::Matrix<double, M, 1> >,
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the distribution from the parameters
  StudentDistribution(double degrees = 1.0, const Eigen::Matrix<double, M, 1>&
    location = Eigen::Matrix<double, M, 1>::Zero(), const
    Eigen::Matrix<double, M, M>& scale =
    Eigen::Matrix<double, M, M>::Identity());
  /// Copy constructor
  StudentDistribution(const StudentDistribution<M>& other);
  /// Assignment operator
  StudentDistribution<M>& operator = (const StudentDistribution<M>& other);
  /// Destructor
  virtual ~StudentDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the location of the distribution
  void setLocation(const Eigen::Matrix<double, M, 1>& scale);
  /// Returns the location of the distribution
  const Eigen::Matrix<double, M, 1>& getLocation() const;
  /// Sets the scale matrix of the distribution
  void setScale(const Eigen::Matrix<double, M, M>& scale)
    throw (BadArgumentException<Eigen::Matrix<double, M, M> >);
  /// Returns the scale matrix of the distribution
  const Eigen::Matrix<double, M, M>& getScale() const;
  /// Sets the degrees of freedom of the distribution
  void setDegrees(double degrees) throw (BadArgumentException<double>);
  /// Returns the degrees of freedom of the distribution
  double getDegrees() const;
  /// Returns the inverse scale matrix of the distribution
  const Eigen::Matrix<double, M, M>& getInverseScale() const;
  /// Returns the determinant of the scale matrix
  double getDeterminant() const;
  /// Returns the normalizer of the distribution
  double getNormalizer() const;
  /// Returns the cholesky decomposition of the scale matrix
  const Eigen::LLT<Eigen::Matrix<double, M, M> >& getTransformation() const;
  /// Returns the mean of the distribution
  Eigen::Matrix<double, M, 1> getMean() const;
  /// Returns the mode of the distribution
  Eigen::Matrix<double, M, 1> getMode() const;
  /// Returns the variance of the distribution
  Eigen::Matrix<double, M, M> getCovariance() const;
  /// Access the probability density function at the given value
  virtual double pdf(const Eigen::Matrix<double, M, 1>& value) const;
  /// Access the log-probability density function at the given value
  double logpdf(const Eigen::Matrix<double, M, 1>& value) const;
  /// Access a sample drawn from the distribution
  virtual Eigen::Matrix<double, M, 1> getSample() const;
  /// Returns the squared Mahalanobis distance from a point
  double mahalanobisDistance(const Eigen::Matrix<double, M, 1>& value) const;
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
  /// Location of the distribution
  Eigen::Matrix<double, M, 1> mLocation;
  /// Scale of the distribution
  Eigen::Matrix<double, M, M> mScale;
  /// Degrees of freedom of the distribution
  double mDegrees;
  /// Inverse scale of the distribution
  Eigen::Matrix<double, M, M> mInverseScale;
  /// Determinant of the scale matrix
  double mDeterminant;
  /// Normalizer of the distribution
  double mNormalizer;
  /// Cholesky decomposition of the scale matrix
  Eigen::LLT<Eigen::Matrix<double, M, M> > mTransformation;
  /** @}
    */

};

#include "statistics/StudentDistributionMv.tpp"
