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

/** \file trangrid.cpp
    \brief This file is a testing binary for TransGrid class.
  */

#include "data-structures/TransGrid.h"

int main (int argc, char** argv) {
  TransGrid<double, size_t, 2> transGrid(
    Grid<double, size_t, 2>::Coordinate(-1.4, -2.0),
    Grid<double, size_t, 2>::Coordinate(0.6, 2.0),
    Grid<double, size_t, 2>::Coordinate(0.1, 0.1), -60.1073, 52.4747, 1.46489);
  std::cout << transGrid << std::endl;
  const Grid<double, size_t, 2>::Coordinate point(-58.25, 51.1);
  if (transGrid.isInRange(point))
    transGrid(point)++;
  return 0;
}
