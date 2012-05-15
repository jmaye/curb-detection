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

#include "exceptions/BadArgumentException.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/
template <size_t M>
CategoricalDistribution<M>::CategoricalDistribution(const
    Eigen::Matrix<double, M, 1>& probabilities) :
    MultinomialDistribution<M>(1, probabilities) {
}

template <size_t M>
CategoricalDistribution<M>::CategoricalDistribution(const
    CategoricalDistribution& other) :
    MultinomialDistribution<M>(other) {
}

template <size_t M>
CategoricalDistribution<M>& CategoricalDistribution<M>::operator = (const
    CategoricalDistribution& other) {
  if (this != &other) {
    MultinomialDistribution<M>::operator=(other);
  }
  return *this;
}

template <size_t M>
CategoricalDistribution<M>::~CategoricalDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <size_t M>
void CategoricalDistribution<M>::read(std::istream& stream) {
}

template <size_t M>
void CategoricalDistribution<M>::write(std::ostream& stream) const {
  stream << "success probabilities: " <<
    MultinomialDistribution<M>::mProbabilities.transpose();
}

template <size_t M>
void CategoricalDistribution<M>::read(std::ifstream& stream) {
}

template <size_t M>
void CategoricalDistribution<M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
void CategoricalDistribution<M>::setNumTrials(size_t numTrials) {
  if (numTrials != 1)
    throw BadArgumentException<size_t>(numTrials,
      "CategoricalDistribution<M>::setNumTrials(): number of trials must be "
      "1",
      __FILE__, __LINE__);
}
