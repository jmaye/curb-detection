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

#include <unordered_map>

#include "visualization/PointViewer3d.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

PointViewer3d::PointViewer3d(const PointCloud<>::Container& data) {
  PointCloud<> pointCloud;
  for (auto it = data.cbegin(); it != data.cend(); ++it)
    pointCloud.insertPoint(*it);
  Colors::Color color;
  color.mRed = 0;
  color.mGreen = 0;
  color.mBlue = 1;
  mPointClouds.push_back(std::tuple<PointCloud<>, Colors::Color>(pointCloud,
    color));
  connect(&View3d::getInstance().getScene(), SIGNAL(render(View3d&, Scene3d&)),
    this, SLOT(render(View3d&, Scene3d&)));
  setBackgroundColor(Qt::white);
  setFogColor(Qt::white);
  setGroundColor(Qt::lightGray);
}

PointViewer3d::PointViewer3d(const
    std::vector<std::tuple<PointCloud<>::Point, size_t> >& data) {
  std::unordered_map<size_t, std::vector<PointCloud<>::Point> > points;
  for (auto it = data.cbegin(); it != data.cend(); ++it)
    points[std::get<1>(*it)].push_back(std::get<0>(*it));
  for (auto it = points.cbegin(); it != points.cend(); ++it) {
    PointCloud<> pointCloud;
    for (auto itP = it->second.cbegin(); itP != it->second.cend(); ++itP)
      pointCloud.insertPoint(*itP);
    mPointClouds.push_back(std::tuple<PointCloud<>, Colors::Color>(pointCloud,
      Colors::genColor(it->first)));
  }
  connect(&View3d::getInstance().getScene(), SIGNAL(render(View3d&, Scene&)),
    this, SLOT(render(View3d&, Scene&)));
  setBackgroundColor(Qt::white);
  setFogColor(Qt::white);
  setGroundColor(Qt::lightGray);
}

PointViewer3d::~PointViewer3d() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void PointViewer3d::setBackgroundColor(const QColor& color) {
  mPalette.setColor("Background", color);
}

void PointViewer3d::setFogColor(const QColor& color) {
  mPalette.setColor("Fog", color);
}

void PointViewer3d::setGroundColor(const QColor& color) {
  mPalette.setColor("Ground", color);
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void PointViewer3d::renderBackground() {
  glPushAttrib(GL_CURRENT_BIT);
  QColor backgroundColor = mPalette.getColor("Background");
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
    backgroundColor.blueF(), 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPopAttrib();
}

void PointViewer3d::renderFog(double start, double end, double density) {
  glPushAttrib(GL_CURRENT_BIT);
  QColor color = mPalette.getColor("Fog");
  float colorfv[] = {(float)color.redF(), (float)color.greenF(),
    (float)color.blueF(), 1.0};
  double scale = View3d::getInstance().getScene().getScale();
  double distance = View3d::getInstance().getCamera().getViewpointDistance();
  glFogi(GL_FOG_MODE, GL_LINEAR);
  glFogfv(GL_FOG_COLOR, colorfv);
  glFogf(GL_FOG_DENSITY, density);
  glHint(GL_FOG_HINT, GL_DONT_CARE);
  glFogf(GL_FOG_START, distance + start * scale);
  glFogf(GL_FOG_END, distance + end * scale);
  glPopAttrib();
}

void PointViewer3d::renderAxes(double length) {
  glPushAttrib(GL_CURRENT_BIT);
  glBegin(GL_LINES);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(length, 0.0, 0.0);
  glEnd();
  View3d::getInstance().render(length, 0.0, 0.0, "X", 0.2 * length, true, true,
    true);
  glBegin(GL_LINES);
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, length, 0.0);
  glEnd();
  View3d::getInstance().render(0.0, length, 0.0, "Y", 0.2 * length, true, true,
    true);
  glBegin(GL_LINES);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, length);
  glEnd();
  View3d::getInstance().render(0, 0, length, "Z", 0.2 * length, true, true,
    true);
  glPopAttrib();
}

void PointViewer3d::renderPoints(double size, bool smooth) {
  glPushAttrib(GL_CURRENT_BIT);
  if (size > 1.0)
    glPointSize(size);
  else
    glPointSize(1.0);
  if (smooth)
    glEnable(GL_POINT_SMOOTH);
  else
    glDisable(GL_POINT_SMOOTH);
  glBegin(GL_POINTS);
  for (auto it = mPointClouds.cbegin(); it != mPointClouds.cend(); ++it) {
    const Colors::Color& color = std::get<1>(*it);
    glColor3f(color.mRed, color.mGreen, color.mBlue);
    const PointCloud<>& pointCloud = std::get<0>(*it);
    for (auto itP = pointCloud.getPointBegin(); itP != pointCloud.getPointEnd();
        ++itP)
      glVertex3f((*itP)(0), (*itP)(1), (*itP)(2));
  }
  glEnd();
  glPointSize(1.0);
  glDisable(GL_POINT_SMOOTH);
  glPopAttrib();
}

void PointViewer3d::show() {
  mView.show();
}

void PointViewer3d::render(View3d& view, Scene3d& scene) {
  renderBackground();
  glEnable(GL_FOG);
  renderFog(10, 2.0 * 10, 1.0);
  renderAxes(2.5);
  renderPoints(1.0, true);
}
