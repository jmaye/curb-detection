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

/** \file MainWindow.h
    \brief This file defines the main Qt window.
  */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include "visualization/Control.h"

class Ui_MainWindow;

/** The MainWindow class represents the Qt main window.
    \brief Qt main window
  */
class MainWindow :
  public QMainWindow {
Q_OBJECT
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  MainWindow(const MainWindow& other);
  /// Assignment operator
  MainWindow& operator = (const MainWindow& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs control with parameter
  MainWindow();
  /// Destructor
  ~MainWindow();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Adds a control to the main window
  void addControl(const QString& title, Control& control);
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Qt user interface
  Ui_MainWindow* mUi;
  /** @}
    */

};

#endif // MAINWINDOW_H
