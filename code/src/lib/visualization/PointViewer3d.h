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

#include <vector>
#include <tuple>

#include "data-structures/PointCloud.h"
#include "visualization/View3d.h"
#include "visualization/Scene3d.h"
#include "utils/Colors.h"

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
  PointViewer3d(const PointCloud<>::Container& data);
  /// Constructs viewer with points with different colors
  PointViewer3d(const std::vector<std::tuple<PointCloud<>::Point, size_t> >&
    data);
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
  /// Render axes
  void renderAxes(double length);
  /// Render the points
  void renderPoints(double size, bool smooth);
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// 3d view
  View3d mView;
  /// Point cloud to be displayed
  std::vector<std::tuple<PointCloud<>, Colors::Color> > mPointClouds;
  /// Palette
  Palette mPalette;
  /** @}
    */

protected slots:
  /** \name Protected slots
    @{
    */
  /// Rendering loop
  void render(View3d& view, Scene3d& scene);
  /** @}
    */

};

#endif // POINTVIEWER3D_H
