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

#include "statistics/Randomizer.h"

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

template <typename Y, typename X>
X RejectionSampler::getSample(const Function<Y, X>& target, const
    SampleDistribution<X>& proposal, double k) {
  const static Randomizer<double> randomizer;
  while (1) {
    const X z0 = proposal.getSample();
    const double u0 = randomizer.sampleUniform(0, k * proposal(z0));
    if (u0 <= target(z0))
      return z0;
  }
}

template <typename Y, typename X>
void RejectionSampler::getSamples(const Function<Y, X>& target, const
    SampleDistribution<X>& proposal, double k, std::vector<X>& samples, size_t
    numSamples) {
  samples.clear();
  samples.reserve(numSamples);
  for (size_t i = 0; i < numSamples; ++i)
    samples.push_back(getSample(target, proposal, k));
}
