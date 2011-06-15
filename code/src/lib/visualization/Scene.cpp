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

#include "visualization/Scene.h"

#include "visualization/GLView.h"

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Scene::Scene() :
  mTranslationVector(3, 0.0),
  mRotationVector(3, 0.0),
  mf64Scale(1.0) {
  setTranslation(0.0, 0.0, 0.0);
  setRotation(-10.0 * M_PI / 180.0, -5.0 * M_PI / 180.0, 0.0);
  setScale(1.0);
}

Scene::~Scene() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void Scene::setTranslation(double f64X, double f64Y, double f64Z) {
  if ((f64X != mTranslationVector[0]) || (f64Y != mTranslationVector[1]) ||
      (f64Z != mTranslationVector[2])) {
    mTranslationVector[0] = f64X;
    mTranslationVector[1] = f64Y;
    mTranslationVector[2] = f64Z;

    emit translationChanged(mTranslationVector);
  }
}

const std::vector<double>& Scene::getTranslation() const {
  return mTranslationVector;
}

void Scene::setRotation(double f64Yaw, double f64Pitch, double f64Roll) {
  if ((f64Yaw != mRotationVector[0]) || (f64Pitch != mRotationVector[1]) ||
      (f64Roll != mRotationVector[2])) {
    mRotationVector[0] = correctAngle(f64Yaw);
    mRotationVector[1] = correctAngle(f64Pitch);
    mRotationVector[2] = correctAngle(f64Roll);

    emit rotationChanged(mRotationVector);
  }
}

const std::vector<double>& Scene::getRotation() const {
  return mRotationVector;
}

void Scene::setScale(double f64Scale) {
  if (this->mf64Scale != f64Scale) {
    this->mf64Scale = f64Scale;

    emit scaleChanged(this->mf64Scale);
  }
}

double Scene::getScale() const {
  return mf64Scale;
}

/******************************************************************************/
/*  Methods                                                                   */
/******************************************************************************/

void Scene::setup(GLView& view) {
  glMatrixMode(GL_MODELVIEW);
  glScalef(mf64Scale, mf64Scale, mf64Scale);
  glRotatef(mRotationVector[2] * 180.0 / M_PI, 1, 0, 0);
  glRotatef(mRotationVector[1] * 180.0 / M_PI, 0, 1, 0);
  glRotatef(mRotationVector[0] * 180.0 / M_PI, 0, 0, 1);
  glTranslatef(mTranslationVector[0], mTranslationVector[1],
    mTranslationVector[2]);
}

void Scene::render(GLView& view) {
  emit render(view, *this);
}

double Scene::correctAngle(double f64Angle) const {
  if (f64Angle >= 0.0)
    while (f64Angle >= M_PI) f64Angle -= 2.0 * M_PI;
  else
    while (f64Angle < -M_PI) f64Angle += 2.0 * M_PI;

  return f64Angle;
}
