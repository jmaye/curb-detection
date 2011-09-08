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

/** \file edge-test.cpp
    \brief This file is a testing binary for testing the edge structure.
  */

#include "data-structures/UndirectedEdge.h"

int main (int argc, char** argv) {
  UndirectedEdge<size_t, double> edge(0, 1, 2.5);
  std::cout << "Edge initial:" << std::endl << edge << std::endl;
  edge.setHead(2);
  edge.setTail(4);
  edge.setProperty(3.0);
  std::cout << "Edge after:" << std::endl << edge << std::endl;
  std::cout << edge.getHead() << std::endl;
  std::cout << edge.getTail() << std::endl;
  std::cout << edge.getProperty() << std::endl;
  return 0;
}
