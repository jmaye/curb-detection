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

template <typename Y, typename X>
DiscreteFunctionPlot<Y, X, 1>::DiscreteFunctionPlot(const std::string& title,
  const DiscreteFunction<Y, X>& function, const X& minimum, const X& maximum)
  throw (BadArgumentException<X>) :
  FunctionPlot<Y, X>(title, minimum, maximum),
  QwtPlot(0),
  mPanner(canvas()),
  mMagnifier(canvas()) {
  if (maximum < minimum)
    throw BadArgumentException<X>(maximum,
      "DiscreteFunctionPlot<Y, X, 1>::DiscreteFunctionPlot(): "
      "maximum must be larger than minimum",
      __FILE__, __LINE__);
  QwtPlot::setTitle(QString(title.c_str()));
  mXData.resize(maximum - minimum + 1);
  mYData.resize(maximum - minimum + 1);
  X xValue = minimum;
  for (size_t i = 0; i < (size_t)mXData.size(); ++i) {
    mXData[i] = xValue;
    mYData[i] = function(xValue);
    xValue++;
  }
  mCurve.setData(mXData, mYData);
  mCurve.setStyle(QwtPlotCurve::Lines);
  mCurve.setPen(QPen(QBrush(QColor(Qt::blue)), 1, Qt::DotLine));
  //mCurve.setBrush(QBrush(QColor(Qt::blue)));
  mCurve.setSymbol(QwtSymbol(QwtSymbol::Star1, Qt::NoBrush,
    QPen(Qt::black), QSize(10, 10)));
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
  //setFixedSize(sizeHint());
}

template <typename Y, typename X>
DiscreteFunctionPlot<Y, X, 1>::~DiscreteFunctionPlot() {
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

template <typename Y, typename X>
void DiscreteFunctionPlot<Y, X, 1>::show() {
  QWidget::show();
}
