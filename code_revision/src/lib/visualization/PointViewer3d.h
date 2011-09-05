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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file PointViewer3d.h
    \brief This file contains a plotting tool 3d points
  */

#ifndef POINTVIEWER3D_H
#define POINTVIEWER3D_H

#include "visualization/GLView.h"

#include <Eigen/Core>

/** The PointViewer3d class is a plotting tool 3d points.
    \brief 3d points viewer
  */
class PointViewer3d :
  public QObject {
Q_OBJECT
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  PointViewer3d(const PointViewer3d& other);
  /// Assignment operator
  PointViewer3d& operator = (const PointViewer3d& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs viewer with points
  PointViewer3d(const std::vector<Eigen::Matrix<double, 3, 1> >& data);
  /// Destructor
  virtual ~PointViewer3d();
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
  /// Sets the point color
  void setPointColor(const QColor& color);
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Show the points
  void show();
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Render background
  void renderBackground();
  /// Render fog
  void renderFog(double start, double end, double density);
  /// Render ground
  void renderGround(double radius, double elevation, double angleStep,
    double rangeStep);
  /// Render axes
  void renderAxes(double length);
  /// Render the points
  void renderPoints(double size, bool smooth);
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// GL viewer
  GLView mGLView;
  /// Points to be displayed
  std::vector<Eigen::Matrix<double, 3, 1> > mData;
  /// Palette
  Palette mPalette;
  /** @}
    */

protected slots:
  /** \name Protected slots
    @{
    */
  /// Rendering loop
  void render(GLView& view, Scene& scene);
  /** @}
    */

};

#endif // POINTVIEWER3D_H
