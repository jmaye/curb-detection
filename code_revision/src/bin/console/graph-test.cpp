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
  Graph<size_t, double> component;
  component.insertVertex(2);
  component.insertVertex(3);
  std::cout << "Component initial:" << std::endl << component << std::endl;
  component.removeVertex(3);
  component.removeVertex(5);
  component.setProperty(3.0);
  std::cout << "Component after:" << std::endl << component << std::endl;
  std::cout << component.getNumVertices() << std::endl;
  std::cout << component.getProperty() << std::endl;
  return 0;
}
