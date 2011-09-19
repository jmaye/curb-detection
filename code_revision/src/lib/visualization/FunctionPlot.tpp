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

template <typename Y, typename X>
FunctionPlot<Y, X>::FunctionPlot(const std::string& title, const X& minimum,
  const X& maximum) :
  mTitle(title),
  mMinimum(minimum),
  mMaximum(maximum) {
}

template <typename Y, typename X>
FunctionPlot<Y, X>::~FunctionPlot() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename Y, typename X>
const std::string& FunctionPlot<Y, X>::getTitle() const {
  return mTitle;
}

template <typename Y, typename X>
const X& FunctionPlot<Y, X>::getMinimum() const {
  return mMinimum;
}

template <typename Y, typename X>
const X& FunctionPlot<Y, X>::getMaximum() const {
  return mMaximum;
}
