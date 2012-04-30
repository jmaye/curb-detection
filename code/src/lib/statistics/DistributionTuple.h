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

/** \file DistributionTuple.h
    \brief This file contains an interface to tuple distributions.
  */

#ifndef DISTRIBUTIONTUPLE_H
#define DISTRIBUTIONTUPLE_H

#include <tuple>

#include "statistics/Distribution.h"

/** The DistributionTuple class represents an interface to tuple distributions.
    \brief Tuple distribution
  */
template <typename... X> class DistributionTuple :
  public virtual Distribution<std::tuple<X...> > {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  DistributionTuple(const DistributionTuple& other);
  /// Assignment operator
  DistributionTuple& operator = (const DistributionTuple& other);
  /** @}
    */

public:
  /** \name Types
    @{
    */
  /// Random variable type
  typedef std::tuple<X...> RandomVariable;
  /// Mode type
  typedef RandomVariable Mode;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  DistributionTuple();
  /// Destructor
  virtual ~DistributionTuple();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Access the probablity density function at the given value
  virtual double pdf(const RandomVariable& value) const = 0;
  /// Interface to function
  virtual double getValue(const std::tuple<X...>& argument) const;
  /** @}
    */

protected:

};

#include "statistics/DistributionTuple.tpp"

#endif // DISTRIBUTIONTUPLE_H
