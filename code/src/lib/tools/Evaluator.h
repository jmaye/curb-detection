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

/** \file Evaluator.h
    \brief This file defines the Evaluator class, which performs all the
           computations to detect planes, curbs, and sidewalks.
  */

#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "base/Serializable.h"

#include <vector>

/** The class Evaluator performs all the computations to detect planes, curbs,
    and sidewalks from a 3D point cloud input.
    \brief Evaluator for curb detection
  */
class Evaluator :
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  Evaluator();
  /// Copy constructor
  Evaluator(const Evaluator& other);
  /// Assignment operator
  Evaluator& operator = (const Evaluator& other);
  /// Destructor
  virtual ~Evaluator();
  /** @}
    */

  /** \name Accessors
      @{
    */
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
  /** @}
    */

};

#include "tools/Evaluator.tpp"

#endif // EVALUATOR_H
