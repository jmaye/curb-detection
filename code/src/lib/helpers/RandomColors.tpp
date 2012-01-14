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

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void randomColors(std::vector<Color>& colors, size_t num) {
  const static Randomizer<double> randomizer;
  colors.clear();
  colors.reserve(num);
  for (size_t i = 0; i < num; ++i) {
    Color color;
    double h = randomizer.sampleUniform(0, 360);
    const double s = 1.0;
    const double v = 1.0;
    h /= 60.0;
    const int i = floor(h);
    const double f =  h - i;
    const double p = v * (1 - s);
    const double q = v * (1 - s * f);
    const double t = v * (1 - s * (1 - f));
    switch (i) {
      case 0:
        color.mRedColor = v ;
        color.mGreenColor = t;
        color.mBlueColor = p;
        break;
      case 1:
        color.mRedColor = q;
        color.mGreenColor = v;
        color.mBlueColor = p;
        break;
      case 2:
        color.mRedColor = p;
        color.mGreenColor = v;
        color.mBlueColor = t;
        break;
      case 3:
        color.mRedColor = p;
        color.mGreenColor = q;
        color.mBlueColor = v;
        break;
      case 4:
        color.mRedColor = t;
        color.mGreenColor = p;
        color.mBlueColor = v;
        break;
      default:
        color.mRedColor = v;
        color.mGreenColor = p;
        color.mBlueColor = q;
        break;
    }
    colors.push_back(color);
  }
}
