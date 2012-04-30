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

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
SymmetricDirichletDistribution<M>::SymmetricDirichletDistribution(double
    alpha, size_t dim) :
    DirichletDistribution<M>(Eigen::Matrix<double, M, 1>::Constant(dim, alpha))
    {
}

template <size_t M>
SymmetricDirichletDistribution<M>::SymmetricDirichletDistribution(const
    SymmetricDirichletDistribution& other) :
    DirichletDistribution<M>(other) {
}

template <size_t M>
SymmetricDirichletDistribution<M>& SymmetricDirichletDistribution<M>::operator =
    (const SymmetricDirichletDistribution& other) {
  if (this != &other) {
    DirichletDistribution<2>::operator=(other);
  }
  return *this;
}

template <size_t M>
SymmetricDirichletDistribution<M>::~SymmetricDirichletDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <size_t M>
void SymmetricDirichletDistribution<M>::read(std::istream& stream) {
}

template <size_t M>
void SymmetricDirichletDistribution<M>::write(std::ostream& stream) const {
  stream << "alpha: " << DirichletDistribution<M>::mAlpha(0) *
    DirichletDistribution<M>::mAlpha.size();
}

template <size_t M>
void SymmetricDirichletDistribution<M>::read(std::ifstream& stream) {
}

template <size_t M>
void SymmetricDirichletDistribution<M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
void SymmetricDirichletDistribution<M>::setAlpha(double alpha) {
  setAlpha(Eigen::Matrix<double, M, 1>::Constant(
    DirichletDistribution<M>::mAlpha.size(), alpha));
}

template <size_t M>
double SymmetricDirichletDistribution<M>::getAlpha() const {
  return DirichletDistribution<M>::mAlpha(0) *
    DirichletDistribution<M>::mAlpha.size();
}
