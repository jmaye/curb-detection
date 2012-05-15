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

namespace ImportanceSampler {

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

template <typename Y, typename X>
void getSamples(const Function<Y, X>& target, const SampleDistribution<X>&
    proposal, std::vector<X>& weights, std::vector<X>& samples, size_t
    numSamples) {
  samples.clear();
  samples.reserve(numSamples);
  weights.clear();
  weights.reserve(numSamples);
  double normalizer = 0;
  for (size_t i = 0; i < numSamples; ++i) {
    const X sample = proposal.getSample();
    samples.push_back(sample);
    const double weight = target(sample) / proposal(sample);
    weights.push_back(weight);
    normalizer += weight;
  }
  for (size_t i = 0; i < numSamples; ++i)
    weights[i] /= normalizer;
}

}
