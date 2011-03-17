#include "PointCloud.h"
#include "DEM.h"
#include "Window.h"
#include "ConnectivityBuilder.h"
#include "GraphSegmenter.h"

#include <iostream>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

int main(int argc ,char** argv) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << "<pointCloudFile>" << endl;
    return -1;
  }
  ifstream pointCloudFile(argv[1]);
  PointCloud pointCloud;
  pointCloudFile >> pointCloud;
  DEM dem(pointCloud, 0.4, 0.4, 20, 30);
  multiset<Edge, EdgeCompare> edgeSet;
  ConnectivityBuilder::build(dem, edgeSet);
  vector<uint32_t> labelsVector;
  GraphSegmenter::segment(dem.getCellsVector(), edgeSet, labelsVector, 400);
  for (uint32_t i = 0; i < labelsVector.size(); i++) {
    if (i % 20 == 0)
      cout << endl;
    cout << labelsVector[i] << " ";
  }
  dem.setLabelsVector(labelsVector);

  Window window(argc, argv);
  window.addPointCloud(pointCloud);
  window.addDEM(dem);
  window.setTranslation(0, -10, -60);
  window.setRotation(0, -90, 90);
  window.setVisibility(true);
  window.show();

  return 0;
}
