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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file InvGammaDistribution.h
    \brief This file defines the InvGammaDistribution class, which represents
           an inverse gamma distribution
  */

#ifndef INVGAMMADISTRIBUTION_H
#define INVGAMMADISTRIBUTION_H

#include "statistics/ContinuousDistribution.h"
#include "statistics/SampleDistribution.h"
#include "base/Serializable.h"
#include "exceptions/BadArgumentException.h"
#include "exceptions/InvalidOperationException.h"

/** The InvGammaDistribution class represents an inverse gamma distribution.
    \brief Inverse gamma distribution
  */
template <typename T = double> class InvGammaDistribution :
  public ContinuousDistribution<double>,
  public SampleDistribution<double>,
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameters
  InvGammaDistribution(const T& shape = T(1), double scale = 1.0);
  /// Copy constructor
  InvGammaDistribution(const InvGammaDistribution& other);
  /// Assignment operator
  InvGammaDistribution<T>& operator = (const InvGammaDistribution& other);
  /// Destructor
  virtual ~InvGammaDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the shape parameter
  void setShape(const T& shape) throw (BadArgumentException<T>);
  /// Returns the shape parameter
  const T& getShape() const;
  /// Sets the scale parameter
  void setScale(double scale) throw (BadArgumentException<double>);
  /// Returns the scale parameter
  double getScale() const;
  /// Returns the normalizer
  double getNormalizer() const;
  /// Returns the mean of the distribution
  Mean getMean() const throw (InvalidOperationException);
  /// Returns the mode of the distribution
  Mode getMode() const;
  /// Returns the variance of the distribution
  Variance getVariance() const throw (InvalidOperationException);
  /// Access the probablity density function at the given value
  virtual double pdf(const RandomVariable& value) const;
  /// Access the log-probablity density function at the given value
  double logpdf(const RandomVariable& value) const;
  /// Access the cumulative density function at the given value
  double cdf(const RandomVariable& value) const;
  /// Access a sample drawn from the distribution
  virtual RandomVariable getSample() const;
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
  /// Shape parameter
  T mShape;
  /// Scale parameter
  double mScale;
  /// Normalizer
  double mNormalizer;
  /** @}
    */

};

#include "statistics/InvGammaDistribution.tpp"

#endif // INVGAMMADISTRIBUTION_H
