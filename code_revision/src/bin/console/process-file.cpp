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

/** \file process-file.cpp
    \brief This file is a testing binary for processing a log file.
  */

#include "data-structures/PointCloud.h"
#include "data-structures/Grid.h"
#include "data-structures/Cell.h"
#include "data-structures/DEMGraph.h"
#include "segmenter/GraphSegmenter.h"
#include "statistics/EstimatorML.h"
#include "helpers/InitML.h"
#include "helpers/FGTools.h"
#include "data-structures/FactorGraph.h"
#include "data-structures/PropertySet.h"
#include "statistics/BeliefPropagation.h"
#include "base/Timestamp.h"


int main (int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <log-file>" << std::endl;
    return 1;
  }
  std::ifstream logFile(argv[1]);
  PointCloud<> pointCloud;
  double before = Timestamp::now();
  logFile >> pointCloud;
  double after = Timestamp::now();
  std::cout << "Loading point cloud: " << after - before << " [s]" << std::endl;
  before = Timestamp::now();
  Grid<double, Cell, 2> dem(Grid<double, Cell, 2>::Coordinate(0.0, 0.0),
    Grid<double, Cell, 2>::Coordinate(4.0, 4.0),
    Grid<double, Cell, 2>::Coordinate(0.1, 0.1));
  for (PointCloud<double, 3>::ConstPointIterator it =
    pointCloud.getPointBegin(); it != pointCloud.getPointEnd(); ++it) {
    Grid<double, Cell, 2>::Coordinate point = (*it).segment(0, 2);
    if (dem.isInRange(point))
      dem(point).addPoint((*it)(2));
  }
  after = Timestamp::now();
  std::cout << "Building DEM: " << after - before << " [s]" << std::endl;
  before = Timestamp::now();
  DEMGraph graph(dem);
  GraphSegmenter<DEMGraph>::Components components;
  GraphSegmenter<DEMGraph>::segment(graph, components, graph.getVertices());
  after = Timestamp::now();
  std::cout << "Segmenting DEM: " << after - before << " [s]" << std::endl;
  before = Timestamp::now();
  EstimatorML<LinearRegression<3>, 3>::Container points;
  Eigen::Matrix<double, Eigen::Dynamic, 1> pointsWeights;
  std::vector<DEMGraph::VertexDescriptor> pointsMapping;
  Eigen::Matrix<double, Eigen::Dynamic, 3> c;
  Eigen::Matrix<double, Eigen::Dynamic, 1> v;
  Eigen::Matrix<double, Eigen::Dynamic, 1> w;
  Helpers::initML(dem, graph, components, points, pointsWeights, pointsMapping,
    c, v, w);
  after = Timestamp::now();
  std::cout << "Initial linear regression estimation: " << after - before
    << " [s]" << std::endl;
  std::cout << "Initial coefficients: " << std::endl << c << std::endl;
  std::cout << "Initial variances: " << v.transpose() << std::endl;
  std::cout << "Initial weights: " << w.transpose() << std::endl;
  EstimatorML<MixtureDistribution<LinearRegression<3>, Eigen::Dynamic>, 3,
    Eigen::Dynamic> estMixtPlane(c, v, w);
  const size_t numIter = estMixtPlane.addPoints(points.begin(), points.end(),
    pointsWeights);
  after = Timestamp::now();
  std::cout << "Mixture linear regression estimation: " << after - before
    << " [s]" << std::endl;
  std::cout << "Final coefficients: " << std::endl
    << estMixtPlane.getCoefficients() << std::endl;
   std::cout << "Final variances: " << estMixtPlane.getVariances().transpose()
    << std::endl;
  std::cout << "Final weights: " << estMixtPlane.getWeights().transpose()
    << std::endl;
  std::cout << "EM converged in: " << numIter << " [it]" << std::endl;
  before = Timestamp::now();
  FactorGraph factorGraph;
  DEMGraph::VertexContainer fgMapping;
  Helpers::buildFactorGraph(dem, graph, estMixtPlane.getCoefficients(),
    estMixtPlane.getVariances(), estMixtPlane.getWeights(), factorGraph,
    fgMapping);
  after = Timestamp::now();
  std::cout << "Constructing factor graph: " << after - before << " [s]"
    << std::endl;
  std::ofstream dotFile("fg.dot");
  factorGraph.printDot(dotFile);
  PropertySet opts;
  opts.set("maxiter", (size_t)200);
  opts.set("tol", 1e-6);
  opts.set("verbose", (size_t)1);
  opts.set("updates", std::string("SEQRND"));
  opts.set("logdomain", false);
  opts.set("inference", std::string("SUMPROD"));
  BeliefPropagation bp(factorGraph, opts);
  bp.init();
  bp.run();
  std::cout << bp.logZ() << std::endl;
  std::cout << bp.beliefV(fgMapping[(Grid<double, Cell, 2>::Index() << 17, 35).finished()]) << std::endl;
  std::cout << estMixtPlane.getResponsibilities().row(0) << std::endl;
  return 0;
}
