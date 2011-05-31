#include "visualization/MainWindow.h"
#include "visualization/ViewControl.h"
#include "visualization/PointCloudControl.h"
#include "visualization/DEMControl.h"
#include "visualization/SegmenterControl.h"
#include "visualization/EMControl.h"

#include <QtGui/QApplication>

int main (int argc, char **argv) {
  QApplication application(argc, argv);
  MainWindow mainWindow;
  ViewControl viewControl;
  PointCloudControl pointCloudControl(false);
  DEMControl demControl(false);
  SegmenterControl segmenterControl(false);
  EMControl emControl(false);

  if (argc > 1)
    pointCloudControl.setLogFilename(argv[1]);

  mainWindow.addControl("View", viewControl);
  mainWindow.addControl("PointCloud", pointCloudControl);
  mainWindow.addControl("DEM", demControl);
  mainWindow.addControl("Segmenter", segmenterControl);
  mainWindow.addControl("EM", emControl);
  mainWindow.show();

  return application.exec();
}
