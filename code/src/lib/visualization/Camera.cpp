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

#include "visualization/GLView.h"

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Camera::Camera(double f64X, double f64Y, double f64Z, double f64Near,
  double f64Far) :
  mPositionVector(3, 0.0),
  mViewpointVector(3, 0.0),
  mRangeVector(2, 0.0),
  mProjectionVector(2, 0.0) {
  setPosition(f64X, f64Y, f64Z);
  setRange(f64Near, f64Far);
}

Camera::~Camera() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void Camera::setPosition(double f64X, double f64Y, double f64Z) {
  if ((f64X != mPositionVector[0]) || (f64Y != mPositionVector[1]) ||
    (f64Z != mPositionVector[2])) {
    mPositionVector[0] = f64X;
    mPositionVector[1] = f64Y;
    mPositionVector[2] = f64Z;

    emit positionChanged(mPositionVector);
  }
}

const std::vector<double>& Camera::getPosition() const {
  return mPositionVector;
}

void Camera::setViewpoint(double f64X, double f64Y, double f64Z) {
  if ((f64X != mViewpointVector[0]) || (f64Y != mViewpointVector[1]) ||
    (f64Z != mViewpointVector[2])) {
    mViewpointVector[0] = f64X;
    mViewpointVector[1] = f64Y;
    mViewpointVector[2] = f64Z;

    emit viewpointChanged(mViewpointVector);
  }
}

const std::vector<double>& Camera::getViewpoint() const {
  return mViewpointVector;
}

void Camera::setRange(double f64Near, double f64Far) {
  if ((f64Near != mRangeVector[0]) || (f64Far != mRangeVector[1])) {
    mRangeVector[0] = f64Near;
    mRangeVector[1] = f64Far;

    emit rangeChanged(mRangeVector);
  }
}

const std::vector<double>& Camera::getRange() const {
  return mRangeVector;
}

double Camera::getViewpointDistance() const {
  std::vector<double> lookatVector(3, 0.0);

  lookatVector[0] = mPositionVector[0] - mViewpointVector[0];
  lookatVector[1] = mPositionVector[1] - mViewpointVector[1];
  lookatVector[2] = mPositionVector[2] - mViewpointVector[2];
  
  return sqrt(lookatVector[0] * lookatVector[0] + lookatVector[1] *
    lookatVector[1] + lookatVector[2] * lookatVector[2]);
}

const std::vector<double>& Camera::getProjection() const {
  return mProjectionVector;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void Camera::setup(GLView& view, double f64Width, double f64Height) {
  double f64Aspect = f64Width / f64Height;
  double f64Near = mRangeVector[0];
  double f64Far = mRangeVector[1];
  double f64Fov = 45.0 * M_PI / 180.0;

  double f64Top = tan(f64Fov * 0.5) * f64Near;
  double f64Bottom = -f64Top;
  double f64Left = f64Aspect * f64Bottom;
  double f64Right = f64Aspect * f64Top;

  mProjectionVector[0] = 2.0 * f64Near / (f64Right - f64Left);
  mProjectionVector[1] = 2.0 * f64Near / (f64Top - f64Bottom);

  glMatrixMode(GL_PROJECTION);
  glFrustum(f64Left, f64Right, f64Bottom, f64Top, f64Near, f64Far);

  glMatrixMode(GL_MODELVIEW);
  gluLookAt(
    mPositionVector[0], mPositionVector[1], mPositionVector[2],
    mViewpointVector[0], mViewpointVector[1], mViewpointVector[2],
    0.0, 0.0, 1.0);
}
