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

/** \file If.h
    \brief This file defines the if template
  */

#ifndef IF_H
#define IF_H

#include "utils/Boolean.h"

/** The If structure defines the If template
    \brief If template
  */
template <typename C> struct If {
};

/** The IfThenElse structure defines the If-Then-Else template
    \brief If template
  */
template <> struct If<True> {
public:
  /// Definition for true
  typedef True Result;
};

#endif // IF_H
