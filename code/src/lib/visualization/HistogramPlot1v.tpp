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

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename T>
HistogramPlot<T, 1>::HistogramPlot(const std::string& title, const
    Histogram<T, 1>& histogram) :
    mTitle(title),
    mHistogram(histogram),
    mPanner(canvas()),
    mMagnifier(canvas()) {
  QVector<double> xData;
  QVector<double> yData;
  auto numCells = mHistogram.getNumCells();
  xData.reserve(numCells(0));
  yData.reserve(numCells(0));
  for (auto i = (typename Histogram<T, 1>::Index() << 0).finished();
      i != numCells; mHistogram.incrementIndex(i))
    if (mHistogram[i]) {
      xData.push_back(mHistogram.getCoordinates(i)(0));
      yData.push_back(mHistogram[i]);
    }
  mCurve.setData(xData, yData);
  mCurve.setBrush(QBrush(QColor(Qt::blue)));
  mCurve.setPen(QPen(QColor(Qt::blue), 10));
  mCurve.setStyle(QwtPlotCurve::Sticks);
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

template <typename T>
HistogramPlot<T, 1>::~HistogramPlot() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <typename T>
const std::string& HistogramPlot<T, 1>::getTitle() const {
  return mTitle;
}

template <typename T>
const Histogram<T, 1>& HistogramPlot<T, 1>::getHistogram() const {
  return mHistogram;
}
