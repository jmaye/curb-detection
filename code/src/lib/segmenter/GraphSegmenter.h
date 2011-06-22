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

/** \file GraphSegmenter.h
    \brief This file defines the GraphSegmenter class, which implements the
           graph-based segmentation algorithm on the DEM
  */

#ifndef GRAPHSEGMENTER_H
#define GRAPHSEGMENTER_H

#include "data-structures/Edge.h"
#include "data-structures/DEM.h"

#include <set>
#include <map>

#include <stdint.h>

/** The class GraphSegmenter implements the graph-based segmentation algorithm
    on the DEM
    \brief Segments a DEM
  */
class GraphSegmenter {
  /** \name Private constructor (not to be instantiated)
    @{
    */
  /// Default constructor
  GraphSegmenter();
  /** @}
    */

public:
  /** \name Methods
    @{
    */
  /// Segments the DEM
  static void segment(const DEM& dem,
    const std::multiset<Edge, EdgeCompare>& edgeSet,
    std::map<std::pair<uint32_t, uint32_t>, uint32_t>& labelsMap,
    std::map<uint32_t, uint32_t>& supportsMap, uint32_t u32K = 100);
  /** @}
    */

protected:

};

#endif // GRAPHSEGMENTER_H
