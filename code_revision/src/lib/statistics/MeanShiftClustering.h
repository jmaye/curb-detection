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

/** \file MeanShiftClustering.h
    \brief This file defines the MeanShiftClustering class, which implements a
           mean-shift clustering algorithm
  */

#ifndef MEANSHIFTCLUSTERING_H
#define MEANSHIFTCLUSTERING_H

#include "exceptions/BadArgumentException.h"

#include <Eigen/Core>

#include <vector>

/** This class implements a mean-shift clustering algorithm.
    \brief Mean-shift clustering algorithm
  */
template <typename T, size_t M> class MeanShiftClustering {
  /** \name Private constructors
    @{
    */
  /// Default constructor
  MeanShiftClustering();
  /** @}
    */

public:
  /** \name Methods
    @{
    */
  /// Clusters the input data points
  static void cluster(const std::vector<Eigen::Matrix<T, M, 1> >& data,
    std::vector<Eigen::Matrix<T, M, 1> >& clusterCenters,
    std::vector<std::vector<size_t> >& clusterToData, std::vector<size_t>&
    dataToCluster, double bandwidth, double tol = 1e-6, bool debug = false)
    throw (BadArgumentException<double>, BadArgumentException<size_t>);
  /** @}
    */

protected:

};

#include "statistics/MeanShiftClustering.tpp"

#endif // MEANSHIFTCLUSTERING_H
