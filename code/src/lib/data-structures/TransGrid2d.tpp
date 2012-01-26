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

template <typename T, typename C>
TransGrid<T, C, 2>::TransGrid(const typename Grid<T, C, 2>::Coordinate& minimum,
    const typename Grid<T, C, 2>::Coordinate& maximum,
    const typename Grid<T, C, 2>::Coordinate& resolution, T x, T y, T yaw) :
    Grid<T, C, 2>(minimum, maximum, resolution),
    mTransformation(x, y, yaw),
    mInvTransformation(mTransformation.getInverse()) {
}

template <typename T, typename C>
TransGrid<T, C, 2>::TransGrid(const typename Grid<T, C, 2>::Coordinate& minimum,
    const typename Grid<T, C, 2>::Coordinate& maximum,
    const typename Grid<T, C, 2>::Coordinate& resolution,
    const Transformation<double, 2>& transformation) :
    Grid<T, C, 2>(minimum, maximum, resolution),
    mTransformation(transformation),
    mInvTransformation(mTransformation.getInverse()) {
}

template <typename T, typename C>
TransGrid<T, C, 2>::TransGrid(const TransGrid<T, C, 2>& other) :
    Grid<T, C, 2>(other),
    mTransformation(other.mTransformation),
    mInvTransformation(other.mInvTransformation) {
}

template <typename T, typename C>
TransGrid<T, C, 2>& TransGrid<T, C, 2>::operator = (const TransGrid<T, C, 2>&
    other) {
  if (this != &other) {
    this->Grid<T, C, 2>::operator=(other);
    mTransformation = other.mTransformation;
    mInvTransformation = other.mInvTransformation;
  }
  return *this;
}

template <typename T, typename C>
TransGrid<T, C, 2>::~TransGrid() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename T, typename C>
void TransGrid<T, C, 2>::read(std::istream& stream) {
}

template <typename T, typename C>
void TransGrid<T, C, 2>::write(std::ostream& stream) const {
  Grid<T, C, 2>::write(stream);
  stream << "Transformation: " << std::endl << mTransformation << std::endl;
}

template <typename T, typename C>
void TransGrid<T, C, 2>::read(std::ifstream& stream) {
}

template <typename T, typename C>
void TransGrid<T, C, 2>::write(std::ofstream& stream) const {
}

template <typename T, typename C>
void TransGrid<T, C, 2>::writeBinary(std::ostream& stream) const {
}

template <typename T, typename C>
void TransGrid<T, C, 2>::readBinary(std::istream& stream) {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename T, typename C>
typename Grid<T, C, 2>::Index TransGrid<T, C, 2>::getIndex(const typename
    Grid<T, C, 2>::Coordinate& point) const throw (OutOfBoundException<typename
    Grid<T, C, 2>::Coordinate>) {
    return Grid<T, C, 2>::getIndex(mInvTransformation(point));
}

template <typename T, typename C>
const C& TransGrid<T, C, 2>::operator () (const typename
    Grid<T, C, 2>::Coordinate& point) const {
  return this->Grid<T, C, 2>::operator()(mInvTransformation(point));
}

template <typename T, typename C>
C& TransGrid<T, C, 2>::operator () (const typename Grid<T, C, 2>::Coordinate&
    point) {
  return this->Grid<T, C, 2>::operator()(mInvTransformation(point));
}

template <typename T, typename C>
typename Grid<T, C, 2>::Coordinate TransGrid<T, C, 2>::getCoordinates(const
    typename Grid<T, C, 2>::Index& idx) const throw
    (OutOfBoundException<typename Grid<T, C, 2>::Index>) {
  return mTransformation(Grid<T, C, 2>::getCoordinates(idx));
}

template <typename T, typename C>
typename Grid<T, C, 2>::Coordinate TransGrid<T, C, 2>::getULCoordinates(const
    typename Grid<T, C, 2>::Index& idx) const {
  typename Grid<T, C, 2>::Coordinate point = Grid<T, C, 2>::getCoordinates(idx);
  point(0) += Grid<T, C, 2>::mResolution(0) / 2.0;
  point(1) += Grid<T, C, 2>::mResolution(1) / 2.0;
  return mTransformation(point);
}

template <typename T, typename C>
typename Grid<T, C, 2>::Coordinate TransGrid<T, C, 2>::getURCoordinates(const
    typename Grid<T, C, 2>::Index& idx) const {
  typename Grid<T, C, 2>::Coordinate point = Grid<T, C, 2>::getCoordinates(idx);
  point(0) += Grid<T, C, 2>::mResolution(0) / 2.0;
  point(1) -= Grid<T, C, 2>::mResolution(1) / 2.0;
  return mTransformation(point);
}

template <typename T, typename C>
typename Grid<T, C, 2>::Coordinate TransGrid<T, C, 2>::getLRCoordinates(const
    typename Grid<T, C, 2>::Index& idx) const {
  typename Grid<T, C, 2>::Coordinate point = Grid<T, C, 2>::getCoordinates(idx);
  point(0) -= Grid<T, C, 2>::mResolution(0) / 2.0;
  point(1) -= Grid<T, C, 2>::mResolution(1) / 2.0;
  return mTransformation(point);
}

template <typename T, typename C>
typename Grid<T, C, 2>::Coordinate TransGrid<T, C, 2>::getLLCoordinates(const
    typename Grid<T, C, 2>::Index& idx) const {
  typename Grid<T, C, 2>::Coordinate point = Grid<T, C, 2>::getCoordinates(idx);
  point(0) -= Grid<T, C, 2>::mResolution(0) / 2.0;
  point(1) += Grid<T, C, 2>::mResolution(1) / 2.0;
  return mTransformation(point);
}

template <typename T, typename C>
bool TransGrid<T, C, 2>::isInRange(const typename Grid<T, C, 2>::Coordinate&
    point) const {
  return Grid<T, C, 2>::isInRange(mInvTransformation(point));
}

template <typename T, typename C>
const Transformation<double, 2>& TransGrid<T, C, 2>::getTransformation() const {
  return mTransformation;
}

template <typename T, typename C>
void TransGrid<T, C, 2>::setTransformation(const Transformation<double, 2>&
    transformation) {
  mTransformation = transformation;
}

template <typename T, typename C>
void TransGrid<T, C, 2>::setTransformation(double x, double y, double yaw) {
  mTransformation.setTransformation(x, y, yaw);
}
