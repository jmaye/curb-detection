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

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename D, size_t M>
MixtureDistribution<D, M>::MixtureDistribution(const std::vector<D>&
    compDistributions, const CategoricalDistribution<M> assignDistribution) :
    mCompDistributions(compDistributions),
    mAssignDistribution(assignDistribution) {
}

template <typename D, size_t M>
MixtureDistribution<D, M>::MixtureDistribution(const MixtureDistribution&
    other) :
    mCompDistributions(other.mCompDistributions),
    mAssignDistribution(other.mAssignDistribution) {
}

template <typename D, size_t M>
MixtureDistribution<D, M>& MixtureDistribution<D, M>::operator =
    (const MixtureDistribution& other) {
  if (this != &other) {
    mCompDistributions = other.mCompDistributions;
    mAssignDistribution = other.mAssignDistribution;
  }
  return *this;
}

template <typename D, size_t M>
MixtureDistribution<D, M>::~MixtureDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename D, size_t M>
void MixtureDistribution<D, M>::read(std::istream& stream) {
}

template <typename D, size_t M>
void MixtureDistribution<D, M>::write(std::ostream& stream) const {
  stream << "assignments distribution: " << std::endl
    << mAssignDistribution << std::endl
    << "components distributions: " << std::endl;
  for (size_t i = 0; i < mCompDistributions.size(); ++i)
    stream <<std::endl << mCompDistributions[i] << std::endl;
}

template <typename D, size_t M>
void MixtureDistribution<D, M>::read(std::ifstream& stream) {
}

template <typename D, size_t M>
void MixtureDistribution<D, M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename D, size_t M>
const std::vector<D>& MixtureDistribution<D, M>::getCompDistributions() const {
  return mCompDistributions;
}

template <typename D, size_t M>
void MixtureDistribution<D, M>::setCompDistributions(const std::vector<D>&
    compDistributions) {
  mCompDistributions = compDistributions;
}

template <typename D, size_t M>
const D& MixtureDistribution<D, M>::getCompDistribution(size_t idx) const
    throw (BadArgumentException<size_t>) {
  if (idx >= mCompDistributions.size())
    throw BadArgumentException<size_t>(idx,
      "MixtureDistribution<D, M>::getCompDistribution(): invalid index",
      __FILE__, __LINE__);
  return mCompDistributions[idx];
}

template <typename D, size_t M>
void MixtureDistribution<D, M>::setCompDistribution(const D& distribution,
    size_t idx) throw (BadArgumentException<size_t>) {
  if (idx >= mCompDistributions.size())
    throw BadArgumentException<size_t>(idx,
      "MixtureDistribution<D, M>::setCompDistribution(): invalid index",
      __FILE__, __LINE__);
  mCompDistributions[idx] = distribution;
}

template <typename D, size_t M>
const CategoricalDistribution<M>& MixtureDistribution<D, M>::
    getAssignDistribution() const {
  return mAssignDistribution;
}

template <typename D, size_t M>
void MixtureDistribution<D, M>::setAssignDistribution(const
    CategoricalDistribution<M>& assignDistribution) {
  mAssignDistribution = assignDistribution;
}

template <typename D, size_t M>
double MixtureDistribution<D, M>::pdf(const RandomVariable& value) const {
  double probability = 0.0;
  for (size_t i = 0; i < mCompDistributions.size(); ++i)
    probability += mAssignDistribution.getProbability(i) *
      mCompDistributions[i](value);
  return probability;
}

template <typename D, size_t M>
double MixtureDistribution<D, M>::pmf(const RandomVariable& value) const {
  return pdf(value);
}
