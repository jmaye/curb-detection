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

#ifndef VIEWCONTROL_H
#define VIEWCONTROL_H

#include "visualization/Control.h"
#include "visualization/Singleton.h"
#include "visualization/GLView.h"
#include "visualization/Scene.h"

#include <QtCore/QString>
#include <QtGui/QColor>

#include <vector>

class Ui_ViewControl;

class ViewControl :
  public Control,
  public Singleton<ViewControl> {
Q_OBJECT

public:
  ViewControl(bool bShowFog = true, bool bShowGround = true,
    bool bShowAxes = true);
  ~ViewControl();

  void setBackgroundColor(const QColor& color);
  void setFogColor(const QColor& color);
  void setGroundColor(const QColor& color);
  void setGroundRadius(double f64Radius);
  void setGroundElevation(double f64Elevation);
  void setShowFog(bool bShowFog);
  void setShowGround(bool bShowGround);
  void setShowAxes(bool bShowAxes);
  void setDumpDirectory(const QString& dirname);
  void setDumpFrameSize(size_t width, size_t height);
  void setDumpFormat(const QString& format);
  void setDumpAll(bool bDumpAll);
  void setRotateFrames(bool bRotateFrames);
  void setFrameRotation(double f64Yaw);

public slots:
  void dumpFrame();

protected:
  void renderBackground();
  void renderFog(double f64Start, double f64End, double f64Density);
  void renderGround(double f64Radius, double f64Elevation, double f64AngleStep,
    double f64RangeStep);
  void renderAxes(double f64Length);
  void dumpFrame(const QString& format, int i32Frame, size_t width,
    size_t height);

  Ui_ViewControl* mpUi;
  Palette mPalette;

protected slots:
  void fontBrowseClicked();
  void cameraPositionChanged();
  void cameraViewpointChanged();
  void sceneTranslationChanged();
  void sceneRotationChanged();
  void sceneScaleChanged();
  void groundRadiusChanged(double f64Radius);
  void groundElevationChanged(double f64Elevation);
  void showFogToggled(bool bChecked);
  void showGroundToggled(bool bChecked);
  void showAxesToggled(bool bChecked);
  void dumpDirBrowseClicked();
  void dumpClicked();
  void dumpAllToggled(bool bChecked);
  void colorChanged(const QString& role, const QColor& color);
  void fontChanged(const QString& filename);
  void cameraPositionChanged(const std::vector<double>& positionVector);
  void cameraViewpointChanged(const std::vector<double>& viewpointVector);
  void sceneTranslationChanged(const std::vector<double>& translationVector);
  void sceneRotationChanged(const std::vector<double>& rotationVector);
  void sceneScaleChanged(double f64Scale);
  void render(GLView& view, Scene& scene);

};

#endif
