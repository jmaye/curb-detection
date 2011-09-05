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

/** \file MixtureSampleDistribution.h
    \brief This file defines the class MixtureSampleDistribution, which
           represents an interface to sample mixture distributions
  */

#ifndef MIXTURESAMPLEDISTRIBUTION_H
#define MIXTURESAMPLEDISTRIBUTION_H

#include "statistics/MixtureDistribution.h"
#include "statistics/SampleDistribution.h"

#include <vector>

/** The MixtureSampleDistribution class represents an interface to sample
    mixture distributions.
    \brief Mixture sample distribution
  */
template <typename D, size_t M> class MixtureSampleDistribution :
  public MixtureDistribution<D, M>,
  public SampleDistribution<typename D::VariableType> {
public:
  /** \name Types definitions
    @{
    */
  /// Variable type
  typedef typename D::VariableType VariableType;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs from parameters
  MixtureSampleDistribution(const std::vector<D>& compDistributions, const
    CategoricalDistribution<M> assignDistribution);
  /// Copy constructor
  MixtureSampleDistribution(const MixtureSampleDistribution& other);
  /// Assignment operator
  MixtureSampleDistribution& operator = (const MixtureSampleDistribution&
    other);
  /// Destructor
  virtual ~MixtureSampleDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Access a sample drawn from the distribution
  VariableType getSample() const;
  /// Access samples drawn from the distribution
  void getSamples(std::vector<VariableType>& samples, size_t numSamples) const;
  /** @}
    */

protected:

};

#include "statistics/MixtureSampleDistribution.tpp"

#endif // MIXTURESAMPLEDISTRIBUTION_H
