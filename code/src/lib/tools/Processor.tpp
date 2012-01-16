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

#include <curb-detection/statistics/EstimatorML.h>
#include <curb-detection/helpers/InitML.h>
#include <curb-detection/helpers/FGTools.h>
#include <curb-detection/data-structures/PropertySet.h>
#include <curb-detection/statistics/BeliefPropagation.h>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Processor::Processor(const Grid<double, Cell, 2>::Coordinate& minDEM,
    const Grid<double, Cell, 2>::Coordinate& maxDEM,
    const Grid<double, Cell, 2>::Coordinate& demCellSize, double k,
    size_t maxMLIter, double mlTol, bool weighted, size_t maxBPIter,
    double bpTol, bool logDomain) :
  mMinDEM(minDEM),
  mMaxDEM(maxDEM),
  mDEMCellSize(demCellSize),
  mK(k),
  mMaxMLIter(maxMLIter),
  mMLTol(mlTol),
  mWeighted(weighted),
  mMaxBPIter(maxBPIter),
  mBPTol(bpTol),
  mLogDomain(logDomain),
  mDEM(mMinDEM, mMaxDEM, mDEMCellSize),
  mGraph(mDEM) {
}

Processor::Processor(const Processor& other) :
  mMinDEM(other.mMinDEM),
  mMaxDEM(other.mMaxDEM),
  mDEMCellSize(other.mDEMCellSize),
  mK(other.mK),
  mMaxMLIter(other.mMaxMLIter),
  mMLTol(other.mMLTol),
  mWeighted(other.mWeighted),
  mMaxBPIter(other.mMaxBPIter),
  mBPTol(other.mBPTol),
  mLogDomain(other.mLogDomain),
  mDEM(other.mDEM),
  mGraph(other.mGraph),
  mVertices(other.mVertices),
  mCoefficients(other.mCoefficients),
  mVariances(other.mVariances),
  mWeights(other.mWeights){
}

Processor& Processor::operator = (const Processor& other) {
  if (this != &other) {
    mMinDEM = other.mMinDEM;
    mMaxDEM = other.mMaxDEM;
    mDEMCellSize = other.mDEMCellSize;
    mK = other.mK;
    mMaxMLIter = other.mMaxMLIter;
    mMLTol = other.mMLTol;
    mWeighted = other.mWeighted;
    mMaxBPIter = other.mMaxBPIter;
    mBPTol = other.mBPTol;
    mLogDomain = other.mLogDomain;
    mDEM = other.mDEM;
    mGraph = other.mGraph;
    mVertices = other.mVertices;
    mCoefficients = other.mCoefficients;
    mVariances = other.mVariances;
    mWeights = other.mWeights;
  }
  return *this;
}

Processor::~Processor() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Processor::read(std::istream& stream) {
}

void Processor::write(std::ostream& stream) const {
}

void Processor::read(std::ifstream& stream) {
}

void Processor::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void Processor::processPointCloud(const PointCloud<double, 3>& pointCloud) {
  mDEM.reset();
  for (PointCloud<double, 3>::ConstPointIterator it =
      pointCloud.getPointBegin();
      it != pointCloud.getPointEnd(); ++it) {
    Eigen::Matrix<double, 2, 1> point = (*it).segment(0, 2);
    if (mDEM.isInRange(point))
      mDEM(point).addPoint((*it)(2));
  }
  mGraph = DEMGraph(mDEM);
  GraphSegmenter<DEMGraph>::Components components;
  GraphSegmenter<DEMGraph>::segment(mGraph, components, mGraph.getVertices(),
    mK);
  Eigen::Matrix<double, Eigen::Dynamic, 3> initCoefficients;
  Eigen::Matrix<double, Eigen::Dynamic, 1> initVariances;
  Eigen::Matrix<double, Eigen::Dynamic, 1> initWeights;
  EstimatorML<LinearRegression<3>, 3>::Container points;
  std::vector<DEMGraph::VertexDescriptor> pointsMapping;
  if (Helpers::initML(mDEM, mGraph, components, points, pointsMapping,
      initCoefficients, initVariances, initWeights, mWeighted)) {
    EstimatorML<MixtureDistribution<LinearRegression<3>, Eigen::Dynamic>, 3,
      Eigen::Dynamic> estMixtPlane(initCoefficients, initVariances, initWeights,
      mMaxMLIter, mMLTol);
    const size_t numIter = estMixtPlane.addPoints(points.begin(),
      points.end());
    mCoefficients = estMixtPlane.getCoefficients();
    mVariances = estMixtPlane.getVariances();
    mWeights = estMixtPlane.getWeights();
    FactorGraph factorGraph;
    DEMGraph::VertexContainer fgMapping;
    Helpers::buildFactorGraph(mDEM, mGraph, mCoefficients, mVariances, mWeights,
      factorGraph, fgMapping);
    PropertySet opts;
    opts.set("maxiter", (size_t)mMaxBPIter);
    opts.set("tol", mBPTol);
    opts.set("verbose", (size_t)0);
    opts.set("updates", std::string("SEQRND"));
    opts.set("logdomain", mLogDomain);
    opts.set("inference", std::string("MAXPROD"));
    BeliefPropagation bp(factorGraph, opts);
    bp.init();
    bp.run();
    std::vector<size_t> mapState;
    mapState.reserve(factorGraph.nrVars());
    mapState = bp.findMaximum();
  }
}
