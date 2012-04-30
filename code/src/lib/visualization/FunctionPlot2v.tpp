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

template <typename F>
FunctionPlot<F, 2>::FunctionPlot(const std::string& title, const F& function,
    const Domain& minimum, const Domain& maximum, const Domain& resolution) :
    mTitle(title),
    mMinimum(minimum),
    mMaximum(maximum),
    mResolution(resolution),
    mDataGrid(minimum, maximum, resolution) {
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
  auto numCells = mDataGrid.getNumCells();
  mData = new double*[numCells(0)];
  for (size_t i = 0; i < numCells(0); ++i) {
    mData[i] = new double[numCells(1)];
    for (size_t j = 0; j < numCells(1); ++j) {
      mData[i][j] = function(mDataGrid.getCoordinates(
        (Index() << i, j).finished()));
      mDataGrid[(Index() << i, j).finished()] = mData[i][j];
    }
  }
  loadFromData(mData, numCells(0), numCells(1), minimum(0), maximum(0),
    minimum(1), maximum(1));
}

template <typename F>
FunctionPlot<F, 2>::~FunctionPlot() {
  auto numCells = mDataGrid.getNumCells();
  for (size_t i = 0; i < numCells(0); ++i)
    delete []mData[i];
  delete []mData;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename F>
const std::string& FunctionPlot<F, 2>::getTitle() const {
  return mTitle;
}

template <typename F>
const typename FunctionPlot<F, 2>::Domain& FunctionPlot<F, 2>::getMinimum()
    const {
  return mMinimum;
}

template <typename F>
const typename FunctionPlot<F, 2>::Domain& FunctionPlot<F, 2>::getMaximum()
    const {
  return mMaximum;
}

template <typename F>
const typename FunctionPlot<F, 2>::Domain& FunctionPlot<F, 2>::getResolution()
    const {
  return mResolution;
}

template <typename F>
const Grid<typename FunctionPlot<F, 2>::DomainType, double, 2>&
    FunctionPlot<F, 2>::getDataGrid() const {
  return mDataGrid;
}
