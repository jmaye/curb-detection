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

template <typename Y, typename X, size_t M>
void MetropolisHastingsSampler::getSamples(const ContinuousFunction<Y, X, M>&
    target, NormalDistribution<M>& proposal,
    std::vector<typename NormalDistribution<M>::RandomVariable>& samples, size_t
    numSamples) {
  samples.clear();
  samples.reserve(numSamples);
  samples.push_back(proposal.getSample());
  static const Randomizer<double> randomizer;
  while (samples.size() != numSamples) {
    proposal.setMean(samples.back());
    const typename NormalDistribution<M>::RandomVariable sample =
      proposal.getSample();
    NormalDistribution<M> proposalInv = proposal;
    proposal.setMean(sample);
    double r = target(sample) * proposalInv(samples.back()) /
      (target(samples.back()) * proposal(sample));
    if (r > 1)
      r = 1;
    const double u = randomizer.sampleUniform();
    if (u < r)
      samples.push_back(sample);
    else
      samples.push_back(samples.back());
  }
}
