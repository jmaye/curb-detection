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

#ifndef SCENE_H
#define SCENE_H

#include <QtCore/QObject>

#include <vector>

class GLView;

class Scene :
  public QObject {
Q_OBJECT

public:
  Scene();
  ~Scene();

  void setTranslation(double f64X, double f64Y, double f64Z);
  const std::vector<double>& getTranslation() const;
  void setRotation(double f64Yaw, double f64Pitch, double f64Roll);
  const std::vector<double>& getRotation() const;
  void setScale(double f64Scale);
  double getScale() const;

  void setup(GLView& view);
  void render(GLView& view);

protected:
  double correctAngle(double f64Angle) const;

  std::vector<double> mTranslationVector;
  std::vector<double> mRotationVector;
  double mf64Scale;

signals:
  void translationChanged(const std::vector<double>& translationVector);
  void rotationChanged(const std::vector<double>& rotationVector);
  void scaleChanged(double f64Scale);
  void render(GLView& view, Scene& scene);

};

#endif
