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
double GraphSegmenter<G>::getTau(const Component<V, double>& c) {
  return mK / c.getNumVertices();
}

template <typename G>
double GraphSegmenter<G>::getMInt(const Component<V, double>& c1, const
  Component<V, double>& c2) {
  return std::min(c1.getProperty() + getTau(c1), c2.getProperty() + getTau(c2));
}

template <typename G>
void GraphSegmenter<G>::segment(const G& graph, Components& components,
  Vertices& vertices, double k) throw (BadArgumentException<double>) {
  if (k < 0)
    throw BadArgumentException<double>(k,
      "GraphSegmenter<G>::segment(): k must be positive", __FILE__, __LINE__);
  std::multimap<double, E> edges;
  for (CstItE it = graph.getEdgeBegin(); it != graph.getEdgeEnd(); ++it) {
    const E e = graph.getEdge(it);
    edges.insert(std::pair<double, E>(graph.getEdgeProperty(e), e));
  }
  components.clear();
  for (CstItV it = vertices.begin(); it != vertices.end(); ++it)
    components[it->second] = Component<V, double>(it->first);
  mK = k;
  typename std::multimap<double, E>::const_iterator it;
  for (it = edges.begin(); it != edges.end(); ++it) {
    const E& e = it->second;
    const V& v1 = graph.getHeadVertex(e);
    const size_t c1  = vertices[v1];
    const V& v2 = graph.getTailVertex(e);
    const size_t c2 = vertices[v2];
    if (c1 != c2 && it->first <= getMInt(components[c1], components[c2])) {
      for (CstItCV itC = components[c2].getVertexBegin();
        itC != components[c2].getVertexEnd(); ++itC)
        vertices[*itC] = c1;
      const double maxInt = std::max(components[c1].getProperty(),
        components[c2].getProperty());
      components[c1].setProperty(std::max(maxInt, it->first));
      components[c1].merge(components[c2]);
      components.erase(c2);
    }
  }
}
