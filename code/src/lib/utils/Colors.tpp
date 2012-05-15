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
#include <vector>
#include <limits>

namespace Colors {

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

template <typename T>
T revertBits(T value) {
  T reverse = value;
  T shift = sizeof(T) * 8 - 1;
  for (value >>= 1; value; value >>= 1) {
    reverse <<= 1;
    reverse |= value & 1;
    --shift;
  }
  reverse <<= shift;
  return reverse;
}

template <typename T>
double intToHue(T value) {
  return (double)revertBits<T>(value) / std::numeric_limits<T>::max() * 360;
}

Color genColor(size_t idx) {
  double h = intToHue<size_t>(idx);
  const double s = 1.0;
  const double v = 1.0;
  h /= 60.0;
  const int i = floor(h);
  const double f =  h - i;
  const double p = v * (1 - s);
  const double q = v * (1 - s * f);
  const double t = v * (1 - s * (1 - f));
  Color color;
  switch (i) {
    case 0:
      color.mRed = v ;
      color.mGreen = t;
      color.mBlue = p;
      break;
    case 1:
      color.mRed = q;
      color.mGreen = v;
      color.mBlue = p;
      break;
    case 2:
      color.mRed = p;
      color.mGreen = v;
      color.mBlue = t;
      break;
    case 3:
      color.mRed = p;
      color.mGreen = q;
      color.mBlue = v;
      break;
    case 4:
      color.mRed = t;
      color.mGreen = p;
      color.mBlue = v;
      break;
    default:
      color.mRed = v;
      color.mGreen = p;
      color.mBlue = q;
      break;
  }
  return color;
}

}
