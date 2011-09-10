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

template <typename G>
double GraphSegmenter<G>::mK = 100.0;

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

template <typename G>
double GraphSegmenter<G>::getTau(const
  Component<typename Graph::VertexDescriptor, double>& c) {
  return mK / c.getNumVertices();
}

template <typename G>
double GraphSegmenter<G>::getMInt(const
  Component<typename Graph::VertexDescriptor, double>& c1, const
  Component<typename Graph::VertexDescriptor, double>& c2) {
  return std::min(c1.getProperty() + getTau(c1), c2.getProperty() + getTau(c2));
}

template <typename G>
void GraphSegmenter<G>::segment(Graph& graph,
  std::list<Component<typename Graph::VertexDescriptor, double> >& components,
  double k) {
  mK = k;
  components.clear();
  size_t componentIdx = 0;
  std::map<size_t, Component<typename Graph::VertexDescriptor, double> >
    componentsMap;
  for (typename Graph::VertexIterator it = graph.getVertexBegin();
    it != graph.getVertexBegin(); ++it) {
    typename Graph::VertexDescriptor v = graph.getVertex(it);
    componentsMap[componentIdx] = Component<typename Graph::VertexDescriptor,
      double>(v);
    graph.setVertexProperty(v, componentIdx++);
  }
  for (typename Graph::ConstEdgeIterator it = graph.getEdgeBegin();
    it != graph.getEdgeEnd(); ++it) {
    typename Graph::EdgeDescriptor e = graph.getEdge(it);
    typename Graph::VertexDescriptor v1 = graph.getHeadVertex(e);
    size_t c1  = graph.getVertexProperty(v1);
    typename Graph::VertexDescriptor v2 = graph.getTailVertex(e);
    size_t c2 = graph.getVertexProperty(v2);
    if (c1 != c2 && graph.getEdgeProperty(e) <= getMInt(componentsMap[c1],
      componentsMap[c2])) {
      for (typename Component<typename
        Graph::VertexDescriptor, double>::VertexIterator it =
        componentsMap[c2].getVertexBegin();
        it != componentsMap[c2].getVertexEnd(); ++it)
        graph.setVertexProperty(*it, c1);
      double maxInt = std::max(componentsMap[c1].getProperty(),
        componentsMap[c2].getProperty());
      componentsMap[c1].setProperty(std::max(maxInt, graph.getEdgeProperty(e)));
      componentsMap[c1].merge(componentsMap[c2]);
      componentsMap.erase(c2);
    }
  }
  //componentsMap::const_iterator;
}
