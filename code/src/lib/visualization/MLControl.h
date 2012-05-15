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

/** \file MLControl.h
    \brief This file defines a Qt control for ML segmentation.
  */

#ifndef MLCONTROL_H
#define MLCONTROL_H

#include "visualization/Control.h"
#include "base/Singleton.h"
#include "visualization/View3d.h"
#include "visualization/Scene3d.h"
#include "segmenter/GraphSegmenter.h"
#include "data-structures/DEMGraph.h"

class Ui_MLControl;
class Cell;
template <typename T, typename C, size_t M> class TransGrid;
template <typename D, size_t M> class MixtureDistribution;
template <size_t M> class LinearRegression;

/** The MLControl class represents a Qt control for ML segmentation.
    \brief Qt control for ML segmentation
  */
class MLControl :
  public Control,
  public Singleton<MLControl> {
Q_OBJECT
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  MLControl(const MLControl& other);
  /// Assignment operator
  MLControl& operator = (const MLControl& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs control with parameter
  MLControl(bool showML = true);
  /// Destructor
  ~MLControl();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Show ML segmentation
  void setShowML(bool showMLSegmentation);
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Renders the ML segmentation
  void renderML();
  /// Sets the ML maximum number of iterations
  void setMaxIter(size_t maxIter);
  /// Sets the ML tolerance
  void setTolerance(double tol);
  /// Sets the weighted linear regression flag
  void setWeighted(bool checked);
  /// Run the ML algorithm
  void runML();
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Qt user interface
  Ui_MLControl* mUi;
  /// DEM
  TransGrid<double, Cell, 2>* mDEM;
  /// DEM graph
  DEMGraph* mGraph;
  /// Segmented components
  GraphSegmenter<DEMGraph>::Components mComponents;
  /// Vertices labels
  DEMGraph::VertexContainer mVertices;
  /// Estimated mixture distribution
  MixtureDistribution<LinearRegression<3>, Eigen::Dynamic>* mMixtureDist;
  /// ML maximum number of iterations
  size_t mMaxIter;
  /// ML tolerance
  double mTol;
  /// Weighted regression
  bool mWeighted;
  /** @}
    */

protected slots:
  /** \name Qt slots
    @{
    */
  /// Renders the segmentation
  void render(View3d& view, Scene3d& scene);
  /// Maximum number of iterations changed
  void maxIterChanged(int maxIter);
  /// Tolerance changed
  void tolChanged(double tol);
  /// Show the ML segmentation
  void showMLToggled(bool checked);
  /// Weighted linear regression toggled
  void weightedToggled(bool checked);
  /// Run button pressed
  void runPressed();
  /// Segmentation updated
  void segmentUpdated(const TransGrid<double, Cell, 2>& dem, const DEMGraph&
    graph, const GraphSegmenter<DEMGraph>::Components& components);
  /** @}
    */

signals:
  /** \name Qt signals
    @{
    */
  /// ML has been updated
  void mlUpdated(const TransGrid<double, Cell, 2>& dem, const DEMGraph& graph,
    const MixtureDistribution<LinearRegression<3>, Eigen::Dynamic>&
    mixtureDist);
  /** @}
    */

};

#endif // MLCONTROL_H
