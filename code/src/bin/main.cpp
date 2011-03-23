#include "PointCloud.h"
#include "DEM.h"
#include "Window.h"
#include "ConnectivityBuilder.h"
#include "GraphSegmenter.h"
#include "LinearRegressor.h"

#include <iostream>
#include <fstream>
#include <set>
#include <vector>

#include <sys/time.h>

using namespace std;

static uint32_t getMsCount() {
  struct timeval now;
  gettimeofday(&now, 0L);
  return ((now.tv_sec * 1000000) + (now.tv_usec)) / 1000;
}

int main(int argc ,char** argv) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << "<pointCloudFile>" << endl;
    return -1;
  }
  double f64Time;
  ifstream pointCloudFile(argv[1]);
  PointCloud pointCloud;
  f64Time = getMsCount();
  pointCloudFile >> pointCloud;
  cout << "Reading point cloud: " << getMsCount() - f64Time << " [ms]" << endl;
  f64Time = getMsCount();
  DEM dem(pointCloud, 0.4, 0.4, 20, 30);
  cout << "Creating DEM: " << getMsCount() - f64Time << " [ms]" << endl;
  multiset<Edge, EdgeCompare> edgeSet;
  f64Time = getMsCount();
  ConnectivityBuilder::build(dem, edgeSet);
  cout << "Building connectivity: " << getMsCount() - f64Time << " [ms]" << endl;
  vector<uint32_t> labelsVector;
  map<uint32_t, uint32_t> supportsMap;
  f64Time = getMsCount();
  GraphSegmenter::segment(dem.getCellsVector(), edgeSet, labelsVector,
    supportsMap, 400);
  cout << "Graph-based segmentation: " << getMsCount() - f64Time << " [ms]" << endl;
  f64Time = getMsCount();
  dem.setInitialLabelsVector(labelsVector, supportsMap);
  cout << "Setting initial labels: " << getMsCount() - f64Time << " [ms]" << endl;
  vector<vector<double> > coeffsMatrix;
  vector<double> variancesVector;
  f64Time = getMsCount();
  LinearRegressor::estimate(dem, coeffsMatrix, variancesVector);
  cout << "Linear regression: " << getMsCount() - f64Time << " [ms]" << endl;

  Window window(argc, argv);
  window.addPointCloud(pointCloud);
  window.addDEM(dem);
  window.setTranslation(0, -10, -60);
  window.setRotation(0, -90, 90);
  window.setVisibility(true);
  window.show();

  return 0;
}
