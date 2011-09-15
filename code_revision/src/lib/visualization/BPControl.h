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
#include "data-structures/Component.h"
#include "segmenter/GraphSegmenter.h"
#include "helpers/RandomColors.h"

#include <vector>

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
  /// Sets the ML tolerance
  void setTolerance(double tol);
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
  /// Vertices labels
  DEMGraph::VertexContainer mVertices;
  /// ML maximum number of iterations
  size_t mMaxIter;
  /// ML tolerance
  double mTol;
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
  /// Show the BP segmentation
  void showBPToggled(bool checked);
  /// ML has been updated
  void mlUpdated(const Grid<double, Cell, 2>& dem, const DEMGraph& graph,
    const Eigen::Matrix<double, Eigen::Dynamic, 3>& coefficients,
    const Eigen::Matrix<double, Eigen::Dynamic, 1>& variances,
    const Eigen::Matrix<double, Eigen::Dynamic, 1>& weights);
  /** @}
    */

signals:
  /** \name Qt signals
    @{
    */
  /// Sends a new segmentation
  void bpUpdated(const Grid<double, Cell, 2>& dem, const DEMGraph&
    graph, const DEMGraph::VertexContainer& vertices);
  /** @}
    */

};

#endif // BPCONTROL_H
