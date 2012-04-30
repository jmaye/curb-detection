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

/** \file SymmetricDirichletDistribution.h
    \brief This file defines the SymmetricDirichletDistribution class, which represents
           a Dirichlet distribution
  */

#ifndef SYMMETRICDIRICHLETDISTRIBUTION_H
#define SYMMETRICDIRICHLETDISTRIBUTION_H

#include "statistics/DirichletDistribution.h"

/** The SymmetricDirichletDistribution class represents a symmetric Dirichlet
    distribution.
    \brief Symmetric Dirichlet distribution
  */
template <size_t M> class SymmetricDirichletDistribution :
  public DirichletDistribution<M> {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameters
  SymmetricDirichletDistribution(double alpha = 1.0, size_t dim = M);
  /// Copy constructor
  SymmetricDirichletDistribution(const SymmetricDirichletDistribution& other);
  /// Assignment operator
  SymmetricDirichletDistribution& operator =
    (const SymmetricDirichletDistribution& other);
  /// Destructor
  virtual ~SymmetricDirichletDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the alpha parameter
  void setAlpha(double alpha);
  /// Returns the alpha parameter
  double getAlpha() const;
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream);
  /// Writes to standard output
  virtual void write(std::ostream& stream) const;
  /// Reads from a file
  virtual void read(std::ifstream& stream);
  /// Writes to a file
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

};

#include "statistics/SymmetricDirichletDistribution.tpp"

#endif // SYMMETRICDIRICHLETDISTRIBUTION_H
