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

#include "visualization/Scene3d.h"

#include <cmath>

#include "visualization/View3d.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Scene3d::Scene3d() :
    mTranslation(3, 0.0),
    mRotation(3, 0.0),
    mScale(1.0) {
  setTranslation(0.0, 0.0, 0.0);
  setRotation(-10.0 * M_PI / 180.0, -5.0 * M_PI / 180.0, 0.0);
  setScale(1.0);
}

Scene3d::~Scene3d() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void Scene3d::setTranslation(double x, double y, double z) {
  if ((x != mTranslation[0]) || (y != mTranslation[1]) ||
      (z != mTranslation[2])) {
    mTranslation[0] = x;
    mTranslation[1] = y;
    mTranslation[2] = z;
    emit translationChanged(mTranslation);
  }
}

const std::vector<double>& Scene3d::getTranslation() const {
  return mTranslation;
}

void Scene3d::setRotation(double yaw, double pitch, double roll) {
  if ((yaw != mRotation[0]) || (pitch != mRotation[1]) ||
      (roll != mRotation[2])) {
    mRotation[0] = correctAngle(yaw);
    mRotation[1] = correctAngle(pitch);
    mRotation[2] = correctAngle(roll);
    emit rotationChanged(mRotation);
  }
}

const std::vector<double>& Scene3d::getRotation() const {
  return mRotation;
}

void Scene3d::setScale(double scale) {
  if (mScale != scale) {
    mScale = scale;
    emit scaleChanged(mScale);
  }
}

double Scene3d::getScale() const {
  return mScale;
}

/******************************************************************************/
/*  Methods                                                                   */
/******************************************************************************/

void Scene3d::setup(View3d& view) {
  glMatrixMode(GL_MODELVIEW);
  glScalef(mScale, mScale, mScale);
  glRotatef(mRotation[2] * 180.0 / M_PI, 1, 0, 0);
  glRotatef(mRotation[1] * 180.0 / M_PI, 0, 1, 0);
  glRotatef(mRotation[0] * 180.0 / M_PI, 0, 0, 1);
  glTranslatef(mTranslation[0], mTranslation[1], mTranslation[2]);
}

void Scene3d::render(View3d& view) {
  emit render(view, *this);
}

double Scene3d::correctAngle(double angle) const {
  if (angle >= 0.0)
    while (angle >= M_PI) angle -= 2.0 * M_PI;
  else
    while (angle < -M_PI) angle += 2.0 * M_PI;
  return angle;
}
