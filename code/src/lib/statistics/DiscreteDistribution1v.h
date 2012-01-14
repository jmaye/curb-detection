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

/** \file DiscreteDistribution1v.h
    \brief This file contains an interface to the univariate discrete
           distributions
  */

#include "functions/DiscreteFunction.h"
#include "statistics/Distribution.h"

/** The DiscreteDistribution1v class represents an interface to the univariate
    discrete distributions.
    \brief Univariate discrete distribution
  */
template <typename X> class DiscreteDistribution<X> :
  public DiscreteFunction<double, X>,
  public virtual Distribution<X> {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  DiscreteDistribution(const DiscreteDistribution<X>& other);
  /// Assignment operator
  DiscreteDistribution& operator = (const DiscreteDistribution<X>& other);
  /** @}
    */

public:
  /** \name Types
    @{
    */
  /// Distribution type
  typedef DiscreteDistribution<X> DistributionType;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  DiscreteDistribution();
  /// Destructor
  virtual ~DiscreteDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Access the probablity of the variable to take on the given value
  virtual double pmf(const X& value) const = 0;
  /// Interface to function
  virtual double getValue(const X& argument) const;
  /** @}
    */

protected:

};

#include "statistics/DiscreteDistribution1v.tpp"
