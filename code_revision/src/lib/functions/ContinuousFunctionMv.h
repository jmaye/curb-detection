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

/** \file ContinuousFunctionMv.h
    \brief This file defines the class ContinuousFunctionMv, which is an
           interface to the multivariate continuous functions
  */

#ifndef CONTINUOUSFUNCTIONMV_H
#define CONTINUOUSFUNCTIONMV_H

#include "functions/Function.h"

#include <Eigen/Core>

/** The class ContinuousFunctionMv is an interface to the multivariate
    continuous functions.
    \brief Multivariate continuous function
  */
template <typename Y, typename X, size_t M, size_t N> class ContinuousFunction :
  public virtual Function<Y, Eigen::Matrix<X, M, N> > {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  ContinuousFunction(const ContinuousFunction<Y, X, M, N>& other);
  /// Assignment operator
  ContinuousFunction& operator = (const ContinuousFunction<Y, X, M, N>& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  ContinuousFunction();
  /// Destructor
  virtual ~ContinuousFunction();
  /** @}
    */

protected:

};

#include "functions/ContinuousFunctionMv.tpp"

#endif // CONTINUOUSFUNCTIONMV_H
