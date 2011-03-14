#include "PointCloud.h"
#include "DEM.h"
#include "Window.h"

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc ,char** argv) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << "<pointCloudFile>" << endl;
    return -1;
  }
  ifstream pointCloudFile(argv[1]);
  PointCloud pointCloud;
  pointCloudFile >> pointCloud;
  DEM dem(pointCloud, 0.4, 0.4, 20, 20, 1, 10, -10);
  Window window(argc, argv);
  window.addPointCloud(pointCloud);
  window.addDEM(dem);
  window.createGlLists();
  window.setTranslation(0, -10, -60);
  window.setRotation(0, -90, 90);
  window.setVisibility(true);
  window.show();

  return 0;
}
