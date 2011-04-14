#include "PointCloud.h"
#include "DEM.h"
#include "Window.h"
#include "ConnectivityBuilder.h"
#include "GraphSegmenter.h"
#include "LinearRegressor.h"
#include "DEMCRF.h"
#include "EM.h"
#include "BeliefPropagation.h"

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
  GraphSegmenter::segment(dem, edgeSet, labelsMap, supportsMap, 100);
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
  BeliefPropagation bp;
  cout << "BP creation: " << getMsCount() - f64Time << " [ms]" << endl;
  f64Time = getMsCount();
  bp.infer(dem, edgeSet, coeffsMatrix, variancesVector, weightsVector);
  cout << "BP inference: " << getMsCount() - f64Time << " [ms]" << endl;
  dem.setLabelsDist(bp);
//  f64Time = getMsCount();
//  DEMCRF crf(dem, edgeSet, coeffsMatrix, variancesVector, weightsVector);
//  cout << "CRF creation: " << getMsCount() - f64Time << " [ms]" << endl;
//  Vector nodesWeightsVector, edgesWeightsVector;
//  nodesWeightsVector.PushBack(1.0);
//  edgesWeightsVector.PushBack(1.0);
//  f64Time = getMsCount();
//  EM::run(crf, nodesWeightsVector, edgesWeightsVector, dem, coeffsMatrix,
//    variancesVector, weightsVector, 1);
//  cout << "EM: " << getMsCount() - f64Time << " [ms]" << endl;

  Window window(argc, argv);
  window.addPointCloud(pointCloud);
  window.addDEM(dem);
  window.addConnectivity(edgeSet, dem);
  window.setTranslation(0, -10, -60);
  window.setRotation(0, -90, 90);
  window.setVisibility(true);
  window.show();

  return 0;
}
