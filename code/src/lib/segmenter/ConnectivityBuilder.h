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

/** \file ConnectivityBuilder.h
    \brief This file defines the ConnectivityBuilder class, which implements the
           connectivity building algorithm for the DEM
  */

#ifndef CONNECTIVITYBUILDER_H
#define CONNECTIVITYBUILDER_H

#include "data-structures/DEM.h"
#include "data-structures/Edge.h"

#include <set>

/** The class ConnectivityBuilder implements the connectivity building algorithm
    for the DEM
    \brief Builds the connectivity in a DEM
  */
class ConnectivityBuilder {
  /** \name Private constructor (not to be instatiatied)
    @{
    */
  /// Default constructor
  ConnectivityBuilder();
  /** @}
    */

public:
  /** \name Methods
    @{
    */
  /// Builds the connectivity
  static void build(const DEM& dem, std::multiset<Edge, EdgeCompare>& edgeSet);
  /** @}
    */

protected:

};

#endif // CONNECTIVITYBUILDER_H
