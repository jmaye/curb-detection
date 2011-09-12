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

#include "functions/LogGammaFunction.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename X, size_t M>
LogBetaFunction<X, M>::LogBetaFunction() {
}

template <typename X, size_t M>
LogBetaFunction<X, M>::~LogBetaFunction() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename X, size_t M>
double LogBetaFunction<X, M>::getValue(const Eigen::Matrix<X, M, 1>& argument)
  const {
  LogGammaFunction<X> logGamma;
  X sum = X(0);
  X logSumGamma = X(0);

  for (size_t i = 0; i < (size_t)argument.size(); ++i) {
    sum += argument(i);
    logSumGamma += logGamma(argument(i));
  }

  return logSumGamma - logGamma(sum);
}
