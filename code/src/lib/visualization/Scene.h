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

/** \file Scene.h
    \brief This file contains a scene implementation for OpenGL
  */

#ifndef SCENE_H
#define SCENE_H

#include <QtCore/QObject>

#include <vector>

class GLView;

/** The Scene class represents a scene in OpenGL.
    \brief Scene for OpenGL
  */
class Scene :
  public QObject {
Q_OBJECT
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  Scene(const Scene& other);
  /// Assignment operator
  Scene& operator = (const Scene& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  Scene();
  /// Destructor
  ~Scene();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the scene translation
  void setTranslation(double x, double y, double z);
  /// Returns the scene translation
  const std::vector<double>& getTranslation() const;
  /// Sets the scene rotation
  void setRotation(double yaw, double pitch, double roll);
  /// Returns the scene rotation
  const std::vector<double>& getRotation() const;
  /// Sets the scene scale
  void setScale(double scale);
  /// Returns the scene scale
  double getScale() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Setup OpenGL
  void setup(GLView& view);
  /// Render the scene
  void render(GLView& view);
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Correct angles
  double correctAngle(double angle) const;
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Scene translation
  std::vector<double> mTranslation;
  /// Scene rotation
  std::vector<double> mRotation;
  /// Scene scale
  double mScale;
  /** @}
    */

signals:
  /** \name Qt signals
    @{
    */
  /// Translation has changed
  void translationChanged(const std::vector<double>& translation);
  /// Rotation has changed
  void rotationChanged(const std::vector<double>& rotation);
  /// Scale has changed
  void scaleChanged(double scale);
  /// Render the scene
  void render(GLView& view, Scene& scene);
  /** @}
    */

};

#endif // SCENE_H
