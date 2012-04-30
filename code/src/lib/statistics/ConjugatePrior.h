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

/** \file ConjugatePrior.h
    \brief This file defines the conjugate priors
  */

#ifndef CONJUGATEPRIOR_H
#define CONJUGATEPRIOR_H

#include "statistics/NormalScaledInvChiSquareDistribution.h"
#include "statistics/NormalInvWishartDistribution.h"
//#include "statistics/DirichletDistribution.h"
//#include "statistics/GammaDistribution.h"
//#include "statistics/BetaDistribution.h"
//#include "statistics/NormalDistribution.h"
//#include "statistics/MultinomialDistribution.h"
//#include "statistics/CategoricalDistribution.h"
//#include "statistics/GeometricDistribution.h"
//#include "statistics/ExponentialDistribution.h"
//#include "statistics/PoissonDistribution.h"
//#include "statistics/MixtureDistribution.h"

/** The ConjugatePrior structure defines the ConjugatePrior template.
    \brief ConjugatePrior template
  */
template <typename D> struct ConjugatePrior;

/** The ConjugatePrior prior is defined for univariate normal distribution.
    \brief ConjugatePrior prior for univariate normal distribution
  */
template <> struct ConjugatePrior<NormalDistribution<1> > {
public:
  /// Conjugate prior for univariate normal distribution
  typedef NormalScaledInvChiSquareDistribution Result;
};

/** The ConjugatePrior prior is defined for multivariate normal distribution.
    \brief ConjugatePrior prior for multivariate normal distribution
  */
template <size_t M> struct ConjugatePrior<NormalDistribution<M> > {
public:
  /// Conjugate prior for multivariate normal distribution
  typedef NormalInvWishartDistribution<M> Result;
};

///** The ConjugatePrior prior is defined for categorical distribution.
//    \brief ConjugatePrior prior for categorical distribution
//  */
//template <size_t M> struct ConjugatePrior<CategoricalDistribution<M> > {
//public:
//  /// Conjugate prior for categorical distribution
//  typedef DirichletDistribution<M> Result;
//};

///** The ConjugatePrior prior is defined for multinomial distribution.
//    \brief ConjugatePrior prior for multinomial distribution
//  */
//template <size_t M> struct ConjugatePrior<MultinomialDistribution<M> > {
//public:
//  /// Conjugate prior for multinomial distribution
//  typedef DirichletDistribution<M> Result;
//};

///** The ConjugatePrior prior is defined for exponential distribution.
//    \brief ConjugatePrior prior for exponential distribution
//  */
//template <> struct ConjugatePrior<ExponentialDistribution> {
//public:
//  /// Conjugate prior for exponential distribution
//  typedef GammaDistribution<double> Result;
//};

///** The ConjugatePrior prior is defined for geometric distribution.
//    \brief ConjugatePrior prior for geometric distribution
//  */
//template <> struct ConjugatePrior<GeometricDistribution> {
//public:
//  /// Conjugate prior for geometric distribution
//  typedef BetaDistribution Result;
//};

///** The ConjugatePrior prior is defined for Poisson distribution.
//    \brief ConjugatePrior prior for Poisson distribution
//  */
//template <> struct ConjugatePrior<PoissonDistribution> {
//public:
//  /// Conjugate prior for Poisson distribution
//  typedef GammaDistribution<double> Result;
//};

///** The ConjugatePrior prior is defined for mixture distribution.
//    \brief ConjugatePrior prior for mixture distribution
//  */
//template <typename D, size_t M>
//struct ConjugatePrior<MixtureDistribution<D, M> > {
//public:
//  /// Conjugate prior for mixture distribution
//  typedef typename ConjugatePrior<D>::Result Result;
//};

#endif // CONJUGATEPRIOR_H
