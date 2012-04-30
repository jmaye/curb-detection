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
HistogramPlot<T, 2>::HistogramPlot(const std::string& title, const
    Histogram<T, 2>& histogram) :
    mHistogram(histogram) {
  Qwt3D::SurfacePlot::setTitle(title.c_str());
  setRotation(30, 0, 15);
  setScale(1, 1, 1);
  setShift(0.15, 0, 0);
  setZoom(0.9);
  for (size_t i = 0; i != coordinates()->axes.size(); ++i) {
    coordinates()->axes[i].setMajors(7);
    coordinates()->axes[i].setMinors(4);
  }
  coordinates()->axes[Qwt3D::X1].setLabelString("x-axis");
  coordinates()->axes[Qwt3D::Y1].setLabelString("y-axis");
  coordinates()->axes[Qwt3D::Z1].setLabelString("z-axis");
  setCoordinateStyle(Qwt3D::FRAME);
  setPlotStyle(Qwt3D::FILLED);
  auto numCells = mHistogram.getNumCells();
  mData = new double*[numCells(0)];
  for (size_t i = 0; i < numCells(0); ++i) {
    mData[i] = new double[numCells(1)];
    for (size_t j = 0; j < numCells(1); ++j)
      mData[i][j] = mHistogram.getCell(
        (typename Histogram<T, 2>::Index() << i, j).finished());
  }
  auto minimum = mHistogram.getMinimum();
  auto maximum = mHistogram.getMaximum();
  loadFromData(mData, numCells(0), numCells(1), minimum(0), maximum(0),
    minimum(1), maximum(1));
}

template <typename T>
HistogramPlot<T, 2>::~HistogramPlot() {
  auto numCells = mHistogram.getNumCells();
  for (size_t i = 0; i < numCells(0); ++i)
    delete []mData[i];
  delete []mData;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename T>
const std::string& HistogramPlot<T, 2>::getTitle() const {
  return mTitle;
}

template <typename T>
const Histogram<T, 2>& HistogramPlot<T, 2>::getHistogram() const {
  return mHistogram;
}
