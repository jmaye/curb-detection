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

/** \file RejectionSampler.h
    \brief This file defines the RejectionSampler namespace, which implements
           rejection sampling
  */

#ifndef REJECTIONSAMPLER_H
#define REJECTIONSAMPLER_H

#include <vector>

#include "functions/Function.h"
#include "statistics/SampleDistribution.h"

/** The RejectionSampler namespace implements rejection sampling.
    \brief Rejection sampler
  */
namespace RejectionSampler {
  /** \name Methods
    @{
    */
  /// Access a sample drawn from the distribution
  template <typename Y, typename X>
  X getSample(const Function<Y, X>& target, const SampleDistribution<X>&
    proposal, double k);
  /// Access samples drawn from the distribution
  template <typename Y, typename X>
  void getSamples(const Function<Y, X>& target, const
    SampleDistribution<X>& proposal, double k, std::vector<X>& samples, size_t
    numSamples);
  /** @}
    */

};

#include "statistics/RejectionSampler.tpp"

#endif // REJECTIONSAMPLER_H
