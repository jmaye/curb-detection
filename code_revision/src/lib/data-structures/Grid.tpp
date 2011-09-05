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

template <typename T, typename C>
Grid<T, C>::Grid(const CoordinateType& minimum, const CoordinateType& maximum,
  const CoordinateType& resolution)
  throw (BadArgumentException<Grid<T, C>::CoordinateType>) :
  mMinimum(minimum),
  mMaximum(maximum),
  mResolution(resolution) {
  if ((resolution.cwise() <= 0).any())
    throw BadArgumentException<CoordinateType>(resolution,
      "Grid<T, C>::Grid(): resolution must be strictly positive",
       __FILE__, __LINE__);
  if ((minimum.cwise() >= maximum).any())
    throw BadArgumentException<CoordinateType>(minimum,
      "Grid<T, C>::Grid(): minimum must be strictly smaller than maximum",
       __FILE__, __LINE__);
  mNumCells.resize(resolution.size());
  size_t numCellsTot = 1.0;
  for (size_t i = 0; i < minimum.size(); ++i) {
    mNumCells(i) = (maximum(i) - minimum(i)) / resolution(i);
    numCellsTot *= mNumCells(i);
  }
  mCells.resize(numCellsTot);
}

template <typename T, typename C>
Grid<T, C>::Grid(const Grid& other) :
  mCells(other.mCells),
  mMinimum(other.mMinimum),
  mMaximum(other.mMaximum),
  mResolution(other.mResolution),
  mNumCells(other.mNumCells) {
}

template <typename T, typename C>
Grid<T, C>& Grid<T, C>::operator = (const Grid<T, C>& other) {
  if (this != &other) {
    mCells = other.mCells;
    mMinimum = other.mMinimum;
    mMaximum = other.mMaximum;
    mResolution = other.mResolution;
    mNumCells = other.mNumCells;
  }
  return *this;
}

template <typename T, typename C>
Grid<T, C>::~Grid() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename T, typename C>
void Grid<T, C>::read(std::istream& stream) {
}

template <typename T, typename C>
void Grid<T, C>::write(std::ostream& stream) const {
}

template <typename T, typename C>
void Grid<T, C>::read(std::ifstream& stream) {
}

template <typename T, typename C>
void Grid<T, C>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename T, typename C>
typename Grid<T, C>::ConstIteratorType Grid<T, C>::getItBegin() const {
  return mCells.begin();
}

template <typename T, typename C>
typename Grid<T, C>::IteratorType Grid<T, C>::getItBegin() {
  return mCells.begin();
}

template <typename T, typename C>
typename Grid<T, C>::ConstIteratorType Grid<T, C>::getItEnd() const {
  return mCells.end();
}

template <typename T, typename C>
typename Grid<T, C>::IteratorType Grid<T, C>::getItEnd() {
  return mCells.end();
}

template <typename T, typename C>
const typename Grid<T, C>::ContainerType& Grid<T, C>::getCells() const {
  return mCells;
}

template <typename T, typename C>
const C& Grid<T, C>::operator () (const Grid<T, C>::IndexType& idx) const
  throw (OutOfBoundException<Grid<T, C>::IndexType>) {
  if ((idx.cwise() > mNumCells).any())
    throw OutOfBoundException<IndexType>(idx,
      "Grid<T, C>::operator (): index out of range", __FILE__, __LINE__);
}

template <typename T, typename C>
C& Grid<T, C>::operator () (const Grid<T, C>::IndexType& idx)
  throw (OutOfBoundException<Grid<T, C>::IndexType>) {
  if ((idx.cwise() >= mNumCells).any())
    throw OutOfBoundException<IndexType>(idx,
      "Grid<T, C>::operator (): index out of range", __FILE__, __LINE__);
}

template <typename T, typename C>
const C& Grid<T, C>::operator () (const Grid<T, C>::CoordinateType& point) const
  throw (OutOfBoundException<Grid<T, C>::CoordinateType>) {
  if ((point.cwise() > mMaximum).any() || (point.cwise() < mMinimum).any())
    throw OutOfBoundException<IndexType>(point,
      "Grid<T, C>::operator (): point out of range", __FILE__, __LINE__);
}

template <typename T, typename C>
C& Grid<T, C>::operator () (const Grid<T, C>::CoordinateType& point)
  throw (OutOfBoundException<Grid<T, C>::CoordinateType>) {
  if ((point.cwise() > mMaximum).any() || (point.cwise() < mMinimum).any())
    throw OutOfBoundException<IndexType>(point,
      "Grid<T, C>::operator (): point out of range", __FILE__, __LINE__);
}

template <typename T, typename C>
const typename Grid<T, C>::IndexType& Grid<T, C>::getNumCells() const {
  return mNumCells;
}

template <typename T, typename C>
const typename Grid<T, C>::CoordinateType& Grid<T, C>::getMinimum() const {
  return mMinimum;
}

template <typename T, typename C>
const typename Grid<T, C>::CoordinateType& Grid<T, C>::getMaximum() const {
  return mMaximum;
}

template <typename T, typename C>
const typename Grid<T, C>::CoordinateType& Grid<T, C>::getResolution() const {
  return mResolution;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

