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

/** \file ViewControl.h
    \brief This file defines a Qt control for viewing a scene
  */

#ifndef VIEWCONTROL_H
#define VIEWCONTROL_H

#include "visualization/Control.h"
#include "base/Singleton.h"
#include "visualization/GLView.h"
#include "visualization/Scene.h"

#include <QtCore/QString>
#include <QtGui/QColor>

#include <vector>

class Ui_ViewControl;

/** The ViewControl class represents a Qt control for viewing a scene.
    \brief Qt control for viewing a scene
  */
class ViewControl :
  public Control,
  public Singleton<ViewControl> {
Q_OBJECT
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  ViewControl(const ViewControl& other);
  /// Assignment operator
  ViewControl& operator = (const ViewControl& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs control from parameters
  ViewControl(bool showFog = true, bool showGround = true,
    bool showAxes = true);
  /// Destructor
  ~ViewControl();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the background color
  void setBackgroundColor(const QColor& color);
  /// Sets the fog color
  void setFogColor(const QColor& color);
  /// Sets the ground color
  void setGroundColor(const QColor& color);
  /// Sets the ground radius
  void setGroundRadius(double radius);
  /// Sets the ground elevation
  void setGroundElevation(double elevation);
  /// Show fog
  void setShowFog(bool showFog);
  /// Show ground
  void setShowGround(bool showGround);
  /// Show axes
  void setShowAxes(bool showAxes);
  /// Sets the dump directory
  void setDumpDirectory(const QString& dirname);
  /// Sets the dump frame size
  void setDumpFrameSize(size_t width, size_t height);
  /// Sets the dump format
  void setDumpFormat(const QString& format);
  /// Dump all frames
  void setDumpAll(bool dumpAll);
  /// Rotate dumped frames
  void setRotateFrames(bool rotateFrames);
  /// Sets frame rotation
  void setFrameRotation(double yaw);
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Render the background
  void renderBackground();
  /// Render the fog
  void renderFog(double start, double end, double density);
  /// Render the ground
  void renderGround(double radius, double elevation, double angleStep, double
    rangeStep);
  /// Render the axes
  void renderAxes(double f64Length);
  /// Dump the frame
  void dumpFrame(const QString& format, int frame, size_t width, size_t height);
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Qt user interface
  Ui_ViewControl* mUi;
  /// Color palette
  Palette mPalette;
  /** @}
    */

protected slots:
  /** \name Qt slots
    @{
    */
  /// Dump frame
  void dumpFrame();
  /// Font browse clicked
  void fontBrowseClicked();
  /// Camera position changed
  void cameraPositionChanged();
  /// Camera view point changed
  void cameraViewpointChanged();
  /// Scene translation changed
  void sceneTranslationChanged();
  /// Scene rotation changed
  void sceneRotationChanged();
  /// Scene scale changed
  void sceneScaleChanged();
  /// Ground radius changed
  void groundRadiusChanged(double radius);
  /// Ground elevation changed
  void groundElevationChanged(double elevation);
  /// Show fog
  void showFogToggled(bool checked);
  /// Show ground
  void showGroundToggled(bool checked);
  /// Show axes
  void showAxesToggled(bool checked);
  /// Dump directory browse clicked
  void dumpDirBrowseClicked();
  /// Dump clicked
  void dumpClicked();
  /// Dump all toggled
  void dumpAllToggled(bool checked);
  /// Color changed
  void colorChanged(const QString& role, const QColor& color);
  /// Font changed
  void fontChanged(const QString& filename);
  /// Camera position changed
  void cameraPositionChanged(const std::vector<double>& position);
  /// Camera viewpoint changed
  void cameraViewpointChanged(const std::vector<double>& viewpoint);
  /// Scene translation changed
  void sceneTranslationChanged(const std::vector<double>& translation);
  /// Scene rotation changed
  void sceneRotationChanged(const std::vector<double>& rotation);
  /// Scene scale changed
  void sceneScaleChanged(double scale);
  /// Render the scene
  void render(GLView& view, Scene& scene);
  /** @}
    */

};

#endif
