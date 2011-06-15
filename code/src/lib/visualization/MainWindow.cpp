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

#include "visualization/MainWindow.h"

#include "ui_MainWindow.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

MainWindow::MainWindow() :
  mpUi(new Ui_MainWindow()) {
  mpUi->setupUi(this);

  while (mpUi->toolBox->count())
    mpUi->toolBox->removeItem(0);
}

MainWindow::~MainWindow() {
  delete mpUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void MainWindow::addControl(const QString& title, Control& control) {
  mpUi->toolBox->addItem(&control, title);
  if (!control.getMenu().isEmpty())
    mpUi->menuBar->addMenu(&control.getMenu())->setText(title);
}
