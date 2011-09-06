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

#include <Eigen/Array>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename T, typename C, size_t M>
Grid<T, C, M>::Grid(const CoordinateType& minimum, const CoordinateType&
  maximum, const CoordinateType& resolution)
  throw (BadArgumentException<Grid<T, C, M>::CoordinateType>) :
  mMinimum(minimum),
  mMaximum(maximum),
  mResolution(resolution) {
  if ((resolution.cwise() <= 0).any())
    throw BadArgumentException<CoordinateType>(resolution,
      "Grid<T, C, M>::Grid(): resolution must be strictly positive",
       __FILE__, __LINE__);
  if ((minimum.cwise() >= maximum).any())
    throw BadArgumentException<CoordinateType>(minimum,
      "Grid<T, C, M>::Grid(): minimum must be strictly smaller than maximum",
       __FILE__, __LINE__);
  mNumCells.resize(resolution.size());
  mNumCellsTot = 1.0;
  for (size_t i = 0; i < (size_t)minimum.size(); ++i) {
    mNumCells(i) = (maximum(i) - minimum(i)) / resolution(i);
    mNumCellsTot *= mNumCells(i);
  }
  mCells.resize(mNumCellsTot);
}

template <typename T, typename C, size_t M>
Grid<T, C, M>::Grid(const Grid& other) :
  mCells(other.mCells),
  mMinimum(other.mMinimum),
  mMaximum(other.mMaximum),
  mResolution(other.mResolution),
  mNumCells(other.mNumCells) {
}

template <typename T, typename C, size_t M>
Grid<T, C, M>& Grid<T, C, M>::operator = (const Grid<T, C, M>& other) {
  if (this != &other) {
    mCells = other.mCells;
    mMinimum = other.mMinimum;
    mMaximum = other.mMaximum;
    mResolution = other.mResolution;
    mNumCells = other.mNumCells;
  }
  return *this;
}

template <typename T, typename C, size_t M>
Grid<T, C, M>::~Grid() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename T, typename C, size_t M>
void Grid<T, C, M>::read(std::istream& stream) {
}

template <typename T, typename C, size_t M>
void Grid<T, C, M>::write(std::ostream& stream) const {
  stream << "minimum: " << mMinimum.transpose() << std::endl
    << "maximum: " << mMaximum.transpose() << std::endl
    << "resolution: " << mResolution.transpose() << std::endl
    << "number of cells per dim: " << mNumCells.transpose() << std:: endl
    << "total number of cells: " << mNumCellsTot;
}

template <typename T, typename C, size_t M>
void Grid<T, C, M>::read(std::ifstream& stream) {
}

template <typename T, typename C, size_t M>
void Grid<T, C, M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename T, typename C, size_t M>
typename Grid<T, C, M>::ConstIteratorType Grid<T, C, M>::getItBegin() const {
  return mCells.begin();
}

template <typename T, typename C, size_t M>
typename Grid<T, C, M>::IteratorType Grid<T, C, M>::getItBegin() {
  return mCells.begin();
}

template <typename T, typename C, size_t M>
typename Grid<T, C, M>::ConstIteratorType Grid<T, C, M>::getItEnd() const {
  return mCells.end();
}

template <typename T, typename C, size_t M>
typename Grid<T, C, M>::IteratorType Grid<T, C, M>::getItEnd() {
  return mCells.end();
}

template <typename T, typename C, size_t M>
const typename Grid<T, C, M>::ContainerType& Grid<T, C, M>::getCells() const {
  return mCells;
}

template <typename T, typename C, size_t M>
size_t Grid<T, C, M>::computeLinearIndex(const Grid<T, C, M>::IndexType& idx)
  const {
  size_t linIdx = 0;
  for (size_t i = 0; i < (size_t)idx.size(); ++i) {
    size_t prod = 1.0;
    for (size_t j = i + 1; j < (size_t)idx.size(); ++j)
      prod *= mNumCells(j);
    linIdx += prod * idx(i);
  }
  return linIdx;
}

