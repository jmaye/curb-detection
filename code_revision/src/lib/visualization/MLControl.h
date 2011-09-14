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
#include "visualization/GLView.h"
#include "visualization/Scene.h"
#include "data-structures/Grid.h"
#include "data-structures/Cell.h"
#include "data-structures/DEMGraph.h"
#include "data-structures/Component.h"
#include "segmenter/GraphSegmenter.h"

#include <vector>

class Ui_MLControl;

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

  /** \name Private types definitions
    @{
    */
  /// Color type
  struct Color {
    /// Red component
    GLfloat mRedColor;
    /// Green component
    GLfloat mGreenColor;
    /// Blue component
    GLfloat mBlueColor;
  };
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
  /// Returns a random color
  void getColor(Color& color) const;
  /// Sets the ML maximum number of iterations
  void setMaxIter(size_t maxIter);
  /// Sets the ML tolerance
  void setTolerance(double tol);
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
  Grid<double, Cell, 2> mDEM;
  /// Vertices labels
  DEMGraph::VertexContainer mVertices;
  /// Points for ML
  EstimatorML<LinearRegression<3>, 3>::Container mPoints;
  /// Points mapping for displaying
  std::vector<DEMGraph::VertexDescriptor> mPointsMapping;
  /// Initial coefficients
  Eigen::Matrix<double, Eigen::Dynamic, 3> mC;
  /// Initial variances
  Eigen::Matrix<double, Eigen::Dynamic, 1> mV;
  /// Initial weights
  Eigen::Matrix<double, Eigen::Dynamic, 1> mW;
  /// ML maximum number of iterations
  size_t mMaxIter;
  /// ML tolerance
  double mTol;
  /// Vector of random colors
  std::vector<Color> mColors;
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
  /// Show the ML segmentation
  void showMLToggled(bool checked);
  /// Segmentation updated
  void segmentUpdated(const Grid<double, Cell, 2>& dem, const DEMGraph& graph,
    const GraphSegmenter<DEMGraph>::Components& components);
  /** @}
    */

signals:
  /** \name Qt signals
    @{
    */
  /** @}
    */

};

#endif // MLCONTROL_H
