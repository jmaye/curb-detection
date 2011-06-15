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

#ifndef POINTCLOUDCONTROL_H
#define POINTCLOUDCONTROL_H

#include "data-structures/PointCloud.h"
#include "visualization/Control.h"
#include "visualization/Singleton.h"
#include "visualization/GLView.h"
#include "visualization/Scene.h"

#include <QtCore/QString>
#include <QtGui/QColor>

class Ui_PointCloudControl;

class PointCloudControl :
  public Control,
  public Singleton<PointCloudControl> {
Q_OBJECT

public:
  PointCloudControl(bool bShowPoints = true);
  ~PointCloudControl();

  void setPointColor(const QColor& color);
  void setPointSize(double f64PointSize);
  void setShowPoints(bool bShowPoints);
  void setSmoothPoints(bool bSmoothPoints);
  void setLogFilename(const QString& filename);

protected:
  void renderPoints(double f64Size, bool bSmooth);

  Ui_PointCloudControl* mpUi;
  Palette mPalette;
  PointCloud mPointCloud;

protected slots:
  void logBrowseClicked();
  void colorChanged(const QString& role, const QColor& color);
  void pointSizeChanged(double f64PointSize);
  void showPointsToggled(bool bChecked);
  void smoothPointsToggled(bool bChecked);
  void render(GLView& view, Scene& scene);

signals:
  void pointCloudRead(const PointCloud* pPointCloud);

};

#endif // POINTCLOUDCONTROL_H
