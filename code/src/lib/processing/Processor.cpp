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

#include "processing/Processor.h"

#include "helpers/InitML.h"
#include "helpers/FGTools.h"
#include "data-structures/PropertySet.h"
#include "ml/BeliefPropagation.h"
#include "data-structures/FactorGraph.h"
#include "data-structures/Component.h"
#include "statistics/EstimatorML.h"
#include "segmenter/GraphSegmenter.h"

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
    mGraph(mDEM),
    mValid(false) {
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
    mVerticesLabels(other.mVerticesLabels),
    mValid(other.mValid) {
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
    mVerticesLabels = other.mVerticesLabels;
    mValid = other.mValid;
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

const Grid<double, Cell, 2>::Coordinate& Processor::getMinDEM() const {
  return mMinDEM;
}

void Processor::setMinDEM(const Grid<double, Cell, 2>::Coordinate& minDEM) {
  mMinDEM = minDEM;
}

const Grid<double, Cell, 2>::Coordinate& Processor::getMaxDEM() const {
  return mMaxDEM;
}

void Processor::setMaxDEM(const Grid<double, Cell, 2>::Coordinate& maxDEM) {
  mMaxDEM = maxDEM;
}

const Grid<double, Cell, 2>::Coordinate& Processor::getDEMCellSize() const {
  return mDEMCellSize;
}

void Processor::setDEMCellSize(const Grid<double, Cell, 2>::Coordinate&
    demCellSize) {
  mDEMCellSize = demCellSize;
}

double Processor::getSegmentationParam() const {
  return mK;
}

void Processor::setSegmentationParam(double k) {
  mK = k;
}

size_t Processor::getMLMaxIter() const {
  return mMaxMLIter;
}

void Processor::setMLMaxIter(size_t maxMLIter) {
  mMaxMLIter = maxMLIter;
}

double Processor::getMLTol() const {
  return mMLTol;
}

void Processor::setMLTol(double mlTol) {
  mMLTol = mlTol;
}

bool Processor::getWeightedRegressionFlag() const {
  return mWeighted;
}

void Processor::setWeightedRegressionFlag(bool weighted) {
  mWeighted = weighted;
}

size_t Processor::getBPMaxIter() const {
  return mMaxBPIter;
}

void Processor::setBPMaxIter(size_t maxBPIter) {
  mMaxBPIter = maxBPIter;
}

double Processor::getBPTol() const {
  return mBPTol;
}

void Processor::setBPTol(double bpTol) {
  mBPTol = bpTol;
}

bool Processor::getLogDomainFlag() const {
  return mLogDomain;
}

void Processor::setLogDomainFlag(bool logDomain) {
  mLogDomain = logDomain;
}

const Grid<double, Cell, 2>& Processor::getDEM() const {
  return mDEM;
}

const DEMGraph& Processor::getDEMGraph() const {
  return mGraph;
}

const DEMGraph::VertexContainer& Processor::getVerticesLabels() const {
  return mVerticesLabels;
}

bool Processor::getValid() const {
  return mValid;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void Processor::processPointCloud(const PointCloud<double, 3>& pointCloud) {
  mDEM.reset();
  mValid = false;
  double before = Timestamp::now();
  for (auto it = pointCloud.getPointBegin(); it != pointCloud.getPointEnd();
      ++it) {
    const Eigen::Matrix<double, 2, 1> point = (*it).segment(0, 2);
    if (mDEM.isInRange(point))
      mDEM(point).addPoint((*it)(2));
  }
  double after = Timestamp::now();
  std::cout << "DEM creation: " << after - before << std::endl;
  const double demTime = after - before;
  before = Timestamp::now();
  mGraph = DEMGraph(mDEM);
  after = Timestamp::now();
  std::cout << "Graph creation: " << after - before << std::endl;
  const double graphTime = after - before;
  before = Timestamp::now();
  GraphSegmenter<DEMGraph>::Components components;
  GraphSegmenter<DEMGraph>::segment(mGraph, components, mGraph.getVertices(),
    mK);
  after = Timestamp::now();
  std::cout << "Graph segmentation: " << after - before << std::endl;
  const double segTime = after - before;
  std::cout << "Init time: " << demTime + graphTime + segTime << std::endl;
  before = Timestamp::now();
  EstimatorML<LinearRegression<3> >::Container points;
  std::vector<DEMGraph::VertexDescriptor> pointsMapping;
  MixtureDistribution<LinearRegression<3>, Eigen::Dynamic>* initMixture = 0;
  if (Helpers::initML(mDEM, mGraph, components, points, pointsMapping,
      initMixture, mWeighted)) {
    after = Timestamp::now();
    std::cout << "Initial ML: " << after - before << std::endl;
    if (initMixture->getCompDistributions().size() > 1) {
      before = Timestamp::now();
      EstimatorML<MixtureDistribution<LinearRegression<3>, Eigen::Dynamic> >
        estMixtPlane(*initMixture, mMaxMLIter, mMLTol);
      const size_t numIter = estMixtPlane.addPointsEM(points.begin(),
        points.end());
      after = Timestamp::now();
      std::cout << "Mixture ML: " << after - before << std::endl;
      if (estMixtPlane.getValid()) {
        FactorGraph factorGraph;
        DEMGraph::VertexContainer fgMapping;
        Helpers::buildFactorGraph(mDEM, mGraph, estMixtPlane.getMixtureDist(),
          factorGraph, fgMapping);
        PropertySet opts;
        opts.set("maxiter", mMaxBPIter);
        opts.set("tol", mBPTol);
        opts.set("verbose", (size_t)0);
        opts.set("updates", std::string("SEQRND"));
        opts.set("logdomain", mLogDomain);
        opts.set("inference", std::string("MAXPROD"));
        BeliefPropagation bp(factorGraph, opts);
        bp.init();
        try {
          bp.run();
        }
        catch (dai::Exception& e) {
          std::cout << estMixtPlane.getMixtureDist() << std::endl;
          return;
        }
        std::vector<size_t> mapState;
        mapState.reserve(factorGraph.nrVars());
        mapState = bp.findMaximum();
        mVerticesLabels.clear();
        for (auto it = mGraph.getVertexBegin(); it != mGraph.getVertexEnd();
            ++it)
          mVerticesLabels[it->first] = mapState[fgMapping[it->first]];
        mValid = true;
      }
    }
    else {
      mVerticesLabels.clear();
      for (auto it = mGraph.getVertexBegin(); it != mGraph.getVertexEnd();
          ++it)
        mVerticesLabels[it->first] = 0;
      mValid = true;
    }
  }
  if (initMixture)
    delete initMixture;
}
