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

#ifndef COLORCHOOSER_H
#define COLORCHOOSER_H

#include "visualization/Palette.h"

#include <QtCore/QSignalMapper>
#include <QtGui/QWidget>
#include <QtGui/QGridLayout>

class ColorChooser :
  public QWidget {
Q_OBJECT

public:
  ColorChooser(QWidget* pParent = 0);
  ~ColorChooser();

  void setPalette(Palette* pPalette);
  Palette* getPalette() const;

protected:
  QGridLayout mLayout;
  QSignalMapper mSignalMapper;
  Palette* mpPalette;

protected slots:
  void buttonClicked(const QString& role);
  void colorChanged(const QString& role, const QColor& color);

};

#endif // COLORCHOOSER_H
