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
Grid<T, C, M>::Grid(const Coordinate& minimum, const Coordinate& maximum, const
  Coordinate& resolution) throw
  (BadArgumentException<Grid<T, C, M>::Coordinate>) :
  mMinimum(minimum),
  mMaximum(maximum),
  mResolution(resolution) {
  if ((resolution.cwise() <= 0).any())
    throw BadArgumentException<Coordinate>(resolution,
      "Grid<T, C, M>::Grid(): resolution must be strictly positive",
       __FILE__, __LINE__);
  if ((minimum.cwise() >= maximum).any())
    throw BadArgumentException<Coordinate>(minimum,
      "Grid<T, C, M>::Grid(): minimum must be strictly smaller than maximum",
       __FILE__, __LINE__);
  if ((resolution.cwise() >= maximum - minimum).any())
    throw BadArgumentException<Coordinate>(resolution,
      "Grid<T, C, M>::Grid(): resolution must be strictly smaller than range",
       __FILE__, __LINE__);
  mNumCells.resize(resolution.size());
  mNumCellsTot = 1.0;
  mLinProd = Index::Ones(resolution.size());
  for (size_t i = 0; i < (size_t)minimum.size(); ++i) {
    mNumCells(i) = ceil((maximum(i) - minimum(i)) / resolution(i));
    mNumCellsTot *= mNumCells(i);
  }
  for (size_t i = 0; i < (size_t)minimum.size(); ++i)
    for (size_t j = i + 1; j < (size_t)minimum.size(); ++j)
      mLinProd(i) *= mNumCells(j);
  mCells.resize(mNumCellsTot);
}

template <typename T, typename C, size_t M>
Grid<T, C, M>::Grid(const Grid& other) :
  mCells(other.mCells),
  mMinimum(other.mMinimum),
  mMaximum(other.mMaximum),
  mResolution(other.mResolution),
  mNumCells(other.mNumCells),
  mNumCellsTot(other.mNumCellsTot),
  mLinProd(other.mLinProd) {
}

template <typename T, typename C, size_t M>
Grid<T, C, M>& Grid<T, C, M>::operator = (const Grid<T, C, M>& other) {
  if (this != &other) {
    mCells = other.mCells;
    mMinimum = other.mMinimum;
    mMaximum = other.mMaximum;
    mResolution = other.mResolution;
    mNumCells = other.mNumCells;
    mNumCellsTot = other.mNumCellsTot;
    mLinProd = other.mLinProd;
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
    << "total number of cells: " << mNumCellsTot << std::endl
    << "cells: " << std::endl;
    for (ConstCellIterator it = getCellBegin(); it != getCellEnd(); ++it)
      stream << *it << std::endl;
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
typename Grid<T, C, M>::ConstCellIterator Grid<T, C, M>::getCellBegin() const {
  return mCells.begin();
}

template <typename T, typename C, size_t M>
typename Grid<T, C, M>::CellIterator Grid<T, C, M>::getCellBegin() {
  return mCells.begin();
}

template <typename T, typename C, size_t M>
typename Grid<T, C, M>::ConstCellIterator Grid<T, C, M>::getCellEnd() const {
  return mCells.end();
}

template <typename T, typename C, size_t M>
typename Grid<T, C, M>::CellIterator Grid<T, C, M>::getCellEnd() {
  return mCells.end();
}

template <typename T, typename C, size_t M>
const typename Grid<T, C, M>::Container& Grid<T, C, M>::getCells() const {
  return mCells;
}

template <typename T, typename C, size_t M>
size_t Grid<T, C, M>::computeLinearIndex(const Index& idx) const {
  size_t linIdx = 0;
  for (size_t i = 0; i < (size_t)idx.size(); ++i)
    linIdx += mLinProd(i) * idx(i);
  return linIdx;
}

template <typename T, typename C, size_t M>
const C& Grid<T, C, M>::getCell(const Index& idx) const throw
  (OutOfBoundException<Index>) {
  if (!isValidIndex(idx))
    throw OutOfBoundException<Index>(idx,
      "Grid<T, C, M>::getCell(): index out of range", __FILE__, __LINE__);
  return mCells[computeLinearIndex(idx)];
}

template <typename T, typename C, size_t M>
C& Grid<T, C, M>::getCell(const Index& idx) throw (OutOfBoundException<Index>) {
  if (!isValidIndex(idx))
    throw OutOfBoundException<Index>(idx,
      "Grid<T, C, M>::getCell(): index out of range", __FILE__, __LINE__);
  return mCells[computeLinearIndex(idx)];
}

template <typename T, typename C, size_t M>
const C& Grid<T, C, M>::operator [] (const Index& idx) const {
  return getCell(idx);
}

template <typename T, typename C, size_t M>
C& Grid<T, C, M>::operator [] (const Index& idx) {
  return getCell(idx);
}

template <typename T, typename C, size_t M>
typename Grid<T, C, M>::Index Grid<T, C, M>::getIndex(const Coordinate& point)
  const throw (OutOfBoundException<Coordinate>) {
  if (!isInRange(point))
    throw OutOfBoundException<Coordinate>(point,
      "Grid<T, C, M>::operator (): point out of range", __FILE__, __LINE__);
  Index idx(point.size());
  for (size_t i = 0; i < (size_t)point.size(); ++i)
    if (point(i) == mMaximum(i))
      idx(i) = mNumCells(i) - 1;
    else
      idx(i) = (point(i) - mMinimum(i)) / mResolution(i);
  return idx;
}

template <typename T, typename C, size_t M>
const C& Grid<T, C, M>::operator () (const Coordinate& point) const {
  return operator[](getIndex(point));
}

template <typename T, typename C, size_t M>
C& Grid<T, C, M>::operator () (const Coordinate& point) {
  return operator[](getIndex(point));
}

template <typename T, typename C, size_t M>
typename Grid<T, C, M>::Coordinate Grid<T, C, M>::getCoordinates(const Index&
  idx) const throw (OutOfBoundException<Index>) {
  if (!isValidIndex(idx))
    throw OutOfBoundException<Index>(idx,
      "Grid<T, C, M>::getCoordinates(): index out of range",
      __FILE__, __LINE__);
  Coordinate point(idx.size());
  for (size_t i = 0; i < (size_t)idx.size(); ++i)
    point[i] = mMinimum(i) + (idx(i) + 0.5) * mResolution(i);
  return point;
}

template <typename T, typename C, size_t M>
bool Grid<T, C, M>::isInRange(const Coordinate& point) const {
  return ((point.cwise() <= mMaximum).all() &&
    (point.cwise() >= mMinimum).all());
}

template <typename T, typename C, size_t M>
bool Grid<T, C, M>::isValidIndex(const Index& idx) const {
  return ((idx.cwise() < mNumCells).all());
}

template <typename T, typename C, size_t M>
const typename Grid<T, C, M>::Index& Grid<T, C, M>::getNumCells() const {
  return mNumCells;
}

template <typename T, typename C, size_t M>
const size_t& Grid<T, C, M>::getNumCellsTot() const {
  return mNumCellsTot;
}

template <typename T, typename C, size_t M>
const typename Grid<T, C, M>::Coordinate& Grid<T, C, M>::getMinimum() const {
  return mMinimum;
}

template <typename T, typename C, size_t M>
const typename Grid<T, C, M>::Coordinate& Grid<T, C, M>::getMaximum() const {
  return mMaximum;
}

template <typename T, typename C, size_t M>
const typename Grid<T, C, M>::Coordinate& Grid<T, C, M>::getResolution() const {
  return mResolution;
}
