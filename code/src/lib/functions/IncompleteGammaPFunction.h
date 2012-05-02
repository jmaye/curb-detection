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

/** \file IncompleteGammaPFunction.h
    \brief This file defines the IncompleteGammaPFunction class, which
           represents the complementary normalized incomplete gamma function
  */

#ifndef INCOMPLETEGAMMAPFUNCTION_H
#define INCOMPLETEGAMMAPFUNCTION_H

#include "functions/ContinuousFunction.h"
#include "base/Serializable.h"

/** The IncompleteGammaPFunction class represents the complementary normalized
    incomplete gamma function.
    \brief Complementary normalized incomplete gamma function
  */
class IncompleteGammaPFunction :
  public ContinuousFunction<double, double>,
  public virtual Serializable {
public:
  /** \name Types
    @{
    */
  /// Variable type
  typedef ContinuousFunction<double, double>::Domain VariableType;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs function with parameters
  inline IncompleteGammaPFunction(double alpha);
  /// Copy constructor
  inline IncompleteGammaPFunction(const IncompleteGammaPFunction& other);
  /// Assignment operator
  inline IncompleteGammaPFunction& operator = (const IncompleteGammaPFunction&
    other);
  /// Destructor
  inline virtual ~IncompleteGammaPFunction();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the alpha parameter
  inline double getAlpha() const;
  /// Sets the alpha parameter
  inline void setAlpha(double alpha);
  /// Access the function value for the given argument
  inline virtual double getValue(const VariableType& argument) const;
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  inline virtual void read(std::istream& stream);
  /// Writes to standard output
  inline virtual void write(std::ostream& stream) const;
  /// Reads from a file
  inline virtual void read(std::ifstream& stream);
  /// Writes to a file
  inline virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Alpha parameter
  double mAlpha;
  /** @}
    */

};

#include "functions/IncompleteGammaPFunction.tpp"

#endif // INCOMPLETEGAMMAPFUNCTION_H
