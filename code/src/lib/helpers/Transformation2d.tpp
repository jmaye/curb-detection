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

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename T>
Transformation<T, 2>::Transformation() {
}

template <typename T>
Transformation<T, 2>::Transformation(const Eigen::Matrix<double, 3, 3>&
    transformationMatrix) :
    mTransformationMatrix(transformationMatrix) {
}

template <typename T>
Transformation<T, 2>::Transformation(const Transformation<T, 2>& other) :
    mTransformationMatrix(other.mTransformationMatrix) {
}

template <typename T>
Transformation<T, 2>& Transformation<T, 2>::operator = (const
    Transformation<T, 2>& other) {
  if (this != &other) {
    mTransformationMatrix = other.mTransformationMatrix;
  }
  return *this;
}

template <typename T>
Transformation<T, 2>::~Transformation() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename T>
void Transformation<T, 2>::read(std::istream& stream) {
}

template <typename T>
void Transformation<T, 2>::write(std::ostream& stream) const {
  stream << "Transformation matrix: " << std::endl << mTransformationMatrix;
}

template <typename T>
void Transformation<T, 2>::read(std::ifstream& stream) {
}

template <typename T>
void Transformation<T, 2>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename T>
void Transformation<T, 2>::setTransformationMatrix(const
    Eigen::Matrix<double, 3, 3>& transformationMatrix) {
  mTransformationMatrix = transformationMatrix;
}

template <typename T>
const Eigen::Matrix<double, 3, 3>&
    Transformation<T, 2>::getTransformationMatrix() {
  return mTransformationMatrix;
}

template <typename T>
void Transformation<T, 2>::setTransformation(T x, T y, T yaw) {
  double cosYaw = cos(yaw);
  double sinYaw = sin(yaw);
  mTransformationMatrix(0, 0) = cosYaw;
  mTransformationMatrix(0, 1) = -sinYaw;
  mTransformationMatrix(0, 2) = x;
  mTransformationMatrix(1, 0) = sinYaw;
  mTransformationMatrix(1, 1) = cosYaw;
  mTransformationMatrix(1, 2) = y;
  mTransformationMatrix(2, 0) = 0;
  mTransformationMatrix(2, 1) = 0;
  mTransformationMatrix(2, 2) = 1;
}

template <typename T>
void Transformation<T, 2>::inverse() {
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

template <typename T>
void Transformation<T, 2>::transform(const Eigen::Matrix<T, 2, 1>& src,
    Eigen::Matrix<T, 2, 1>& dest) const {
  Eigen::Matrix<T, 3, 1> point(src(0), src(1), T(1));
  dest = (mTransformationMatrix * point).start(2);
}
