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

#include <algorithm>
#include <map>

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

template <typename G>
double GraphSegmenter<G>::getTau(const
  Component<typename GraphType::VertexType, double>& c) {
  return mK / c.getNumVertices();
}

template <typename G>
double GraphSegmenter<G>::getMInt(const
  Component<typename GraphType::VertexType, double>& c1, const
  Component<typename GraphType::VertexType, double>& c2) {
  return std::min(c1.getProperty() + getTau(c1), c2.getProperty() + getTau(c2));
}

template <typename G>
void GraphSegmenter<G>::segment(const GraphType& graph,
  std::list<Component<typename GraphType::VertexType, double> >& components,
  double k) {
  mK = k;
  components.clear();
  std::map<typename GraphType::VertexType,
    Component<typename GraphType::VertexType, double> > vertexToComponent;
  for (typename GraphType::VertexIterator it = graph.getVertexBegin();
    it != graph.getVertexBegin(); ++it)
      components.insert(Component<typename GraphType::VertexType,
        double>(*it));
  for (typename GraphType::EdgeIterator it = graph.getEdgeBegin();
    it != graph.getEdgeEnd(); ++it) {
    it->getHead();
    it->getTail();
    if (it->getProperty() <= 0)
      ;
  }
}
