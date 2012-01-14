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

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ScatterPlot<2>::ScatterPlot(const std::string& title, const
  std::vector<Eigen::Matrix<double, 2, 1> >& data) :
  QwtPlot(0),
  mPanner(canvas()),
  mMagnifier(canvas()) {
  QwtPlot::setTitle(QString(title.c_str()));
  mXData.resize(data.size());
  mYData.resize(data.size());
  for (size_t i = 0; i < data.size(); ++i) {
    mXData[i] = data[i](0);
    mYData[i] = data[i](1);
  }
  mCurve.setData(mXData, mYData);
  mCurve.setPen(QPen(QColor(Qt::blue)));
  mCurve.setStyle(QwtPlotCurve::Dots);
  mCurve.attach(this);
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

ScatterPlot<2>::~ScatterPlot() {
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void ScatterPlot<2>::show() {
  QWidget::show();
}
