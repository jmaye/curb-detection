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
