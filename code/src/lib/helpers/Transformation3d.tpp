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

template <typename T>
Transformation<T, 3>::Transformation() {
}

template <typename T>
Transformation<T, 3>::Transformation(const Eigen::Matrix<double, 4, 4>&
    transformationMatrix) :
    mTransformationMatrix(transformationMatrix) {
}

template <typename T>
Transformation<T, 3>::Transformation(const Transformation<T, 3>& other) :
    mTransformationMatrix(other.mTransformationMatrix) {
}

template <typename T>
Transformation<T, 3>& Transformation<T, 3>::operator = (const
    Transformation<T, 3>& other) {
  if (this != &other) {
    mTransformationMatrix = other.mTransformationMatrix;
  }
  return *this;
}

template <typename T>
Transformation<T, 3>::~Transformation() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

template <typename T>
void Transformation<T, 3>::read(std::istream& stream) {
}

template <typename T>
void Transformation<T, 3>::write(std::ostream& stream) const {
  stream << "Transformation matrix: " << std::endl << mTransformationMatrix;
}

template <typename T>
void Transformation<T, 3>::read(std::ifstream& stream) {
}

template <typename T>
void Transformation<T, 3>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename T>
void Transformation<T, 3>::setTransformationMatrix(const
    Eigen::Matrix<double, 4, 4>& transformationMatrix) {
  mTransformationMatrix = transformationMatrix;
}

template <typename T>
const Eigen::Matrix<double, 4, 4>&
    Transformation<T, 3>::getTransformationMatrix() {
  return mTransformationMatrix;
}

template <typename T>
void Transformation<T, 3>::setTransformation(T x, T y, T z, T roll, T pitch,
  T yaw) {
  double sinRoll = sin(roll);
  double cosRoll = cos(roll);
  double sinPitch = sin(pitch);
  double cosPitch = cos(pitch);
  double sinYaw = sin(yaw);
  double cosYaw = cos(yaw);
  mTransformationMatrix(0, 0) = cosYaw * cosPitch;
  mTransformationMatrix(0, 1) = cosYaw * sinPitch * sinRoll - sinYaw * cosRoll;
  mTransformationMatrix(0, 2) = cosYaw * sinPitch * cosRoll + sinYaw * sinRoll;
  mTransformationMatrix(0, 3) = x;
  mTransformationMatrix(1, 0) = sinYaw * cosPitch;
  mTransformationMatrix(1, 1) = sinYaw * sinPitch * sinRoll + cosYaw * cosRoll;
  mTransformationMatrix(1, 2) = sinYaw * sinPitch * cosRoll - cosYaw * sinRoll;
  mTransformationMatrix(1, 3) = y;
  mTransformationMatrix(2, 0) = -sinPitch;
  mTransformationMatrix(2, 1) = cosPitch * sinRoll;
  mTransformationMatrix(2, 2) = cosPitch * cosRoll;
  mTransformationMatrix(2, 3) = z;
  mTransformationMatrix(3, 0) = 0;
  mTransformationMatrix(3, 1) = 0;
  mTransformationMatrix(3, 2) = 0;
  mTransformationMatrix(3, 3) = 1;
}

template <typename T>
void Transformation<T, 3>::inverse() {
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

template <typename T>
void Transformation<T, 3>::transform(const Eigen::Matrix<T, 3, 1>& src,
    Eigen::Matrix<T, 3, 1>& dest) const {
  Eigen::Matrix<T, 4, 1> point(src(0), src(1), src(2), T(1));
  dest = (mTransformationMatrix * point).start(3);
}
