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

/** \file ContinuousDistribution1v.h
    \brief This file contains an interface to the univariate continuous
           distributions
  */

#include "functions/ContinuousFunction.h"
#include "statistics/Distribution.h"

/** The ContinuousDistribution1v class represents an interface to the univariate
    continuous distributions.
    \brief Univariate continuous distribution
  */
template <typename X> class ContinuousDistribution<X> :
  public ContinuousFunction<double, X>,
  public virtual Distribution<X> {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  ContinuousDistribution(const ContinuousDistribution& other);
  /// Assignment operator
  ContinuousDistribution& operator = (const ContinuousDistribution& other);
  /** @}
    */

public:
  /** \name Types
    @{
    */
  /// Distribution type
  typedef ContinuousDistribution<X> DistributionType;
  /// Random variable type
  typedef X RandomVariable;
  /// Mean type
  typedef double Mean;
  /// Variance type
  typedef double Variance;
  /// Mode type
  typedef X Mode;
  /// Median type
  typedef double Median;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  ContinuousDistribution();
  /// Destructor
  virtual ~ContinuousDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Access the probablity density function at the given value
  virtual double pdf(const RandomVariable& value) const = 0;
  /// Interface to function
  virtual double getValue(const X& argument) const;
  /** @}
    */

protected:

};

#include "statistics/ContinuousDistribution1v.tpp"
