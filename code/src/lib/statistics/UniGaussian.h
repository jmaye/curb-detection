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

/** \file UniGaussian.h
    \brief This file defines the UniGaussian class, which represents a
           univariate Gaussian distribution
  */

#ifndef UNIGAUSSIAN_H
#define UNIGAUSSIAN_H

#include "exceptions/OutOfBoundException.h"

#include <iosfwd>
#include <stdint.h>

/** The class UniGaussian represents univariate Gaussian distribution
    \brief Univariate Gaussian distribution
  */
class UniGaussian {
  friend std::ostream& operator << (std::ostream& stream,
    const UniGaussian& obj);
  friend std::istream& operator >> (std::istream& stream, UniGaussian& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const UniGaussian& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, UniGaussian& obj);

  /** \name Streaming methods
    @{
    */
  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Private members
    @{
    */
  /// Mean of the Gaussian
  double mf64Mean;
  /// Variance of the Gaussian
  double mf64Variance;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs Gaussian from mean and variance
  UniGaussian(double f64Mean, double f64Variance) throw (OutOfBoundException);
  /// Copy constructor
  UniGaussian(const UniGaussian& other);
  /// Assignment operator
  UniGaussian& operator = (const UniGaussian& other);
  /// Destructor
  ~UniGaussian();
  /** @}
    */

  /** \name Accessors
      @{
    */
  /// Returns mean of the Gaussian
  double getMean() const;
  /// Returns variance of the Gaussian
  double getVariance() const;
  /// Sets the mean of the Gaussian
  void setMean(double f64Mean);
  /// Sets the variance of the Gaussian
  void setVariance(double f64Variance) throw (OutOfBoundException);
  /** @}
    */

  /** \name Methods
      @{
    */
  /// Returns probability density at a point
  double pdf(double f64X) const;
  /// Returns log-probability density at a point
  double logpdf(double f64X) const;
  /// Returns KL-divergence with another distribution
  double KLDivergence(const UniGaussian& other) const;
  /** @}
    */

protected:

};

#endif // UNIGAUSSIAN_H
