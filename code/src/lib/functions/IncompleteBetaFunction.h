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

/** \file IncompleteBetaFunction.h
    \brief This file defines the IncompleteBetaFunction class, which represents
           the normalized incomplete beta function
  */

#ifndef INCOMPLETEBETAFUNCTION_H
#define INCOMPLETEBETAFUNCTION_H

#include "functions/ContinuousFunction.h"
#include "base/Serializable.h"

/** The IncompleteBetaFunction class represents the normalized incomplete beta
    function.
    \brief Normalized incomplete beta function
  */
template <typename X = double> class IncompleteBetaFunction :
  public ContinuousFunction<double, X>,
  public virtual Serializable {
public:
  /** \name Types
    @{
    */
  /// Variable type
  typedef typename ContinuousFunction<double, X>::Domain VariableType;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs function with parameters
  IncompleteBetaFunction(double alpha, double beta);
  /// Copy constructor
  IncompleteBetaFunction(const IncompleteBetaFunction& other);
  /// Assignment operator
  IncompleteBetaFunction& operator = (const IncompleteBetaFunction& other);
  /// Destructor
  virtual ~IncompleteBetaFunction();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the alpha parameter
  double getAlpha() const;
  /// Sets the alpha parameter
  void setAlpha(double alpha);
  /// Returns the beta parameter
  double getBeta() const;
  /// Sets the beta parameter
  void setBeta(double beta);
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
  /// Alpha parameter
  double mAlpha;
  /// Beta parameter
  double mBeta;
  /** @}
    */

};

#include "functions/IncompleteBetaFunction.tpp"

#endif // INCOMPLETEBETAFUNCTION_H
