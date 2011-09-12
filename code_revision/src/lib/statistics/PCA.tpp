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

#include <Eigen/QR>

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

template <typename T, size_t D, size_t M>
void PCA<T, D, M>::analyze(const std::vector<Eigen::Matrix<T, D, 1> >& data,
  std::vector<Eigen::Matrix<T, M, 1> >& transformedData, Eigen::Matrix<T, D, 1>&
  eigenValues, Eigen::Matrix<T, D, D>& eigenVectors)
  throw (BadArgumentException<size_t>) {

  if (data.size() == 0)
    throw BadArgumentException<size_t>(data.size(),
      "PCA::cluster(): input points vector is empty",
      __FILE__, __LINE__);

  if (M > D)
    throw BadArgumentException<size_t>(M,
      "PCA::cluster(): dimension must be smaller than the original data",
      __FILE__, __LINE__);

  Eigen::Matrix<T, D, 1> mean = Eigen::Matrix<T, D, 1>::Zero();
  for (size_t i = 0; i < data.size(); ++i)
    mean += data[i];
  mean /= data.size();

  Eigen::Matrix<T, D, D> covariance = Eigen::Matrix<T, D, D>::Zero();
  for (size_t i = 0; i < data.size(); ++i)
    covariance += (data[i] - mean) * (data[i] - mean).transpose();
  covariance /= data.size();

  Eigen::SelfAdjointEigenSolver<Eigen::Matrix<T, D, D> > solver(covariance);
  eigenValues = solver.eigenvalues();
  eigenVectors = solver.eigenvectors();

  transformedData.clear();
  transformedData.resize(data.size());
  for (size_t i = 0; i < data.size(); ++i) {
    Eigen::Matrix<T, M, 1> point;
    for (size_t j = 0; j < M; ++j)
      point(j) = (data[i].transpose() * eigenVectors.col(D - 1 - j))(0) -
        (mean.transpose() * eigenVectors.col(D - 1 - j))(0);
    transformedData[i] = point;
  }
}
