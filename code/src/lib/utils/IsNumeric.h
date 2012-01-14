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

/** \file IsNumeric.h
    \brief This file determines if types are number
  */

#ifndef ISNUMERIC_H
#define ISNUMERIC_H

#include "utils/Boolean.h"

/** The IsNumeric structure determines if a type is numeric
    \brief Real types definitions
  */
template <typename T> struct IsNumeric {
public:
  /// Definition for non-numeric types
  typedef False Result;
};

/** The IsNumeric structure determines if a type is numeric
    \brief Numeric types definitions
  */
template <> struct IsNumeric<float> {
public:
  /// Definition for numeric type
  typedef True Result;
};

/** The IsNumeric structure determines if a type is numeric
    \brief Numeric types definitions
  */
template <> struct IsNumeric<double> {
public:
  /// Definition for numeric type
  typedef True Result;
};

/** The IsNumeric structure determines if a type is numeric
    \brief Numeric types definitions
  */
template <> struct IsNumeric<int> {
public:
  /// Definition for numeric type
  typedef True Result;
};

/** The IsNumeric structure determines if a type is numeric
    \brief Numeric types definitions
  */
template <> struct IsNumeric<unsigned int> {
public:
  /// Definition for numeric type
  typedef True Result;
};

/** The IsNumeric structure determines if a type is numeric
    \brief Numeric types definitions
  */
template <> struct IsNumeric<long> {
public:
  /// Definition for numeric type
  typedef True Result;
};

/** The IsNumeric structure determines if a type is numeric
    \brief Numeric types definitions
  */
template <> struct IsNumeric<unsigned long> {
public:
  /// Definition for numeric type
  typedef True Result;
};

#endif // ISNUMERIC_H
