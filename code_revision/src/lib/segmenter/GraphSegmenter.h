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
           graph-based segmentation algorithm from Felzenszwalb [2004]
  */

#ifndef GRAPHSEGMENTER_H
#define GRAPHSEGMENTER_H

#include "data-structures/Component.h"

/** The class GraphSegmenter implements the graph-based segmentation algorithm
    described in [Felzenszwalb, 2004]
    \brief Graph-based segmentation algorithm
  */
template <typename G> class GraphSegmenter {
  /** \name Types definitions
      @{
    */
  /// Graph type
  typedef G GraphType;
  /** @}
    */

  /** \name Private constructors
    @{
    */
  /// Default constructor
  GraphSegmenter();
  /** @}
    */

  /** \name Private methods
    @{
    */
  /// Threshold function
  static double getTau(const Component<typename GraphType::VertexType, double>&
   c);
  /// Returns the minimum internal difference between two components
  static double getMInt(const Component<typename GraphType::VertexType, double>&
    c1, const Component<typename GraphType::VertexType, double>& c2);
  /** @}
    */

  /** \name Private members
    @{
    */
  /// Parameter for the algorithm
  static double mK;
  /** @}
    */

public:
  /** \name Methods
      @{
    */
  /// Segment the graph
  static void segment(const GraphType& graph,
    std::list<Component<typename GraphType::VertexType, double> >& components,
    double k = 100.0);
  /** @}
    */

};

#include "segmenter/GraphSegmenter.tpp"

#endif // GRAPHSEGMENTER_H
