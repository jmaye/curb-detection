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

/** \file RandomColors.h
    \brief This file defines the randomColors function, which is a helper to
           generate random colors.
  */

#ifndef RANDOMCOLORS_H
#define RANDOMCOLORS_H

#include <vector>
#include <cstdlib>

namespace Helpers {

  /** \name Types definitions
    @{
    */
  /// Color type
  struct Color {
    /// Red component
    GLfloat mRedColor;
    /// Green component
    GLfloat mGreenColor;
    /// Blue component
    GLfloat mBlueColor;
  };
  /** @}
    */

/** The randomColors function generates random colors.
*/
static void randomColors(std::vector<Color>& colors, size_t num);

#include "helpers/RandomColors.tpp"

};

#endif // RANDOMCOLORS_H
