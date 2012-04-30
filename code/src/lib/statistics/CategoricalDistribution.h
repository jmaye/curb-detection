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

/** \file CategoricalDistribution.h
    \brief This file defines the CategoricalDistribution class, which
           represents a categorical distribution
  */

#ifndef CATEGORICALDISTRIBUTION_H
#define CATEGORICALDISTRIBUTION_H

#include "statistics/MultinomialDistribution.h"
#include "exceptions/BadArgumentException.h"

/** The CategoricalDistribution class represents a categorical distribution,
    i.e., the discrete distribution of a random event that can take one out of K
    values.
    \brief Categorical distribution
  */
template <size_t M> class CategoricalDistribution:
  public MultinomialDistribution<M> {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameters
  CategoricalDistribution(const Eigen::Matrix<double, M, 1>&
    probabilities = Eigen::Matrix<double, M, 1>::Constant(1.0 / M));
  /// Copy constructor
  CategoricalDistribution(const CategoricalDistribution& other);
  /// Assignment operator
  CategoricalDistribution& operator = (const CategoricalDistribution& other);
  /// Destructor
  virtual ~CategoricalDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the number of trials
  virtual void setNumTrials(size_t numTrials)
    throw (BadArgumentException<size_t>);
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

#include "statistics/CategoricalDistribution.tpp"

#endif // CATEGORICALDISTRIBUTION_H
