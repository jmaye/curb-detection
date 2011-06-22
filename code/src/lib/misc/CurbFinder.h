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

/** \file CurbFinder.h
    \brief This file defines the CurbFinder class, which implements the curb
           finder algorithm
  */

#ifndef CURBFINDER_H
#define CURBFINDER_H

#include "data-structures/DEM.h"
#include "data-structures/Edge.h"
#include "data-structures/PointCloud.h"

#include <set>

/** The class CurbFinder implements the curb finder algorithm for the DEM
    \brief Finds curbs in a processed DEM
  */
class CurbFinder {
  /** \name Private constructor (not to be instantiated)
    @{
    */
  /// Default constructor
  CurbFinder();
  /** @}
    */

public:
  /** \name Methods
    @{
    */
  /// Finds curbs on the DEM
  static void find(const DEM& dem,
    const std::multiset<Edge, EdgeCompare>& edgeSet, PointCloud& pointCloud);
  /** @}
    */


protected:

};

#endif // CURBFINDER_H
