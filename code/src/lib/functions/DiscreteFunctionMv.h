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

/** \file DiscreteFunctionMv.h
    \brief This file defines the class DiscreteFunctionMv, which is an interface
           to the multivariate discrete functions
  */

#include <Eigen/Core>

#include "functions/Function.h"
#include "utils/SizeTSupport.h"
#include "utils/SsizeTSupport.h"

/** The DiscreteFunctionMv class is an interface to the multivariate discrete
    functions.
    \brief Multivariate discrete function
  */
template <typename Y, typename X, size_t M, size_t N> class DiscreteFunction :
  public virtual Function<Y, Eigen::Matrix<X, M, N> > {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  DiscreteFunction(const DiscreteFunction& other);
  /// Assignment operator
  DiscreteFunction& operator = (const DiscreteFunction& other);
  /** @}
    */

public:
  /** \name Types
    @{
    */
  /// Domain type
  typedef X DomainType;
  /// Codomain type
  typedef Y CodomainType;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  DiscreteFunction();
  /// Destructor
  virtual ~DiscreteFunction();
  /** @}
    */

protected:

};

#include "functions/DiscreteFunctionMv.tpp"
