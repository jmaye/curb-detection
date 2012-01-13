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

#include "visualization/MainWindow.h"
#include "visualization/ViewControl.h"
#include "visualization/PointCloudControl.h"
#include "visualization/DEMControl.h"
#include "visualization/SegmentationControl.h"
#include "visualization/MLControl.h"
#include "visualization/BPControl.h"
#include "visualization/MLBPControl.h"
#include "visualization/CurbsControl.h"

#include <QtGui/QApplication>

int main (int argc, char** argv) {
  QApplication application(argc, argv);
  MainWindow mainWindow;
  ViewControl viewControl;
  PointCloudControl pointCloudControl(true);
  DEMControl demControl(true);
  SegmentationControl segControl(true);
  MLControl mlControl(true);
  BPControl bpControl(true);
  MLBPControl mlbpControl(true);
  CurbsControl curbsControl(true);
  if (argc > 1)
    pointCloudControl.setLogFilename(argv[1]);
  mainWindow.addControl("View", viewControl);
  mainWindow.addControl("PointCloud", pointCloudControl);
  mainWindow.addControl("DEM", demControl);
  mainWindow.addControl("Segmentation", segControl);
  mainWindow.addControl("ML", mlControl);
  mainWindow.addControl("BP", bpControl);
  mainWindow.addControl("MLBP", mlbpControl);
  mainWindow.addControl("Curbs", curbsControl);
  mainWindow.show();
  return application.exec();
}
