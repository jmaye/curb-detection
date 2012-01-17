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

#include <sstream>

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
  for (std::vector<const QRegion*>::iterator it = mClusters.begin();
      it != mClusters.end(); ++it)
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
      mClusters.push_back(new QRegion(QPolygon(polygon)));
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
  std::ofstream labels("labels.log");
  for (DEMGraph::ConstVertexIterator it = verticesLabels.begin(); it !=
      verticesLabels.end(); ++it) {
    const Eigen::Matrix<double, 2, 1> point = dem.getCoordinates(it->first);
    const size_t label = it->second;
    std::cout << "Inferred label: " << label << " ";
    labels << label << " ";
    for (std::vector<const QRegion*>::const_iterator it = mClusters.begin();
        it != mClusters.end(); ++it)
      if ((*it)->contains(QPoint(point(0), point(1)))) {
        labels << it - mClusters.begin() << std::endl;
        std::cout << "Ground truth label: " << it - mClusters.begin() <<
          std::endl;
       }
  }
}
