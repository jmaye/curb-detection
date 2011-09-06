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

/** \file GLView.h
    \brief This file contains the base OpenGL viewer
  */

#ifndef GLVIEW_H
#define GLVIEW_H

#include "base/Singleton.h"
#include "visualization/Palette.h"
#include "visualization/Camera.h"
#include "visualization/Scene.h"

#include <QtOpenGL/QGLWidget>
#include <QtGui/QColor>
#include <QtCore/QString>
#include <QtCore/QPoint>

#include <vector>

class FTPolygonFont;

/** The GLView class represents the base OpenGL viewer.
    \brief Base OpenGL viewer
  */
class GLView :
  public QGLWidget,
  public Singleton<GLView> {
Q_OBJECT
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  GLView(const GLView& other);
  /// Assignment operator
  GLView& operator = (const GLView& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the viewer
  GLView(QWidget* parent = 0);
  /// Destructor
  ~GLView();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the camera
  Camera& getCamera();
  /// Returns the camera
  const Camera& getCamera() const;
  /// Returns the scene
  Scene& getScene();
  /// Returns the scene
  const Scene& getScene() const;
  /// Sets a color
  void setColor(const QColor& color);
  /// Sets a color
  void setColor(const Palette& palette, const QString& role);
  /// Sets the font
  void setFont(const QString& filename);
  /// Returns the font
  const QString& getFont() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Unproject a point
  std::vector<double> unproject(const QPoint& point, double distance);
  /// Render the scene
  void render(double x, double y, double z, const QString& text,
    double scale = 1.0, bool faceX = false, bool faceY = false,
    bool faceZ = false);
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Mouse press event
  virtual void mousePressEvent(QMouseEvent* event);
  /// Mouse move event
  virtual void mouseMoveEvent(QMouseEvent* event);
  /// Mouse wheel event
  virtual void wheelEvent(QWheelEvent* event);
  /// Init the OpenGL engine
  virtual void initializeGL();
  /// Resize the OpenGL engine
  virtual void resizeGL(int width, int height);
  /// Paint the OpenGL engine
  virtual void paintGL();
  /// Paint event
  virtual void paintEvent(QPaintEvent* event);
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Filename for the font
  QString mFontFilename;
  /// Font object
  FTPolygonFont* mFont;
  /// Camera
  Camera mCamera;
  /// Scene
  Scene mScene;
  /// Mouse
  std::vector<int> mMouse;
  /// Viewport
  std::vector<int> mViewport;
  /// Projection
  std::vector<double> mProjection;
  /// Model view
  std::vector<double> mModelview;
  /** @}
    */

protected slots:
  /** \name Qt slots
    @{
    */
  /// Camera position changed
  void cameraPositionChanged(const std::vector<double>& position);
  /// Camera viewpoint changed
  void cameraViewpointChanged(const std::vector<double>& viewpoint);
  /// Camera range changed
  void cameraRangeChanged(const std::vector<double>& range);
  /// Scene translation changed
  void sceneTranslationChanged(const std::vector<double>& translation);
  /// Scene rotation changed
  void sceneRotationChanged(const std::vector<double>& rotation);
  /// Scene scale changed
  void sceneScaleChanged(double scale);
  /** @}
    */

signals:
  /** \name Qt signals
    @{
    */
  /// Font changed
  void fontChanged(const QString& filename);
  /// Updated signal
  void updated();
  /** @}
    */

};

#endif // GLVIEW_H
