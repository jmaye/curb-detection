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

/** \file IndexHash.h
    \brief This file defines a hash function for index types
  */

#ifndef INDEXHASH_H
#define INDEXHASH_H

#include <utils/SizeTSupport.h>

/** The IndexHash structure defines the hash function for 2d indices
    \brief Hash function for 2d indices
  */
struct IndexHash {
  /// Type of the index
  typedef Eigen::Matrix<size_t, 2, 1> Index;
  /// Number of columns
  size_t mNumCols;
  /// Constructor with parameters
  IndexHash(size_t numCols = 40) :
    mNumCols(numCols) {
  };
  /// Hash function
  size_t operator() (const Index& value) const {
    return value(0) * mNumCols + value(1);
  }
};

#endif // INDEXHASH_H
