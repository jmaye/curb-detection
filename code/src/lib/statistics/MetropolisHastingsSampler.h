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

/** \file MetropolisHastingsSampler.h
    \brief This file defines the MetropolisHastingsSampler namespace, which
           implements Metropolis-Hastings sampling
  */

#ifndef METROPOLISHASTINGSSAMPLER_H
#define METROPOLISHASTINGSSAMPLER_H

#include <vector>

#include "functions/ContinuousFunction.h"
#include "statistics/NormalDistribution.h"

/** The MetropolisHastingsSampler namespace implements Metropolis-Hastings
    sampling.
    \brief Metropolis-Hastings sampler
  */
namespace MetropolisHastingsSampler {
  /** \name Methods
    @{
    */
  /// Access samples
  template <typename Y, typename X, size_t M>
  void getSamples(const ContinuousFunction<Y, X, M>& target,
    NormalDistribution<M>& proposal,
    std::vector<typename NormalDistribution<M>::RandomVariable>& samples, size_t
    numSamples);
  /** @}
    */

};

#include "statistics/MetropolisHastingsSampler.tpp"

#endif // METROPOLISHASTINGSSAMPLER_H
