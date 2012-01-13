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

/** \file BPControl.h
    \brief This file defines a Qt control for BP segmentation.
  */

#ifndef BPCONTROL_H
#define BPCONTROL_H

#include "visualization/Control.h"
#include "base/Singleton.h"
#include "visualization/GLView.h"
#include "visualization/Scene.h"
#include "data-structures/Grid.h"
#include "data-structures/Cell.h"
#include "data-structures/DEMGraph.h"
#include "data-structures/FactorGraph.h"
#include "data-structures/PointCloud.h"
#include "helpers/RandomColors.h"

#include <vector>
#include <string>

class Ui_BPControl;

/** The BPControl class represents a Qt control for BP segmentation.
    \brief Qt control for BP segmentation
  */
class BPControl :
  public Control,
  public Singleton<BPControl> {
Q_OBJECT
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  BPControl(const BPControl& other);
  /// Assignment operator
  BPControl& operator = (const BPControl& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs control with parameter
  BPControl(bool showBP = true);
  /// Destructor
  ~BPControl();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Show BP segmentation
  void setShowBP(bool showBPSegmentation);
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Renders the BP segmentation
  void renderBP();
  /// Sets the ML maximum number of iterations
  void setMaxIter(size_t maxIter);
  /// Sets the interaction strength
  void setStrength(double strength);
  /// Sets the ML tolerance
  void setTolerance(double tol);
  /// Sets the log-domain inference
  void setLogDomain(bool checked);
  /// Sets parallel updates
  void setParallUpdates(bool checked);
  /// Sets fixed sequential updates
  void setSeqFixUpdates(bool checked);
  /// Sets random sequential updates
  void setSeqRndUpdates(bool checked);
  /// Sets max-residual sequential updates
  void setSeqMaxUpdates(bool checked);
  /// Sets MAXPROD
  void setMaxProd(bool checked);
  /// Sets SUMPROD
  void setSumProd(bool checked);
  /// Run the BP algorithm
  void runBP();
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Qt user interface
  Ui_BPControl* mUi;
  /// DEM
  Grid<double, Cell, 2> mDEM;
  /// DEM graph
  DEMGraph mGraph;
  /// Factor graph
  FactorGraph mFactorGraph;
  /// Factor graph mapping
  DEMGraph::VertexContainer mFgMapping;
  /// Vertices labels
  DEMGraph::VertexContainer mVertices;
  /// ML maximum number of iterations
  size_t mMaxIter;
  /// ML tolerance
  double mTol;
  /// Log-domain inference
  bool mLogDomain;
  /// Algo
  std::string mAlgo;
  /// Updates types
  std::string mUpdates;
  /// Vector of random colors
  std::vector<Helpers::Color> mColors;
  /// Regression coefficients
  Eigen::Matrix<double, Eigen::Dynamic, 3> mCoefficients;
  /// Regression variances
  Eigen::Matrix<double, Eigen::Dynamic, 1> mVariances;
  /// Regression weights
  Eigen::Matrix<double, Eigen::Dynamic, 1> mWeights;
  /// Edge strength
  double mStrength;
  /** @}
    */

protected slots:
  /** \name Qt slots
    @{
    */
  /// Renders the segmentation
  void render(GLView& view, Scene& scene);
  /// Maximum number of iterations changed
  void maxIterChanged(int maxIter);
  /// Interaction strength changed
  void strengthChanged(double strength);
  /// Tolerance changed
  void tolChanged(double tol);
  /// Log-domain toggled
  void logDomainToggled(bool checked);
  /// Parallel updates toggled
  void parallToggled(bool checked);
  /// Fixed sequential updates toggled
  void seqfixToggled(bool checked);
  /// Random sequential updates toggled
  void seqrndToggled(bool checked);
  /// Max-residual sequential updates toggled
  void seqmaxToggled(bool checked);
  /// MAXPROD toggled
  void maxProdToggled(bool checked);
  /// SUMPROD toggled
  void sumProdToggled(bool checked);
  /// Show the BP segmentation
  void showBPToggled(bool checked);
  /// Run button pressed
  void runPressed();
  /// ML has been updated
  void mlUpdated(const Grid<double, Cell, 2>& dem, const DEMGraph& graph,
    const Eigen::Matrix<double, Eigen::Dynamic, 3>& coefficients,
    const Eigen::Matrix<double, Eigen::Dynamic, 1>& variances,
    const Eigen::Matrix<double, Eigen::Dynamic, 1>& weights,
    const std::vector<Helpers::Color>& colors);
  void pointCloudRead(const PointCloud<double, 3>& pointCloud);
  /** @}
    */

signals:

};

#endif // BPCONTROL_H
