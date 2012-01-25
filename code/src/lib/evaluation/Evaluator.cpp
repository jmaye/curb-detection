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
  clear();
  while (stream.eof() == false) {
    std::string line;
    getline(stream, line);
    if (line.size()) {
      std::stringstream lineStream(line);
      int x, y;
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

double Evaluator::computeVMeasure(const
  Eigen::Matrix<size_t, Eigen::Dynamic, Eigen::Dynamic>& contingencyTable,
  double beta) const {
  double condEntropy = 0;
  for (size_t i = 0; i < static_cast<size_t>(contingencyTable.cols()); ++i) {
    const size_t columnSum = contingencyTable.col(i).sum();
    for (size_t j = 0; j < static_cast<size_t>(contingencyTable.rows()); ++j)
      if (contingencyTable(j, i))
        condEntropy += (double)contingencyTable(j, i) / contingencyTable.sum() *
          log((double)contingencyTable(j, i) / columnSum);
  }
  condEntropy *= -1.0;
  double entropy = 0.0;
  for (size_t i = 0; i < static_cast<size_t>(contingencyTable.rows()); ++i) {
    const size_t rowSum = contingencyTable.row(i).sum();
    entropy += (double)rowSum / contingencyTable.sum() *
      log((double)rowSum / contingencyTable.sum());
  }
  entropy *= -1.0;
  double homogeneity = 1.0 - (condEntropy / entropy);
  if (contingencyTable.rows() == 1)
    homogeneity = 1.0;
  condEntropy = 0.0;
  for (size_t i = 0; i < static_cast<size_t>(contingencyTable.rows()); ++i) {
    const size_t rowSum = contingencyTable.row(i).sum();
    for (size_t j = 0; j < static_cast<size_t>(contingencyTable.cols()); ++j)
      if (contingencyTable(i, j))
        condEntropy += (double)contingencyTable(i, j) / contingencyTable.sum() *
          log((double)contingencyTable(i, j) / rowSum);
  }
  condEntropy *= -1.0;
  entropy = 0.0;
  for (size_t i = 0; i < static_cast<size_t>(contingencyTable.cols()); ++i) {
    const size_t columnSum = contingencyTable.col(i).sum();
    entropy += (double)columnSum / contingencyTable.sum() *
      log((double)columnSum / contingencyTable.sum());
  }
  entropy *= -1.0;
  double completeness = 1.0 - (condEntropy / entropy);
  if (contingencyTable.cols() == 1)
    completeness = 1.0;
  return (1.0 + beta) * homogeneity * completeness /
    (beta * homogeneity + completeness);
}

double Evaluator::evaluate(const Grid<double, Cell, 2>& dem, const DEMGraph&
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
      const Cell& cell =
        dem[(Eigen::Matrix<size_t, 2, 1>() << i, j).finished()];
      if (cell.getHeightEstimator().getValid() == false)
        continue;
      const Eigen::Matrix<double, 2, 1> point = 
        dem.getCoordinates((Eigen::Matrix<size_t, 2, 1>() << i, j).finished());
      for (std::vector<const QRegion*>::const_iterator it = mClasses.begin();
          it != mClasses.end(); ++it)
        if ((*it)->contains(QPoint(point(0) * 1000.0, point(1) * 1000.0)))
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
      if ((*it)->contains(QPoint(point(0) * 1000.0, point(1) * 1000.0)))
        contingencyTable(classMap[it - mClasses.begin()], label)++;
  }
  return computeVMeasure(contingencyTable, 1.0);
}

double Evaluator::evaluate(const Grid<double, Cell, 2>& dem, const DEMGraph&
    demgraph, const DEMGraph::VertexContainer& verticesLabels, double x, double
    y, double yaw) {
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
  setTransformation(x, y, 0, 0, 0, yaw);
  for (size_t i = 0; i < numCells(0); ++i)
    for (size_t j = 0; j < numCells(1); ++j) {
      const Cell& cell =
        dem[(Eigen::Matrix<size_t, 2, 1>() << i, j).finished()];
      if (cell.getHeightEstimator().getValid() == false)
        continue;
      Eigen::Matrix<double, 2, 1> point = 
        dem.getCoordinates((Eigen::Matrix<size_t, 2, 1>() << i, j).finished());
      transform(point, point);
      for (std::vector<const QRegion*>::const_iterator it = mClasses.begin();
          it != mClasses.end(); ++it)
        if ((*it)->contains(QPoint(point(0) * 1000.0, point(1) * 1000.0)))
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
    Eigen::Matrix<double, 2, 1> point = dem.getCoordinates(it->first);
    transform(point, point);
    const size_t label = it->second;
    for (std::vector<const QRegion*>::const_iterator it = mClasses.begin();
        it != mClasses.end(); ++it)
      if ((*it)->contains(QPoint(point(0) * 1000.0, point(1) * 1000.0)))
        contingencyTable(classMap[it - mClasses.begin()], label)++;
  }
  return computeVMeasure(contingencyTable, 1.0);
}

size_t Evaluator::getNumClasses() const {
  return mClasses.size();
}

void Evaluator::clear() {
  for (std::vector<const QRegion*>::iterator it = mClasses.begin();
      it != mClasses.end(); ++it)
    delete *it;
  mClasses.clear();
}

size_t Evaluator::getLabel(const Eigen::Matrix<double, 2, 1>& point) const {
  for (std::vector<const QRegion*>::const_iterator it = mClasses.begin();
      it != mClasses.end(); ++it)
    if ((*it)->contains(QPoint(point(0) * 1000.0, point(1) * 1000.0)))
      return it - mClasses.begin();
  return 0;
}

size_t Evaluator::getLabel(Eigen::Matrix<double, 2, 1>& point, double x,
  double y, double yaw) {
  Eigen::Matrix<double, 2, 1>& pointCopy = point;
  mTransformation.setTransformation(x, y, yaw);
  mTransformation.transform(pointCopy, pointCopy);
  setTransformation(x, y, 0, 0, 0, yaw);
  transform(point, point);
  for (std::vector<const QRegion*>::const_iterator it = mClasses.begin();
      it != mClasses.end(); ++it)
    if ((*it)->contains(QPoint(point(0) * 1000.0, point(1) * 1000.0)))
      return it - mClasses.begin();
  return 0;
}

void Evaluator::setTransformation(double x, double y, double z, double roll,
    double pitch, double yaw) {
  double A = cos(yaw), B = sin(yaw), C = cos(pitch), D = sin(pitch),
    E = cos(roll), F = sin(roll), DE = D * E, DF = D * F;
  mTransformationMatrix(0, 0) = A * C;
  mTransformationMatrix(0, 1) = A * DF - B * E;
  mTransformationMatrix(0, 2) = B * F + A * DE;
  mTransformationMatrix(0, 3) = x;
  mTransformationMatrix(1, 0) = B * C;
  mTransformationMatrix(1, 1) = A * E + B * DF;
  mTransformationMatrix(1, 2) = B * DE - A * F;
  mTransformationMatrix(1, 3) = y;
  mTransformationMatrix(2, 0) = -D;
  mTransformationMatrix(2, 1) = C * F;
  mTransformationMatrix(2 ,2) = C * E;
  mTransformationMatrix(2, 3) = z;
  mTransformationMatrix(3, 0) = 0;
  mTransformationMatrix(3, 1) = 0;
  mTransformationMatrix(3, 2) = 0;
  mTransformationMatrix(3, 3) = 1;
}

void Evaluator::transform(const Eigen::Matrix<double, 2, 1>& src,
    Eigen::Matrix<double, 2, 1>& dest) const {
  double pX = src(0), pY = src(1), pZ = 0;
  dest(0) = mTransformationMatrix(0, 0) * pX + mTransformationMatrix(0, 1) * pY
    + mTransformationMatrix(0, 2) * pZ + mTransformationMatrix(0, 3);
  dest(1) = mTransformationMatrix(1, 0) * pX + mTransformationMatrix(1, 1) * pY
    + mTransformationMatrix(1, 2) * pZ + mTransformationMatrix(1, 3);
  //dest(2) = mTransformationMatrix(2, 0) * pX + mTransformationMatrix(2, 1) * pY
    //+ mTransformationMatrix(2, 2) * pZ + mTransformationMatrix(2, 3);
}
