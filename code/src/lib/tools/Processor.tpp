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

#include "helpers/InitML.h"
#include "helpers/FGTools.h"
#include "data-structures/PropertySet.h"
#include "statistics/BeliefPropagation.h"
#include "data-structures/FactorGraph.h"
#include "data-structures/Component.h"
#include "statistics/EstimatorML.h"

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
  mCoefficients(other.mCoefficients),
  mVariances(other.mVariances),
  mWeights(other.mWeights),
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
    mCoefficients = other.mCoefficients;
    mVariances = other.mVariances;
    mWeights = other.mWeights;
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

const Eigen::Matrix<double, Eigen::Dynamic, 3>& Processor::getCoefficients()
    const {
  return mCoefficients;
}

const Eigen::Matrix<double, Eigen::Dynamic, 1>& Processor::getVariances()
    const {
  return mVariances;
}

const Eigen::Matrix<double, Eigen::Dynamic, 1>& Processor::getWeights() const {
  return mWeights;
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
  for (PointCloud<double, 3>::ConstPointIterator it =
      pointCloud.getPointBegin();
      it != pointCloud.getPointEnd(); ++it) {
    Eigen::Matrix<double, 2, 1> point = (*it).segment(0, 2);
    if (mDEM.isInRange(point))
      mDEM(point).addPoint((*it)(2));
  }
  // FILTERING CODE: HACK!
  double mean = 0;
  double variance = 0;
  size_t count = 0;
  const Grid<double, Cell, 2>::Index& numCells = mDEM.getNumCells();
  for (size_t i = 0; i < numCells(0); ++i)
    for (size_t j = 0; j < numCells(1); ++j) {
      const Eigen::Matrix<double, 2, 1> point = 
        mDEM.getCoordinates((Eigen::Matrix<size_t, 2, 1>() << i, j).finished());
      const Cell& cell =
        mDEM[(Eigen::Matrix<size_t, 2, 1>() << i, j).finished()];
      const double sampleMean = cell.getHeightEstimator().getPostPredDist()
        .getMean();
      const double sampleVariance = cell.getHeightEstimator().getPostPredDist()
        .getVariance();
      if (cell.getHeightEstimator().getValid()) {
        mean += sampleMean;
        variance += sampleVariance;
        count++;
      }
    }
  mean /= count;
  variance /= count;
  for (size_t i = 0; i < numCells(0); ++i)
    for (size_t j = 0; j < numCells(1); ++j) {
      const Eigen::Matrix<double, 2, 1> point = 
        mDEM.getCoordinates((Eigen::Matrix<size_t, 2, 1>() << i, j).finished());
      Cell& cell =
        mDEM[(Eigen::Matrix<size_t, 2, 1>() << i, j).finished()];
      const double sampleMean = cell.getHeightEstimator().getPostPredDist()
        .getMean();
      if (cell.getHeightEstimator().getValid()) {
        if (NormalDistribution<1>(mean, variance)(sampleMean) == 0) {
          cell.reset();
        }
      }
    }
  // FILTERING CODE: HACK!
  mGraph = DEMGraph(mDEM);
  GraphSegmenter<DEMGraph>::Components components;
  GraphSegmenter<DEMGraph>::segment(mGraph, components, mGraph.getVertices(),
    mK);
  Eigen::Matrix<double, Eigen::Dynamic, 3> initCoefficients;
  Eigen::Matrix<double, Eigen::Dynamic, 1> initVariances;
  Eigen::Matrix<double, Eigen::Dynamic, 1> initWeights;
  EstimatorBayesImproper<LinearRegression<3>, 3>::Container points;
  std::vector<DEMGraph::VertexDescriptor> pointsMapping;
  if (Helpers::initML(mDEM, mGraph, components, points, pointsMapping,
      initCoefficients, initVariances, initWeights, mWeighted)) {
    if (initCoefficients.rows() > 1) {
      EstimatorML<MixtureDistribution<LinearRegression<3>, Eigen::Dynamic>, 3,
        Eigen::Dynamic> estMixtPlane(initCoefficients, initVariances,
        initWeights, mMaxMLIter, mMLTol);
      const size_t numIter = estMixtPlane.addPoints(points.begin(),
        points.end());
      if (estMixtPlane.getValid()) {
        mCoefficients = estMixtPlane.getCoefficients();
        mVariances = estMixtPlane.getVariances();
        mWeights = estMixtPlane.getWeights();
        FactorGraph factorGraph;
        DEMGraph::VertexContainer fgMapping;
        Helpers::buildFactorGraph(mDEM, mGraph, mCoefficients, mVariances,
          mWeights, factorGraph, fgMapping);
        PropertySet opts;
        opts.set("maxiter", (size_t)mMaxBPIter);
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
          std::cout << mCoefficients << std::endl;
          std::cout << mVariances << std::endl;
          std::cout << mWeights << std::endl;
          return;
        }
        std::vector<size_t> mapState;
        mapState.reserve(factorGraph.nrVars());
        mapState = bp.findMaximum();
        mVerticesLabels.clear();
        for (DEMGraph::ConstVertexIterator it = mGraph.getVertexBegin(); it !=
            mGraph.getVertexEnd(); ++it)
          mVerticesLabels[it->first] = mapState[fgMapping[it->first]];
        mValid = true;
      }
    }
    else {
      mVerticesLabels.clear();
      for (DEMGraph::ConstVertexIterator it = mGraph.getVertexBegin(); it !=
          mGraph.getVertexEnd(); ++it)
        mVerticesLabels[it->first] = 0;
      mValid = true;
    }
  }
}
