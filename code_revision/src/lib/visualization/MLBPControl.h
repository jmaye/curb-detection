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

/** \file MLBPControl.h
    \brief This file defines a Qt control for ML-BP segmentation.
  */

#ifndef MLBPCONTROL_H
#define MLBPCONTROL_H

#include "visualization/Control.h"
#include "base/Singleton.h"
#include "visualization/GLView.h"
#include "visualization/Scene.h"
#include "data-structures/Grid.h"
#include "data-structures/Cell.h"
#include "data-structures/DEMGraph.h"
#include "data-structures/Component.h"
#include "segmenter/GraphSegmenter.h"
#include "helpers/RandomColors.h"

#include <vector>

class Ui_MLBPControl;

/** The MLBPControl class represents a Qt control for ML-BP segmentation.
    \brief Qt control for ML-BP segmentation
  */
class MLBPControl :
  public Control,
  public Singleton<MLBPControl> {
Q_OBJECT
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  MLBPControl(const MLBPControl& other);
  /// Assignment operator
  MLBPControl& operator = (const MLBPControl& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs control with parameter
  MLBPControl(bool showMLBP = true);
  /// Destructor
  ~MLBPControl();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Show ML-BP segmentation
  void setShowMLBP(bool showMLBPSegmentation);
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Renders the ML-BP segmentation
  void renderMLBP();
  /// Sets the ML maximum number of iterations
  void setMaxIter(size_t maxIter);
  /// Sets the ML tolerance
  void setTolerance(double tol);
  /// Sets the BP maximum number of iterations
  void setMaxIterBP(size_t maxIter);
  /// Sets the BP tolerance
  void setToleranceBP(double tol);
  /// Sets the weighted linear regression flag
  void setWeighted(bool checked);
  /// Run the ML-BP algorithm
  void runMLBP();
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Qt user interface
  Ui_MLBPControl* mUi;
  /// DEM
  Grid<double, Cell, 2> mDEM;
  /// DEM graph
  DEMGraph mGraph;
  /// Segmented components
  GraphSegmenter<DEMGraph>::Components mComponents;
  /// Vertices labels
  DEMGraph::VertexContainer mVertices;
  /// ML maximum number of iterations
  size_t mMaxIter;
  /// ML tolerance
  double mTol;
  /// BP maximum number of iterations
  size_t mMaxIterBP;
  /// BP tolerance
  double mTolBP;
  /// Weighted regression
  bool mWeighted;
  /// Vector of random colors
  std::vector<Helpers::Color> mColors;
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
  /// Tolerance changed
  void tolChanged(double tol);
  /// Maximum number of iterations changed (BP)
  void maxIterBPChanged(int maxIter);
  /// Tolerance changed (BP)
  void tolBPChanged(double tol);
  /// Show the ML-BP segmentation
  void showMLBPToggled(bool checked);
  /// Weighted linear regression toggled
  void weightedToggled(bool checked);
  /// Run button pressed
  void runPressed();
  /// Segmentation updated
  void segmentUpdated(const Grid<double, Cell, 2>& dem, const DEMGraph& graph,
    const GraphSegmenter<DEMGraph>::Components& components, const
    std::vector<Helpers::Color>& colors);
  /** @}
    */

signals:
  /** \name Qt signals
    @{
    */
  /// ML-BP has been updated
  void mlbpUpdated(const Grid<double, Cell, 2>& dem, const DEMGraph& graph,
    const Eigen::Matrix<double, Eigen::Dynamic, 3>& coefficients,
    const Eigen::Matrix<double, Eigen::Dynamic, 1>& variances,
    const Eigen::Matrix<double, Eigen::Dynamic, 1>& weights,
    const std::vector<Helpers::Color>& colors);
  /** @}
    */

};

#endif // MLBPCONTROL_H
