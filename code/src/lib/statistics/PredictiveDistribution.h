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

/** \file PredictiveDistribution.h
    \brief This file defines the predictive distributions
  */

#ifndef PREDICTIVEDISTRIBUTION_H
#define PREDICTIVEDISTRIBUTION_H

#include "statistics/StudentDistribution.h"
#include "statistics/DCMDistribution.h"
#include "statistics/BetaBinomialDistribution.h"
#include "statistics/NormalDistribution.h"
#include "statistics/MultinomialDistribution.h"
#include "statistics/CategoricalDistribution.h"
#include "statistics/PoissonDistribution.h"
#include "statistics/LinearRegression.h"
#include "statistics/LinearRegressionPred.h"

/** The PredictiveDistribution structure defines the PredictiveDistribution
    template.
    \brief PredictiveDistribution template
  */
template <typename D> struct PredictiveDistribution;

/** The PredictiveDistribution is defined for univariate normal distribution.
    \brief Predictive distribution for univariate normal distribution
  */
template <> struct PredictiveDistribution<NormalDistribution<1> > {
public:
  /// Predictive distribution for univariate normal distribution
  typedef StudentDistribution<1> Result;
};

/** The PredictiveDistribution is defined for multivariate normal distribution.
    \brief Predictive distribution for multivariate normal distribution
  */
template <size_t M> struct PredictiveDistribution<NormalDistribution<M> > {
public:
  /// Predictive distribution for multivariate normal distribution
  typedef StudentDistribution<M> Result;
};

/** The PredictiveDistribution is defined for categorical distribution.
    \brief Predictive distribution for categorical distribution
  */
template <size_t M> struct PredictiveDistribution<CategoricalDistribution<M> > {
public:
  /// Predictive distribution for categorical distribution
  typedef DCMDistribution<M> Result;
};

/** The PredictiveDistribution is defined for multinomial distribution.
    \brief Predictive distribution for multinomial distribution
  */
template <size_t M> struct PredictiveDistribution<MultinomialDistribution<M> > {
public:
  /// Predictive distribution for multinomial distribution
  typedef DCMDistribution<M> Result;
};

/** The PredictiveDistribution is defined for Poisson distribution.
    \brief Predictive distribution for Poisson distribution
  */
template <> struct PredictiveDistribution<PoissonDistribution> {
public:
  /// Predictive distribution for Poisson distribution
  typedef BetaBinomialDistribution Result;
};

/** The PredictiveDistribution is defined for linear regression models.
    \brief Predictive distribution for linear regression models
  */
template <size_t M> struct PredictiveDistribution<LinearRegression<M> > {
public:
  /// Predictive distribution for linear regression
  typedef LinearRegressionPred<M> Result;
};

#endif // PREDICTIVEDISTRIBUTION_H
