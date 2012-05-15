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

/** \file gui.cpp
    \brief This file is a GUI for curb detection qualitative analysis.
  */

#include <QtGui/QApplication>

#include "visualization/MainWindow.h"
#include "visualization/View3d.h"
#include "visualization/View3dControl.h"
#include "visualization/PointCloudControl.h"
#include "visualization/DEMControl.h"
#include "visualization/SegmentationControl.h"
#include "visualization/MLControl.h"
#include "visualization/BPControl.h"
#include "visualization/MLBPControl.h"
#include "visualization/CurbsControl.h"
#include "visualization/EvaluatorControl.h"

int main (int argc, char** argv) {
  QApplication application(argc, argv);
  MainWindow mainWindow;
  mainWindow.addView(QString("3d"), View3d::getInstance());
  mainWindow.addControl("View", View3dControl::getInstance());
  PointCloudControl pointCloudControl(true);
  mainWindow.addControl("PointCloud", pointCloudControl);
  DEMControl demControl(true);
  mainWindow.addControl("DEM", demControl);
  SegmentationControl segControl(false);
  mainWindow.addControl("Segmentation", segControl);
  MLControl mlControl(false);
  mainWindow.addControl("ML", mlControl);
  BPControl bpControl(true);
  mainWindow.addControl("BP", bpControl);
  MLBPControl mlbpControl(true);
  mainWindow.addControl("ML-BP", mlbpControl);
  CurbsControl curbsControl(true);
  mainWindow.addControl("Curbs", curbsControl);
  EvaluatorControl evaluatorControl(false);
  mainWindow.addControl("Evaluation", evaluatorControl);
  mainWindow.show();
  return application.exec();
}
