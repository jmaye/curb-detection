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

/** \file PointCloudControl.h
    \brief This file defines a Qt control for point clouds
  */

#ifndef POINTCLOUDCONTROL_H
#define POINTCLOUDCONTROL_H

#include "data-structures/PointCloud.h"
#include "visualization/Control.h"
#include "base/Singleton.h"
#include "visualization/GLView.h"
#include "visualization/Scene.h"

#include <QtCore/QString>
#include <QtGui/QColor>

class Ui_PointCloudControl;

/** The PointCloudControl class represents a Qt control for point clouds.
    \brief Qt control for point clouds
  */
class PointCloudControl :
  public Control,
  public Singleton<PointCloudControl> {
Q_OBJECT
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  PointCloudControl(const PointCloudControl& other);
  /// Assignment operator
  PointCloudControl& operator = (const PointCloudControl& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the control with parameters
  PointCloudControl(bool showPoints = true);
  /// Destructor
  ~PointCloudControl();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the points color
  void setPointColor(const QColor& color);
  /// Sets the points size
  void setPointSize(double size);
  /// Shows the points
  void setShowPoints(bool showPoints);
  /// Smoothes the points
  void setSmoothPoints(bool smoothPoints);
  /// Sets the log file to read the point cloud from
  void setLogFilename(const QString& filename);
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Render the points
  void renderPoints(double size, bool smooth);
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Qt user interface
  Ui_PointCloudControl* mUi;
  /// Palette
  Palette mPalette;
  /// Point cloud
  PointCloud<double, 3> mPointCloud;
  /** @}
    */

protected slots:
  /** \name Qt slots
    @{
    */
  /// Log file browse clicked
  void logBrowseClicked();
  /// Color changed
  void colorChanged(const QString& role, const QColor& color);
  /// Point size changed
  void pointSizeChanged(double pointSize);
  /// Show points toggled
  void showPointsToggled(bool checked);
  /// Smooth points toggled
  void smoothPointsToggled(bool checked);
  /// Render the scene
  void render(GLView& view, Scene& scene);
  /** @}
    */

signals:
  /** \name Qt signals
    @{
    */
  /// New point cloud read
  void pointCloudRead(const PointCloud<double, 3>& pointCloud);
  /** @}
    */

};

#endif // POINTCLOUDCONTROL_H
