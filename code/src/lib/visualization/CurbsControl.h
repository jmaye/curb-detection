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

/** \file CurbsControl.h
    \brief This file defines a Qt control for curbs
  */

#ifndef CURBSCONTROL_H
#define CURBSCONTROL_H

#include "visualization/Control.h"
#include "base/Singleton.h"
#include "visualization/GLView.h"
#include "visualization/Scene.h"
#include "data-structures/Grid.h"
#include "data-structures/Cell.h"
#include "data-structures/DEMGraph.h"
#include "segmenter/GraphSegmenter.h"
#include "helpers/RandomColors.h"

#include <QtCore/QString>
#include <QtGui/QColor>

class Ui_CurbsControl;

/** The CurbsControl class represents a Qt control for curbs.
    \brief Qt control for curbs
  */
class CurbsControl :
  public Control,
  public Singleton<CurbsControl> {
Q_OBJECT
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  CurbsControl(const CurbsControl& other);
  /// Assignment operator
  CurbsControl& operator = (const CurbsControl& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the control with parameters
  CurbsControl(bool showCurbs = true);
  /// Destructor
  ~CurbsControl();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the line color
  void setLineColor(const QColor& color);
  /// Sets the line size
  void setLineSize(double lineSize);
  /// Shows the curbs
  void setShowCurbs(bool showCurbs);
  /// Smoothes the lines
  void setSmoothLines(bool smoothLines);
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Render the curbs
  void renderCurbs(double size, bool smooth);
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Qt user interface
  Ui_CurbsControl* mUi;
  /// Palette
  Palette mPalette;
  /// DEM
  Grid<double, Cell, 2> mDEM;
  /// Segmented vertices
  DEMGraph::VertexContainer mVertices;
  /// DEM graph
  DEMGraph mGraph;
  /** @}
    */

protected slots:
  /** \name Qt slots
    @{
    */
  /// Color changed
  void colorChanged(const QString& role, const QColor& color);
  /// Line size changed
  void lineSizeChanged(double lineSize);
  /// Show curbs toggled
  void showCurbsToggled(bool checked);
  /// Smooth lines toggled
  void smoothLinesToggled(bool checked);
  /// Render the scene
  void render(GLView& view, Scene& scene);
  /// Receives a new segmentation
  void bpUpdated(const Grid<double, Cell, 2>& dem, const DEMGraph& graph, const
    DEMGraph::VertexContainer& vertices);
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
  /** @}
    */

};

#endif // CURBSCONTROL_H
