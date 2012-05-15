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

#include <ANN/ANN.h>

#include "statistics/Randomizer.h"
#include "exceptions/BadArgumentException.h"

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

template <typename T, size_t M>
size_t KMeansClustering<T, M>::cluster(const
    std::vector<Eigen::Matrix<T, M, 1> >& data,
    std::vector<Eigen::Matrix<T, M, 1> >& clusterCenters,
    std::vector<std::vector<size_t> >& clusterToData, std::vector<size_t>&
    dataToCluster, size_t k, size_t maxIterations, double tol, bool debug) {

  if (k == 0)
    throw BadArgumentException<size_t>(k,
      "KMeansClustering::cluster(): k must be greater than 0",
      __FILE__, __LINE__);

  if (data.size() == 0)
    throw BadArgumentException<size_t>(data.size(),
      "KMeansClustering::cluster(): input points vector is empty",
      __FILE__, __LINE__);

  size_t dim = data[0].size();

  ANNpointArray clusterCentersANN = annAllocPts(k, dim);

  Randomizer<size_t> randomizer;

  for (size_t i = 0; i < k; ++i) {
    size_t idx = randomizer.sampleUniform(0, data.size() - 1);
    for (size_t j = 0; j < dim; ++j)
      clusterCentersANN[i][j] = data[idx](j);
  }

  size_t iteration = 0;

  ANNidxArray idx = new ANNidx[1];
  ANNdistArray dist = new ANNdist[1];

  clusterCenters.clear();
  clusterCenters.resize(k);

  std::vector<Eigen::Matrix<T, M, 1> > clusterCentersOld;
  clusterCentersOld.resize(k);

  while (iteration != maxIterations) {
    ANNkd_tree* pKdTree =  new ANNkd_tree(clusterCentersANN, k, dim);

    clusterToData.clear();
    clusterToData.resize(k);
    dataToCluster.clear();
    dataToCluster.resize(data.size());

    for (size_t i = 0; i < data.size(); ++i) {
      ANNpoint point = annAllocPt(dim);
      for (size_t j = 0; j < dim; j++)
        point[j] = data[i](j);
      pKdTree->annkSearch(point, 1, idx, dist, 0);
      clusterToData[idx[0]].push_back(i);
      dataToCluster[i] = idx[0];
      annDeallocPt(point);
    }

    delete pKdTree;

    double dist = 0;
    for (size_t i = 0; i < k; ++i) {
      clusterCenters[i].setConstant(0);
      for (size_t j = 0; j < clusterToData[i].size(); ++j) {
        clusterCenters[i] += data[clusterToData[i][j]];
      }
      if (clusterToData[i].size())
        clusterCenters[i] /= clusterToData[i].size();
      for (size_t j = 0; j < dim; ++j) {
        clusterCentersANN[i][j] = clusterCenters[i](j);
        if (iteration)
          dist += (clusterCenters[i] - clusterCentersOld[i]).norm();
        clusterCentersOld[i] = clusterCenters[i];
      }
    }

    if (debug) {
      std::cout << "Centers moved: " << std::scientific << dist << std::endl;
      std::cout << "Iteration: " << std::fixed << iteration << std::endl;
    }

    if (iteration && dist < tol)
      break;

    iteration++;
  }

  annDeallocPts(clusterCentersANN);
  delete [] idx;
  delete [] dist;
  annClose();
  return iteration;
}