template <typename T, typename C, size_t M>
const C& Grid<T, C, M>::getCell(const Grid<T, C, M>::IndexType& idx) const
  throw (OutOfBoundException<IndexType>) {
  if ((idx.cwise() > mNumCells).any())
    throw OutOfBoundException<IndexType>(idx,
      "Grid<T, C, M>::getCell(): index out of range", __FILE__, __LINE__);
  return mCells[computeLinearIndex(idx)];
}

template <typename T, typename C, size_t M>
C& Grid<T, C, M>::getCell(const Grid<T, C, M>::IndexType& idx)
  throw (OutOfBoundException<IndexType>) {
  if ((idx.cwise() > mNumCells).any())
    throw OutOfBoundException<IndexType>(idx,
      "Grid<T, C, M>::getCell(): index out of range", __FILE__, __LINE__);
  return mCells[computeLinearIndex(idx)];
}

template <typename T, typename C, size_t M>
const C& Grid<T, C, M>::operator [] (const Grid<T, C, M>::IndexType& idx)
  const {
  return getCell(idx);
}

template <typename T, typename C, size_t M>
C& Grid<T, C, M>::operator [] (const Grid<T, C, M>::IndexType& idx) {
  return getCell(idx);
}

template <typename T, typename C, size_t M>
typename Grid<T, C, M>::IndexType Grid<T, C, M>::getIndex(const
  Grid<T, C, M>::CoordinateType& point) const
  throw (OutOfBoundException<CoordinateType>) {
  if ((point.cwise() > mMaximum).any() || (point.cwise() < mMinimum).any())
    throw OutOfBoundException<CoordinateType>(point,
      "Grid<T, C, M>::operator (): point out of range", __FILE__, __LINE__);
  IndexType idx(point.size());
  for (size_t i = 0; i < (size_t)point.size(); ++i)
    if (point(i) == mMaximum(i))
      idx(i) = mNumCells(i) - 1;
    else
      idx(i) = (point(i) - mMinimum(i)) / mResolution(i);
  return idx;
}

template <typename T, typename C, size_t M>
const C& Grid<T, C, M>::operator () (const Grid<T, C, M>::CoordinateType& point)
  const {
  return operator[](getIndex(point));
}

template <typename T, typename C, size_t M>
C& Grid<T, C, M>::operator () (const Grid<T, C, M>::CoordinateType& point) {
  return operator[](getIndex(point));
}

template <typename T, typename C, size_t M>
typename Grid<T, C, M>::CoordinateType Grid<T, C, M>::getCoordinates(const
  Grid<T, C, M>::IndexType& idx) const throw (OutOfBoundException<IndexType>) {
  if ((idx.cwise() > mNumCells).any())
    throw OutOfBoundException<IndexType>(idx,
      "Grid<T, C, M>::getCoordinates(): index out of range",
      __FILE__, __LINE__);
  CoordinateType point(idx.size());
  for (size_t i = 0; i < (size_t)idx.size(); ++i)
    point[i] = mMinimum(i) + (idx(i) + 0.5) * mResolution(i);
  return point;
}

template <typename T, typename C, size_t M>
const typename Grid<T, C, M>::IndexType& Grid<T, C, M>::getNumCells() const {
  return mNumCells;
}

template <typename T, typename C, size_t M>
size_t Grid<T, C, M>::getNumCellsTot() const {
  return mNumCellsTot;
}

template <typename T, typename C, size_t M>
const typename Grid<T, C, M>::CoordinateType& Grid<T, C, M>::getMinimum()
  const {
  return mMinimum;
}

template <typename T, typename C, size_t M>
const typename Grid<T, C, M>::CoordinateType& Grid<T, C, M>::getMaximum()
  const {
  return mMaximum;
}

template <typename T, typename C, size_t M>
const typename Grid<T, C, M>::CoordinateType& Grid<T, C, M>::getResolution()
  const {
  return mResolution;
}
