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
  Qwt3D::SurfacePlot(0) {
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
  Eigen::Matrix<size_t, 2, 1> numBins = histogram.getNumBins();
  size_t xSize = numBins(0);
  size_t ySize = numBins(0);
  mData = new T*[xSize];
  for (size_t i = 0; i < xSize; ++i) {
    Qwt3D::Cell cell;
    mData[i] = new T[ySize];
    for (size_t j = 0; j < ySize; ++j) {
      mData[i][j] = histogram.getBinContent((Eigen::Matrix<size_t, 2, 1>()
        << i, j).finished());
    }
  }
  loadFromData(mData, xSize, ySize, histogram.getBinCenter(
    (Eigen::Matrix<size_t, 2, 1>() << 0, 0).finished())(0),
    histogram.getBinCenter((Eigen::Matrix<size_t, 2, 1>() << numBins(0) - 1,
    numBins(1) - 1).finished())(0), histogram.getBinCenter(
    (Eigen::Matrix<size_t, 2, 1>() << 0, 0).finished())(1),
    histogram.getBinCenter((Eigen::Matrix<size_t, 2, 1>() << numBins(0) - 1,
    numBins(1) - 1).finished())(1));
}

template <typename T>
HistogramPlot<T, 2>::~HistogramPlot() {
//  size_t xSize = round((this->getMaximum()(0) - this->getMinimum()(0)) /
//    this->getResolution()(0));
//  for (size_t i = 0; i < xSize; ++i) {
//    delete []mData[i];
//  }
//  delete []mData;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/


/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

template <typename T>
void HistogramPlot<T, 2>::show() {
  QWidget::show();
}
