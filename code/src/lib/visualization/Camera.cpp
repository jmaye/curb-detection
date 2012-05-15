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

#include "visualization/Camera.h"

#include <cmath>

#include "visualization/View3d.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Camera::Camera(double x, double y, double z, double near, double far) :
    mPosition(3, 0.0),
    mViewpoint(3, 0.0),
    mRange(2, 0.0),
    mProjection(2, 0.0) {
    setPosition(x, y, z);
    setRange(near, far);
}

Camera::~Camera() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void Camera::setPosition(double x, double y, double z) {
  if ((x != mPosition[0]) || (y != mPosition[1]) || (z != mPosition[2])) {
    mPosition[0] = x;
    mPosition[1] = y;
    mPosition[2] = z;
    emit positionChanged(mPosition);
  }
}

const std::vector<double>& Camera::getPosition() const {
  return mPosition;
}

void Camera::setViewpoint(double x, double y, double z) {
  if ((x != mViewpoint[0]) || (y != mViewpoint[1]) || (z != mViewpoint[2])) {
    mViewpoint[0] = x;
    mViewpoint[1] = y;
    mViewpoint[2] = z;
    emit viewpointChanged(mViewpoint);
  }
}

const std::vector<double>& Camera::getViewpoint() const {
  return mViewpoint;
}

void Camera::setRange(double near, double far) {
  if ((near != mRange[0]) || (far != mRange[1])) {
    mRange[0] = near;
    mRange[1] = far;
    emit rangeChanged(mRange);
  }
}

const std::vector<double>& Camera::getRange() const {
  return mRange;
}

double Camera::getViewpointDistance() const {
  std::vector<double> lookat(3, 0.0);
  lookat[0] = mPosition[0] - mViewpoint[0];
  lookat[1] = mPosition[1] - mViewpoint[1];
  lookat[2] = mPosition[2] - mViewpoint[2];
  return sqrt(lookat[0] * lookat[0] + lookat[1] * lookat[1] + lookat[2] *
    lookat[2]);
}

const std::vector<double>& Camera::getProjection() const {
  return mProjection;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void Camera::setup(View3d& view, double width, double height) {
  double aspect = width / height;
  double near = mRange[0];
  double far = mRange[1];
  double fov = 45.0 * M_PI / 180.0;
  double top = tan(fov * 0.5) * near;
  double bottom = -top;
  double left = aspect * bottom;
  double right = aspect * top;
  mProjection[0] = 2.0 * near / (right - left);
  mProjection[1] = 2.0 * near / (top - bottom);
  glMatrixMode(GL_PROJECTION);
  glFrustum(left, right, bottom, top, near, far);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(mPosition[0], mPosition[1], mPosition[2], mViewpoint[0],
    mViewpoint[1], mViewpoint[2], 0.0, 0.0, 1.0);
}
