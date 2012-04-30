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

#include <QtCore/QVector>
#include <qwt-qt4/qwt_plot_canvas.h>
#include <qwt-qt4/qwt_symbol.h>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename F>
FunctionPlot<F, 1>::FunctionPlot(const std::string& title, const F& function,
    const Domain& minimum, const Domain& maximum, const Domain& resolution) :
    mTitle(title),
    mMinimum(minimum),
    mMaximum(maximum),
    mResolution(resolution),
    mDataGrid((Coordinate() << minimum).finished(),
      (Coordinate() << maximum).finished(),
      (Coordinate() << resolution).finished()),
    mPanner(canvas()),
    mMagnifier(canvas()) {
  QVector<double> xData;
  QVector<double> yData;
  auto numCells = mDataGrid.getNumCells();
  xData.reserve(numCells(0));
  yData.reserve(numCells(0));
  for (Index i = Index::Zero(numCells.size()); i != numCells;
      mDataGrid.incrementIndex(i)) {
    mDataGrid[i] = function(mDataGrid.getCoordinates(i)(0));
    xData.push_back(mDataGrid.getCoordinates(i)(0));
    yData.push_back(mDataGrid[i]);
  }
  mCurve.setData(xData, yData);
  Traits::template setCurveStyle<DomainType, true>(mCurve);
  mCurve.attach(this);
  mGrid.enableX(true);
  mGrid.enableY(true);
  mGrid.enableXMin(false);
  mGrid.enableYMin(false);
  mGrid.setMajPen(QPen(Qt::black, 0, Qt::DotLine));
  mGrid.attach(this);
  QwtPlot::setTitle(QString(title.c_str()));
  canvas()->setLineWidth(2);
  QPalette palette = canvas()->palette();
  palette.setColor(backgroundRole(), Qt::white);
  canvas()->setPalette(palette);
  canvas()->setAutoFillBackground(true);
  setAxisTitle(QwtPlot::xBottom, QString('x'));
  setAxisTitle(QwtPlot::yLeft, QString('y'));
  replot();
}

template <typename F>
FunctionPlot<F, 1>::~FunctionPlot() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename F>
const std::string& FunctionPlot<F, 1>::getTitle() const {
  return mTitle;
}

template <typename F>
const typename FunctionPlot<F, 1>::Domain& FunctionPlot<F, 1>::getMinimum()
    const {
  return mMinimum;
}

template <typename F>
const typename FunctionPlot<F, 1>::Domain& FunctionPlot<F, 1>::getMaximum()
    const {
  return mMaximum;
}

template <typename F>
const typename FunctionPlot<F, 1>::Domain& FunctionPlot<F, 1>::getResolution()
    const {
  return mResolution;
}

template <typename F>
const Grid<typename FunctionPlot<F, 1>::DomainType, double, 1>&
    FunctionPlot<F, 1>::getDataGrid() const {
  return mDataGrid;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

template <typename F>
template <typename Z, typename IsReal<Z>::Result::Numeric>
void FunctionPlot<F, 1>::Traits::setCurveStyle(QwtPlotCurve& curve) {
  curve.setPen(QPen(QColor(Qt::blue)));
  curve.setStyle(QwtPlotCurve::Lines);
}

template <typename F>
template <typename Z, typename IsInteger<Z>::Result::Numeric>
void FunctionPlot<F, 1>::Traits::setCurveStyle(QwtPlotCurve& curve) {
  curve.setStyle(QwtPlotCurve::Lines);
  curve.setPen(QPen(QBrush(QColor(Qt::blue)), 1, Qt::DotLine));
  curve.setSymbol(QwtSymbol(QwtSymbol::Star1, Qt::NoBrush,
    QPen(Qt::black), QSize(10, 10)));
}
