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

#ifndef DEMCONTROL_H
#define DEMCONTROL_H

#include "data-structures/DEM.h"
#include "data-structures/PointCloud.h"
#include "visualization/Control.h"
#include "visualization/Singleton.h"
#include "visualization/GLView.h"
#include "visualization/Scene.h"

#include <QtCore/QString>
#include <QtGui/QColor>

class Ui_DEMControl;

class DEMControl :
  public Control,
  public Singleton<DEMControl> {
Q_OBJECT

public:
  DEMControl(bool bShowDEM = true);
  ~DEMControl();

  void setLineColor(const QColor& color);
  void setLineSize(double f64LineSize);
  void setShowDEM(bool bShowDEM);
  void setSmoothLines(bool bSmoothLines);

protected:
  void renderDEM(double f64Size, bool bSmooth);

  Ui_DEMControl* mpUi;
  Palette mPalette;
  DEM* mpDEM;
  const PointCloud* mpPointCloud;

protected slots:
  void colorChanged(const QString& role, const QColor& color);
  void lineSizeChanged(double f64LineSize);
  void showDEMToggled(bool bChecked);
  void smoothLinesToggled(bool bChecked);
  void pointCloudRead(const PointCloud* pPointCloud);
  void demChanged();
  void render(GLView& view, Scene& scene);

signals:
  void demUpdated(DEM* pDEM);

};

#endif // DEMCONTROL_H
