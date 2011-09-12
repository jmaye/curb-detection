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

#include <tr1/unordered_map>
#include <utils/SizeTSupport.h>

namespace std {

namespace tr1 {

/// Definition of the index type we want to hash
typedef Eigen::Matrix<size_t, 2, 1> Index;

/// Hash function for the index type
template<> inline size_t hash<Index>::operator()(Index value) const {
  return value(0) * 40 + value(1);
};

}

}

#endif // INDEXHASH_H
