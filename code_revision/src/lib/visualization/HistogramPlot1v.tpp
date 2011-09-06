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

#include <QtCore/QString>
#include <qwt-qt4/qwt_plot_canvas.h>
#include <qwt-qt4/qwt_symbol.h>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename T>
HistogramPlot<T, 1>::HistogramPlot(const std::string& title, const
  Histogram<T, 1>& histogram) :
  QwtPlot(0),
  mPanner(canvas()),
  mMagnifier(canvas()) {
  QwtPlot::setTitle(QString(title.c_str()));
  mXData.resize(histogram.getNumBins() + 1);
  mYData.resize(histogram.getNumBins() + 1);
  mXData[0] = histogram.getBinStart(0);
  mYData[0] = histogram.getBinContent(0);
  for (size_t i = 0; i < histogram.getNumBins(); ++i) {
    mXData[i + 1] = histogram.getBinStart(i) + histogram.getBinWidth();
    mYData[i + 1] = histogram.getBinContent(i);
  }
  mHistogram.setData(mXData, mYData);
  mHistogram.setBrush(QBrush(QColor(Qt::blue)));
  mHistogram.setPen(QPen(QColor(Qt::blue)));
  mHistogram.setStyle(QwtPlotCurve::Steps);
  mHistogram.attach(this);
  mGrid.enableX(true);
  mGrid.enableY(true);
  mGrid.enableXMin(false);
  mGrid.enableYMin(false);
  mGrid.setMajPen(QPen(Qt::black, 0, Qt::DotLine));
  mGrid.attach(this);
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

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

template <typename T>
void HistogramPlot<T, 1>::show() {
  QWidget::show();
}
