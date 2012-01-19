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

#include "evaluation/Evaluator.h"

#include <sstream>
#include <set>
#include <map>

#include <QVector>
#include <QPoint>
#include <QPolygon>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Evaluator::Evaluator() {
}

Evaluator::Evaluator(const Evaluator& other) {
}

Evaluator& Evaluator::operator = (const Evaluator& other) {
  if (this != &other) {
  }
  return *this;
}

Evaluator::~Evaluator() {
  for (std::vector<const QRegion*>::iterator it = mClasses.begin();
      it != mClasses.end(); ++it)
    delete *it;
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Evaluator::read(std::istream& stream) {
}

void Evaluator::write(std::ostream& stream) const {
}

void Evaluator::read(std::ifstream& stream) throw (IOException) {
  if (stream.is_open() == false)
    throw IOException("Evaluator::read(): could not open file");
  QVector<QPoint> polygon;
  while (stream.eof() == false) {
    std::string line;
    getline(stream, line);
    if (line.size()) {
      std::stringstream lineStream(line);
      double x, y;
      lineStream >> x >> y;
      polygon.push_back(QPoint(x, y));
    }
    else {
      mClasses.push_back(new QRegion(QPolygon(polygon)));
      polygon.clear();
    }
  }
}

void Evaluator::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void Evaluator::evaluate(const Grid<double, Cell, 2>& dem, const DEMGraph&
    demgraph, const DEMGraph::VertexContainer& verticesLabels) const {
  std::set<size_t> labelSet;
  std::map<size_t, size_t> labelMap;
  size_t labelPool = 0;
  for (DEMGraph::ConstVertexIterator it = verticesLabels.begin(); it !=
      verticesLabels.end(); ++it)
    if (labelSet.count(it->second) == 0) {
      labelMap[it->second] = labelPool;
      labelPool++;
      labelSet.insert(it->second);
    }
  DEMGraph::VertexContainer verticesLabelsMap;
  for (DEMGraph::ConstVertexIterator it = demgraph.getVertexBegin(); it !=
      demgraph.getVertexEnd(); ++it)
    verticesLabelsMap[it->first] =
      labelMap[verticesLabels.find(it->first)->second];
  const Grid<double, Cell, 2>::Index& numCells = dem.getNumCells();
  std::set<size_t> classSet;
  std::map<size_t, size_t> classMap;
  size_t classPool = 0;
  for (size_t i = 0; i < numCells(0); ++i)
    for (size_t j = 0; j < numCells(1); ++j) {
      const Eigen::Matrix<double, 2, 1> point = 
        dem.getCoordinates((Eigen::Matrix<size_t, 2, 1>() << i, j).finished());
      for (std::vector<const QRegion*>::const_iterator it = mClasses.begin();
          it != mClasses.end(); ++it)
        if ((*it)->contains(QPoint(point(0), point(1))))
          if (classSet.count(it - mClasses.begin()) == 0) {
            classMap[it - mClasses.begin()] = classPool;
            classPool++;
            classSet.insert(it - mClasses.begin());
          }
    }
  Eigen::Matrix<size_t, Eigen::Dynamic, Eigen::Dynamic> contingencyTable =
    Eigen::Matrix<size_t, Eigen::Dynamic, Eigen::Dynamic>::Zero(classSet.size(),
    labelSet.size());
  for (DEMGraph::ConstVertexIterator it = verticesLabelsMap.begin(); it !=
      verticesLabelsMap.end(); ++it) {
    const Eigen::Matrix<double, 2, 1> point = dem.getCoordinates(it->first);
    const size_t label = it->second;
    for (std::vector<const QRegion*>::const_iterator it = mClasses.begin();
        it != mClasses.end(); ++it)
      if ((*it)->contains(QPoint(point(0), point(1))))
        contingencyTable(classMap[it - mClasses.begin()], label)++;
  }
  std::cout << contingencyTable << std::endl;
  double condEntropy = 0;
  for (size_t i = 0; i < labelSet.size(); ++i) {
    const size_t columnSum = contingencyTable.col(i).sum();
    for (size_t j = 0; j < classSet.size(); ++j)
      if (contingencyTable(j, i))
        condEntropy += (double)contingencyTable(j, i) / verticesLabels.size() *
          log((double)contingencyTable(j, i) / columnSum);
  }
  condEntropy *= -1.0;
  double entropy = 0.0;
  for (size_t i = 0; i < classSet.size(); ++i) {
    const size_t rowSum = contingencyTable.row(i).sum();
    entropy += (double)rowSum / verticesLabels.size() *
      log((double)rowSum / verticesLabels.size());
  }
  entropy *= -1.0;
  std::cout << condEntropy << std::endl;
  std::cout << entropy << std::endl;
  double homogeneity = 1.0 - (condEntropy / entropy);
  std::cout << std::fixed << "homogeneity: " << homogeneity << std::endl;
  condEntropy = 0.0;
  for (size_t i = 0; i < classSet.size(); ++i) {
    const size_t rowSum = contingencyTable.row(i).sum();
    for (size_t j = 0; j < labelSet.size(); ++j)
      if (contingencyTable(i, j))
        condEntropy += (double)contingencyTable(i, j) / verticesLabels.size() *
          log((double)contingencyTable(i, j) / rowSum);
  }
  condEntropy *= -1.0;
  entropy = 0.0;
  for (size_t i = 0; i < labelSet.size(); ++i) {
    const size_t columnSum = contingencyTable.col(i).sum();
    entropy += (double)columnSum / verticesLabels.size() *
      log((double)columnSum / verticesLabels.size());
  }
  entropy *= -1.0;
  std::cout << condEntropy << std::endl;
  std::cout << entropy << std::endl;
  double completeness = 1.0 - (condEntropy / entropy);
  std::cout << std::fixed << "completeness: " << completeness << std::endl;
  double beta = 1.0;
  double vmeasure = (1.0 + beta) * homogeneity * completeness /
    (beta * homogeneity + completeness);
  std::cout << "v-measure: " << vmeasure << std::endl;
}
