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

/** \file FactorGraph.h
    \brief This file defines the BeliefPropagation class which implements
           (loopy) Belief Propagation (BP) on factor graphs.
  */

#ifndef BELIEFPROPAGATION_H
#define BELIEFPROPAGATION_H

#include <dai/bp.h>

/** \name Types definitions
  @{
  */
  /// Belief Propagation is implemented by libDAI
typedef dai::BP BeliefPropagation;
/** @}
  */

#endif // BELIEFPROPAGATION_H
