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

/** \file Scene3d.h
    \brief This file contains a 3d scene implementation
  */

#ifndef SCENE3D_H
#define SCENE3D_H

#include <vector>

#include <QtCore/QObject>

class View3d;

/** The Scene3d class represents a 3d scene.
    \brief 3d scene
  */
class Scene3d :
  public QObject {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  Scene3d(const Scene3d& other);
  /// Assignment operator
  Scene3d& operator = (const Scene3d& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  Scene3d();
  /// Destructor
  virtual ~Scene3d();
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
  /// Setup view
  void setup(View3d& view);
  /// Render the scene
  void render(View3d& view);
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
  void render(View3d& view, Scene3d& scene);
  /** @}
    */

};

#endif // SCENE3D_H
