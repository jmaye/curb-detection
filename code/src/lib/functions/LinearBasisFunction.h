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

/** \file LinearBasisFunction.h
    \brief This file defines the LinearBasisFunction class, which represents a
           linear basis function model
  */

#ifndef LINEARBASISFUNCTION_H
#define LINEARBASISFUNCTION_H

#include "functions/ContinuousFunction.h"
#include "base/Serializable.h"

/** The LinearBasisFunction class represents the linear basis function model.
    \brief Linear basis function model
  */
template <typename X, size_t M> class LinearBasisFunction :
  public ContinuousFunction<double, X, M - 1>,
  public virtual Serializable {
public:
  /** \name Types
    @{
    */
  /// Variable type
  typedef typename ContinuousFunction<double, X, M - 1>::Domain VariableType;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructors with the linear coefficients
  LinearBasisFunction(const Eigen::Matrix<double, M, 1>& coefficients =
    Eigen::Matrix<double, M, 1>::Ones());
  /// Copy constructor
  LinearBasisFunction(const LinearBasisFunction& other);
  /// Assignment operator
  LinearBasisFunction& operator = (const LinearBasisFunction& other);
  /// Destructor
  virtual ~LinearBasisFunction();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the linear coefficients
  const Eigen::Matrix<double, M, 1>& getCoefficients() const;
  /// Sets the linear coefficients
  void setCoefficients(const Eigen::Matrix<double, M, 1>& coefficients);
  /// Access the function value for the given argument
  virtual double getValue(const VariableType& argument) const;
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

  /** \name Protected members
    @{
    */
  /// Linear coefficients
  Eigen::Matrix<double, M, 1> mCoefficients;
  /** @}
    */

};

#include "functions/LinearBasisFunction.tpp"

#endif // LINEARBASISFUNCTION_H
