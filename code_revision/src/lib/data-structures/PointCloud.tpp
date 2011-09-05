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

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename X, size_t M>
PointCloud<X, M>::PointCloud() {
}

template <typename X, size_t M>
PointCloud<X, M>::PointCloud(const PointCloud<X, M>& other) :
  mPoints(other.mPoints) {
}

template <typename X, size_t M>
PointCloud<X, M>& PointCloud<X, M>::operator = (const PointCloud<X, M>& other) {
  if (this != &other) {
    mPoints = other.mPoints;
  }
  return *this;
}

template <typename X, size_t M>
PointCloud<X, M>::~PointCloud() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename X, size_t M>
void PointCloud<X, M>::read(std::istream& stream) {
}

template <typename X, size_t M>
void PointCloud<X, M>::write(std::ostream& stream) const {
}

template <typename X, size_t M>
void PointCloud<X, M>::read(std::ifstream& stream) throw (IOException) {
  mPoints.clear();
  if (stream.is_open() == false)
    throw IOException("PointCloud<X, M>::read(): could not open file");
  while (stream.eof() == false) {
    PointType point;
    for (size_t i = 0; i < M; ++i) {
      stream >> point(i);
      stream.seekg(1, std::ios_base::cur);
    }
    mPoints.push_back(point);
  }
}

template <typename X, size_t M>
void PointCloud<X, M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename X, size_t M>
const typename PointCloud<X, M>::PointType& PointCloud<X, M>::operator ()
  (size_t idx) const throw (OutOfBoundException<size_t>) {
  if (idx >= mPoints.size())
    throw OutOfBoundException<size_t>(idx,
      "PointCloud<X, M>::operator (): invalid index", __FILE__, __LINE__);
  return mPoints[idx];
}

template <typename X, size_t M>
size_t PointCloud<X, M>::getNumPoints() const {
  return mPoints.size();
}

template <typename X, size_t M>
void PointCloud<X, M>::clear() {
  mPoints.clear();
}

template <typename X, size_t M>
void PointCloud<X, M>::addPoint(const PointType& point) {
  mPoints.push_back(point);
}

template <typename X, size_t M>
void PointCloud<X, M>::addPointCloud(const PointCloud& pointCloud) {
  for (size_t i = 0; i < pointCloud.getNumPoints(); ++i)
    mPoints.push_back(pointCloud(i));
}

template <typename X, size_t M>
typename PointCloud<X, M>::ConstIteratorType PointCloud<X, M>::getItBegin()
  const {
  return mPoints.begin();
}

template <typename X, size_t M>
typename PointCloud<X, M>::IteratorType PointCloud<X, M>::getItBegin() {
  return mPoints.begin();
}

template <typename X, size_t M>
typename PointCloud<X, M>::ConstIteratorType PointCloud<X, M>::getItEnd()
  const {
  return mPoints.end();
}

template <typename X, size_t M>
typename PointCloud<X, M>::IteratorType PointCloud<X, M>::getItEnd() {
  return mPoints.end();
}

template <typename X, size_t M>
const typename PointCloud<X, M>::ContainerType& PointCloud<X, M>::getPoints()
  const {
  return mPoints;
}
