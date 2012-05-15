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

#include "statistics/Randomizer.h"

#include <list>

#include <ANN/ANN.h>

#include "exceptions/BadArgumentException.h"

namespace MeanShiftClustering {

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

template <typename T, size_t M>
void cluster(const std::vector<Eigen::Matrix<T, M, 1> >& data,
    std::vector<Eigen::Matrix<T, M, 1> >& clusterCenters,
    std::vector<std::vector<size_t> >& clusterToData, std::vector<size_t>&
    dataToCluster, double bandwidth, double tol, bool debug) {

  if (bandwidth <= 0)
    throw BadArgumentException<double>(bandwidth,
      "MeanShiftClustering::cluster(): bandwidth must be strictly greater "
      "than 0",
      __FILE__, __LINE__);

  if (data.size() == 0)
    throw BadArgumentException<size_t>(data.size(),
      "MeanShiftClustering::cluster(): input points vector is empty",
      __FILE__, __LINE__);

  size_t dim = data[0].size();

  std::list<size_t> activePoints;
  for (size_t i = 0; i < data.size(); ++i)
    activePoints.push_back(i);

  Randomizer<size_t> randomizer;

  ANNpointArray annPoints = annAllocPts(data.size(), dim);

  for (size_t i = 0; i < data.size(); ++i) {
    for (size_t j = 0; j < dim; ++j)
      annPoints[i][j] = data[i](j);
  }

  ANNkd_tree* pKdTree =  new ANNkd_tree(annPoints, data.size(), dim);
  std::vector<Eigen::Matrix<size_t, Eigen::Dynamic, 1> > clusterVotes;
  while (activePoints.size()) {
    size_t idx = 0;
    if (activePoints.size() > 1)
      idx = randomizer.sampleUniform(0, activePoints.size() - 1);
    std::list<size_t>::const_iterator it;
    size_t i = 0;
    for (it = activePoints.begin(); i < idx; ++it, ++i)
      ;
    Eigen::Matrix<T, M, 1> mean = data[*it];
    Eigen::Matrix<size_t, Eigen::Dynamic, 1> currentClusterVotes =
      Eigen::Matrix<size_t, Eigen::Dynamic, 1>::Zero(data.size());
    while (true) {
      ANNpoint point = annAllocPt(dim);
      for (size_t i = 0; i < dim; ++i)
        point[i] = mean(i);
      int numPoints = pKdTree->annkFRSearch(point, bandwidth * bandwidth, 0);
      ANNidxArray idx = new ANNidx[numPoints];
      ANNdistArray dist = new ANNdist[numPoints];
      pKdTree->annkFRSearch(point, bandwidth * bandwidth, numPoints, idx, dist);
      Eigen::Matrix<T, M, 1> oldMean = mean;
      mean.setConstant(0);
      for (size_t i = 0; i < (size_t)numPoints; ++i) {
        mean += data[idx[i]];
        activePoints.remove(idx[i]);
        currentClusterVotes(idx[i])++;
      }
      mean /= numPoints;
      annDeallocPt(point);
      delete [] idx;
      delete [] dist;
      if ((mean - oldMean).norm() < tol) {
        if (debug)
          std::cout << "New mean found: " << std::endl << mean << std::endl;
        ssize_t merge = -1;
        for (size_t i = 0; i < clusterCenters.size(); ++i) {
          if ((mean - clusterCenters[i]).norm() < 0.5 * bandwidth) {
            merge = i;
            break;
          }
        }
        if (merge >= 0) {
          clusterCenters[merge] = 0.5 * (mean + clusterCenters[merge]);
          clusterVotes[merge] += currentClusterVotes;
        }
        else {
          clusterCenters.push_back(mean);
          clusterVotes.push_back(currentClusterVotes);
        }
        break;
      }
    }
  }

  dataToCluster.clear();
  dataToCluster.resize(data.size());
  clusterToData.clear();
  clusterToData.resize(clusterCenters.size());
  for (size_t i = 0; i < data.size(); ++i) {
    size_t maxVotes = 0;
    size_t maxCluster = 0;
    for (size_t j = 0; j < clusterVotes.size(); ++j) {
      if (clusterVotes[j](i) > maxVotes) {
        maxVotes = clusterVotes[j](i);
        maxCluster = j;
      }
    }
    dataToCluster[i] = maxCluster;
    clusterToData[maxCluster].push_back(i);
  }

  annDeallocPts(annPoints);
  delete pKdTree;
  annClose();
}

}
