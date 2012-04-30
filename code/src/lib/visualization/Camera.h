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

/** \file Camera.h
    \brief This file contains a camera implementation for OpenGL
  */

#ifndef CAMERA_H
#define CAMERA_H

#include <vector>

#include <QtCore/QObject>

class GLView;

/** The Camera class represents a camera in OpenGL.
    \brief Camera for OpenGL
  */
class Camera :
  public QObject {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  Camera(const Camera& other);
  /// Assignment operator
  Camera& operator = (const Camera& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs camera from parameters
  Camera(double x = -20.0, double y = 0.0, double z = 0.0, double near = 0.1,
    double far = 1000.0);
  /// Destructor
  ~Camera();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets position of the camera
  void setPosition(double x, double y, double z);
  /// Returns position of the camera
  const std::vector<double>& getPosition() const;
  /// Sets viewpoint of the camera
  void setViewpoint(double x, double y, double z);
  /// Returns viewpoint of the camera
  const std::vector<double>& getViewpoint() const;
  /// Sets range of the camera
  void setRange(double near, double far);
  /// Returns range of the camera
  const std::vector<double>& getRange() const;
  /// Returns projection of the camera
  const std::vector<double>& getProjection() const;
  /// Returns viewpoint distance of the camera
  double getViewpointDistance() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Setup the camera
  void setup(GLView& view, double width, double height);
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Position of the camera
  std::vector<double> mPosition;
  /// Viewpoint of the camera
  std::vector<double> mViewpoint;
  /// Range of the camera
  std::vector<double> mRange;
  /// Projection of the camera
  std::vector<double> mProjection;
  /** @}
    */

signals:
  /** \name Qt signals
    @{
    */
  /// Camera position updated
  void positionChanged(const std::vector<double>& position);
  /// Camera viewpoint updated
  void viewpointChanged(const std::vector<double>& viewpoint);
  /// Camera range updated
  void rangeChanged(const std::vector<double>& range);
  /** @}
    */

};

#endif // CAMERA_H
