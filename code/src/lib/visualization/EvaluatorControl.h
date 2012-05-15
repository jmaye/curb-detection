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

/** \file EvaluatorControl.h
    \brief This file defines a Qt control for the evaluation
  */

#ifndef EVALUATORCONTROL_H
#define EVALUATORCONTROL_H

#include <string>
#include <vector>

#include "visualization/Control.h"
#include "base/Singleton.h"
#include "visualization/View3d.h"
#include "visualization/Scene3d.h"
#include "data-structures/DEMGraph.h"
#include "evaluation/Evaluator.h"

class Ui_EvaluatorControl;
class Cell;
template <typename T, typename C, size_t M> class TransGrid;

/** The EvaluatorControl class represents a Qt control for evaluation.
    \brief Qt control for evaluation
  */
class EvaluatorControl :
  public Control,
  public Singleton<EvaluatorControl> {
Q_OBJECT
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  EvaluatorControl(const EvaluatorControl& other);
  /// Assignment operator
  EvaluatorControl& operator = (const EvaluatorControl& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the control with parameters
  EvaluatorControl(bool showGroundTruth = true);
  /// Destructor
  ~EvaluatorControl();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Shows the ground truth
  void setShowGroundTruth(bool showGroundTruth);
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Render the ground truth
  void renderGroundTruth();
  /// Label the DEM
  void labelDEM();
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Qt user interface
  Ui_EvaluatorControl* mUi;
  /// DEM
  TransGrid<double, Cell, 2>* mDEM;
  /// Vertices labels
  DEMGraph::VertexContainer mVertices;
  /// Evaluator of the solution
  Evaluator mEvaluator;
  /// Ground truth filename
  std::string mGTFilename;
  /** @}
    */

protected slots:
  /** \name Qt slots
    @{
    */
  /// Show ground truth toggled
  void showGroundTruthToggled(bool checked);
  /// Render the scene
  void render(View3d& view, Scene3d& scene);
  /// New point cloud read with filename
  void pointCloudRead(const std::string& filename);
  /// DEM updated
  void demUpdated(const TransGrid<double, Cell, 2>& dem);
  /// New segmentation done
  void bpUpdated(const TransGrid<double, Cell, 2>& dem, const DEMGraph& graph,
    const DEMGraph::VertexContainer& vertices);
  /** @}
    */

};

#endif // EVALUATORCONTROL_H
