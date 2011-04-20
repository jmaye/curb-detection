#include "PointCloud.h"
#include "DEM.h"
#include "Window.h"
#include "ConnectivityBuilder.h"
#include "ConnectivityMap.h"
#include "GraphSegmenter.h"
#include "LinearRegressor.h"
#include "EM.h"
#include "CurbFinder.h"
#include "CurbMap.h"

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
  DEM dem(pointCloud, 0.15, 0.15, 30, 30, 1.55, -0.5, -2, 1);
  cout << "Creating DEM: " << getMsCount() - f64Time << " [ms]" << endl;
  multiset<Edge, EdgeCompare> edgeSet;
  f64Time = getMsCount();
  ConnectivityBuilder::build(dem, edgeSet);
  cout << "Building connectivity: " << getMsCount() - f64Time << " [ms]"
       << endl;
  map<pair<uint32_t, uint32_t>, uint32_t> labelsMap;
  map<uint32_t, uint32_t> supportsMap;
  f64Time = getMsCount();
  GraphSegmenter::segment(dem, edgeSet, labelsMap, supportsMap, 200);
  cout << "Graph-based segmentation: " << getMsCount() - f64Time << " [ms]"
       << endl;
  dem.setInitialLabels(labelsMap, supportsMap);
  vector<vector<double> > coeffsMatrix;
  vector<double> variancesVector;
  vector<double> weightsVector;
  f64Time = getMsCount();
  LinearRegressor::estimate(dem, coeffsMatrix, variancesVector, weightsVector);
  cout << "Initial linear regression: " << getMsCount() - f64Time << " [ms]"
       << endl;
  f64Time = getMsCount();
  EM::run(dem, edgeSet, coeffsMatrix, variancesVector, weightsVector, 15, 1e-6,
    10000, 1e-9);
  cout << "EM: " << getMsCount() - f64Time << " [ms]" << endl;
  ConnectivityMap connectivityMap(dem, edgeSet);
  CurbMap curbMap;
  CurbFinder::find(dem, edgeSet, curbMap);

  Window window(argc, argv);
  window.addPointCloud(pointCloud);
  window.addDEM(dem);
  window.addConnectivity(connectivityMap);
  window.addCurbMap(curbMap);
  window.setTranslation(0, -10, -60);
  window.setRotation(0, -90, 90);
  window.setVisibility(true);
  window.show();

  return 0;
}
