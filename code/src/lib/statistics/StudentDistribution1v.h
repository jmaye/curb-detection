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

/** \file StudentDistribution1v.h
    \brief This file defines the univariate Student's t-distribution
  */

#include "statistics/ContinuousDistribution.h"
#include "statistics/SampleDistribution.h"
#include "base/Serializable.h"

/** The StudentDistribution1v class represents a univariate Student's
    t-distribution, i.e., a predictive distribution for a normal with unknown
    mean and variance.
    \brief Univariate Student's t-distribution
  */
template <> class StudentDistribution<1> :
  public ContinuousDistribution<double>,
  public SampleDistribution<double>,
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the distribution from the parameters
  inline StudentDistribution(double degrees = 1.0, double location = 0.0, double
    scale = 1.0);
  /// Copy constructor
  inline StudentDistribution(const StudentDistribution& other);
  /// Assignment operator
  inline StudentDistribution& operator = (const StudentDistribution& other);
  /// Destructor
  inline virtual ~StudentDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the location of the distribution
  inline void setLocation(double scale);
  /// Returns the location of the distribution
  inline double getLocation() const;
  /// Sets the scale of the distribution (already squared)
  inline void setScale(double scale);
  /// Returns the scale of the distribution
  inline double getScale() const;
  /// Sets the degrees of freedom of the distribution
  inline void setDegrees(double degrees);
  /// Returns the degrees of freedom of the distribution
  inline double getDegrees() const;
  /// Returns the inverse scale of the distribution
  inline double getInverseScale() const;
  /// Returns the normalizer of the distribution
  inline double getNormalizer() const;
  /// Returns the mean of the distribution
  inline Mean getMean() const;
  /// Returns the median of the distribution
  inline Median getMedian() const;
  /// Returns the mode of the distribution
  inline Mode getMode() const;
  /// Returns the variance of the distribution
  inline Variance getVariance() const;
  /// Access the probability density function at the given value
  inline virtual double pdf(const RandomVariable& value) const;
  /// Access the log-probability density function at the given value
  inline double logpdf(const RandomVariable& value) const;
  /// Access the cumulative density function at the given value
  inline double cdf(const RandomVariable& value) const;
  /// Access a sample drawn from the distribution
  inline virtual RandomVariable getSample() const;
  /// Returns the squared Mahalanobis distance from a given value
  inline double mahalanobisDistance(const RandomVariable& value) const;
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Computes the normalizer
  inline void computeNormalizer();
  /** @}
    */

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
  /// Location of the distribution
  double mLocation;
  /// Scale of the distribution
  double mScale;
  /// Degrees of freedom of the distribution
  double mDegrees;
  /// Inverse scale of the distribution
  double mInverseScale;
  /// Normalizer of the distribution
  double mNormalizer;
  /** @}
    */

};

#include "statistics/StudentDistribution1v.tpp"
