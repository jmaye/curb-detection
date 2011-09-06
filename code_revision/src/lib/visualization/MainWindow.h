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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "visualization/Control.h"

#include <QtGui/QMainWindow>

class Ui_MainWindow;

class MainWindow :
  public QMainWindow {
Q_OBJECT

public:
  MainWindow();
  ~MainWindow();

  void addControl(const QString& title, Control& control);

protected:
  Ui_MainWindow* mpUi;

};

#endif // MAINWINDOW_H
