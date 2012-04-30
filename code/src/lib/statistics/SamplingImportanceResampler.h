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

/** \file SamplingImportanceResampler.h
    \brief This file defines the SamplingImportanceResampler namespace, which
           implements sampling-importance-resampling
  */

#ifndef SAMPLINGIMPORTANCERESAMPLER_H
#define SAMPLINGIMPORTANCERESAMPLER_H

#include <vector>

#include "functions/Function.h"
#include "statistics/SampleDistribution.h"

/** The SamplingImportanceResampler namespace implements
    sampling-importance-resampling.
    \brief Sampling-importance-resampler
  */
namespace SamplingImportanceResampler {
  /** \name Methods
    @{
    */
  /// Access samples drawn from the prop. distribution and their weights,
  template <typename Y, typename X>
  static void getSamples(const Function<Y, X>& target, const
    SampleDistribution<X>& proposal, std::vector<X>& weights,
    std::vector<X>& propSamples, std::vector<X>& targetSamples, size_t
    numSamples);
  /** @}
    */

};

#include "statistics/SamplingImportanceResampler.tpp"

#endif // SAMPLINGIMPORTANCERESAMPLER_H
