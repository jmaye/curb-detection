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

#include "visualization/PointViewer3d.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

PointViewer3d::PointViewer3d(const std::vector<Eigen::Matrix<double, 3, 1> >&
  data) :
  mData(data) {
  connect(&GLView::getInstance().getScene(), SIGNAL(render(GLView&, Scene&)),
    this, SLOT(render(GLView&, Scene&)));
  setBackgroundColor(Qt::white);
  setFogColor(Qt::white);
  setGroundColor(Qt::lightGray);
  setPointColor(Qt::blue);
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

void PointViewer3d::setPointColor(const QColor& color) {
  mPalette.setColor("Point", color);
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
  float colorfv[] = {color.redF(), color.greenF(), color.blueF(), 1.0};
  double scale = GLView::getInstance().getScene().getScale();
  double distance = GLView::getInstance().getCamera().getViewpointDistance();
  glFogi(GL_FOG_MODE, GL_LINEAR);
  glFogfv(GL_FOG_COLOR, colorfv);
  glFogf(GL_FOG_DENSITY, density);
  glHint(GL_FOG_HINT, GL_DONT_CARE);
  glFogf(GL_FOG_START, distance + start * scale);
  glFogf(GL_FOG_END, distance + end * scale);
  glPopAttrib();
}

void PointViewer3d::renderGround(double radius, double elevation, double
  angleStep, double rangeStep) {
  glPushAttrib(GL_CURRENT_BIT);
  glBegin(GL_LINES);
  GLView::getInstance().setColor(mPalette, "Ground");
  for (double angle = -M_PI; angle < M_PI; angle += angleStep) {
    glVertex3f(rangeStep * sin(angle), rangeStep * cos(angle), elevation);
    glVertex3f(radius * sin(angle), radius * cos(angle), elevation);
  }
  glEnd();
  for (double range = rangeStep; ; range += rangeStep) {
    if (range > radius)
      range = radius;
    glBegin(GL_LINE_STRIP);
    for (double angle = -M_PI; angle <= M_PI; angle += angleStep)
      for (double theta = angle; theta <= angle + angleStep;
        theta += angleStep / range)
        glVertex3f(range * sin(theta), range * cos(theta), elevation);
    glEnd();
    if (range == radius)
      break;
  }
  glPopAttrib();
}

void PointViewer3d::renderAxes(double length) {
  glPushAttrib(GL_CURRENT_BIT);
  glBegin(GL_LINES);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(length, 0.0, 0.0);
  glEnd();
  GLView::getInstance().render(length, 0.0, 0.0, "X", 0.2 * length, true, true,
    true);
  glBegin(GL_LINES);
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, length, 0.0);
  glEnd();
  GLView::getInstance().render(0.0, length, 0.0, "Y", 0.2 * length, true, true,
    true);
  glBegin(GL_LINES);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, length);
  glEnd();
  GLView::getInstance().render(0, 0, length, "Z", 0.2 * length, true, true,
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
  GLView::getInstance().setColor(mPalette, "Point");
  for (size_t i = 0; i < mData.size(); ++i)
    glVertex3f(mData[i](0), mData[i](1), mData[i](2));
  glEnd();
  glPointSize(1.0);
  glDisable(GL_POINT_SMOOTH);
  glPopAttrib();
}

void PointViewer3d::show() {
  mGLView.show();
}

void PointViewer3d::render(GLView& view, Scene& scene) {
  renderBackground();
  glEnable(GL_FOG);
  renderFog(10, 2.0 * 10, 1.0);
  renderGround(10, 0, 30.0 * M_PI / 180.0, 5.0);
  renderAxes(2.5);
  renderPoints(1.0, true);
}
