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
