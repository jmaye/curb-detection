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

/** \file graph-test.cpp
    \brief This file is a testing binary for testing the graph structure.
  */

#include "data-structures/Graph.h"

int main (int argc, char** argv) {
  Graph<size_t, size_t, size_t, double> graph;
  graph.insertEdge(0, 1);
  graph.insertEdge(1, 2);
  std::cout << "Initial graph: " << std::endl << graph << std::endl;
  graph.setEdgeProperty(0, 2.5);
  graph.setVertexProperty(0, 2);
  std::cout << "Final graph: " << std::endl << graph << std::endl;
  std::cout << graph.getNumVertices() << std::endl;
  std::cout << graph.getNumEdges() << std::endl;
  std::cout << graph.getEdge(0, 1) << std::endl;
  std::cout << graph.containsVertex(3) << std::endl;
  std::cout << graph.containsEdge(3, 4) << std::endl;
  std::cout << graph.getEdgeProperty(0) << std::endl;
  std::cout << graph.getVertexProperty(0) << std::endl;
  std::cout << graph.getTailVertex(0) << std::endl;
  std::cout << graph.getHeadVertex(0) << std::endl;
  return 0;
}
