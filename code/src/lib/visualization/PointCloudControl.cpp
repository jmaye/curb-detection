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

#include "visualization/PointCloudControl.h"

#include <fstream>

#include <QtGui/QFileDialog>

#include "ui_PointCloudControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

PointCloudControl::PointCloudControl(bool showPoints) :
  mUi(new Ui_PointCloudControl()) {
  mUi->setupUi(this);
  mUi->colorChooser->setPalette(&mPalette);
  connect(&mPalette, SIGNAL(colorChanged(const QString&, const QColor&)),
    this, SLOT(colorChanged(const QString&, const QColor&)));
  connect(&View3d::getInstance().getScene(), SIGNAL(render(View3d&, Scene3d&)),
    this, SLOT(render(View3d&, Scene3d&)));
  setPointColor(Qt::gray);
  setPointSize(1.0);
  setShowPoints(showPoints);
  setSmoothPoints(true);
  setLogFilename(mUi->logEdit->text());
}

PointCloudControl::~PointCloudControl() {
  delete mUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void PointCloudControl::setPointColor(const QColor& color) {
  mPalette.setColor("Point", color);
}

void PointCloudControl::setPointSize(double pointSize) {
  mUi->pointSizeSpinBox->setValue(pointSize);
  View3d::getInstance().update();
}

void PointCloudControl::setShowPoints(bool showPoints) {
  mUi->showPointsCheckBox->setChecked(showPoints);
  View3d::getInstance().update();
}

void PointCloudControl::setSmoothPoints(bool smoothPoints) {
  mUi->smoothPointsCheckBox->setChecked(smoothPoints);
  View3d::getInstance().update();
}

void PointCloudControl::setLogFilename(const QString& filename) {
  mUi->logEdit->setText(filename);
  QFileInfo fileInfo(filename);
  if (fileInfo.isFile() && fileInfo.isReadable()) {
    std::ifstream pointCloudFile(filename.toAscii().constData());
    pointCloudFile >> mPointCloud;
    mUi->showPointsCheckBox->setEnabled(true);
    View3d::getInstance().update();
    emit pointCloudRead(mPointCloud);
    emit pointCloudRead(filename.toStdString());
  }
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void PointCloudControl::renderPoints(double size, bool smooth) {
  glPushAttrib(GL_CURRENT_BIT);
  if (size > 1.0)
    glPointSize(size);
  else
    glPointSize(1.0);
  if (smooth)
    glEnable(GL_POINT_SMOOTH);
  else
    glDisable(GL_POINT_SMOOTH);
  glBegin(GL_POINTS);
  View3d::getInstance().setColor(mPalette, "Point");
  for (auto it = mPointCloud.getPointBegin(); it != mPointCloud.getPointEnd();
      ++it)
    glVertex3f((*it)(0), (*it)(1), (*it)(2));
  glEnd();
  glPointSize(1.0);
  glDisable(GL_POINT_SMOOTH);
  glPopAttrib();
}

void PointCloudControl::logBrowseClicked() {
  QString filename = QFileDialog::getOpenFileName(this,
    "Open Log File", mUi->logEdit->text(),
    "Point cloud log files (*.*)");
  if (!filename.isNull())
    setLogFilename(filename);
}

void PointCloudControl::colorChanged(const QString& role, const QColor& color) {
  View3d::getInstance().update();
}

void PointCloudControl::pointSizeChanged(double pointSize) {
  setPointSize(pointSize);
}

void PointCloudControl::showPointsToggled(bool checked) {
  setShowPoints(checked);
}

void PointCloudControl::smoothPointsToggled(bool checked) {
  setSmoothPoints(checked);
}

void PointCloudControl::render(View3d& view, Scene3d& scene) {
  if (mUi->showPointsCheckBox->isChecked())
    renderPoints(mUi->pointSizeSpinBox->value(),
      mUi->smoothPointsCheckBox->isChecked());
}
