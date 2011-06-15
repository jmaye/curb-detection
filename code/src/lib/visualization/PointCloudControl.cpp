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

#include "ui_PointCloudControl.h"

#include <QtGui/QFileDialog>

#include <fstream>

#include <stdint.h>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

PointCloudControl::PointCloudControl(bool bShowPoints) :
  mpUi(new Ui_PointCloudControl()) {
  mpUi->setupUi(this);

  mpUi->colorChooser->setPalette(&mPalette);

  connect(&mPalette, SIGNAL(colorChanged(const QString&, const QColor&)),
    this, SLOT(colorChanged(const QString&, const QColor&)));

  connect(&GLView::getInstance().getScene(), SIGNAL(render(GLView&, Scene&)),
    this, SLOT(render(GLView&, Scene&)));

  setPointColor(Qt::gray);

  setPointSize(1.0);
  setShowPoints(bShowPoints);
  setSmoothPoints(true);

  setLogFilename(mpUi->logEdit->text());
}

PointCloudControl::~PointCloudControl() {
  delete mpUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void PointCloudControl::setPointColor(const QColor& color) {
  mPalette.setColor("Point", color);
}

void PointCloudControl::setPointSize(double f64PointSize) {
  mpUi->pointSizeSpinBox->setValue(f64PointSize);
  GLView::getInstance().update();
}

void PointCloudControl::setShowPoints(bool bShowPoints) {
  mpUi->showPointsCheckBox->setChecked(bShowPoints);
  GLView::getInstance().update();
}

void PointCloudControl::setSmoothPoints(bool bSmoothPoints) {
  mpUi->smoothPointsCheckBox->setChecked(bSmoothPoints);
  GLView::getInstance().update();
}

void PointCloudControl::setLogFilename(const QString& filename) {
  mpUi->logEdit->setText(filename);

  QFileInfo fileInfo(filename);
  if (fileInfo.isFile() && fileInfo.isReadable()) {
    std::ifstream pointCloudFile(filename.toAscii().constData());
    pointCloudFile >> mPointCloud;
    mpUi->showPointsCheckBox->setEnabled(true);
    GLView::getInstance().update();
    emit pointCloudRead(&mPointCloud);
  }
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void PointCloudControl::renderPoints(double f64Size, bool bSmooth) {
  glPushAttrib(GL_CURRENT_BIT);

  if (f64Size > 1.0)
    glPointSize(f64Size);
  else
    glPointSize(1.0);

  if (bSmooth)
    glEnable(GL_POINT_SMOOTH);
  else
    glDisable(GL_POINT_SMOOTH);

  glBegin(GL_POINTS);
  GLView::getInstance().setColor(mPalette, "Point");
  for (uint32_t i = 0; i < mPointCloud.getSize(); i++)
    glVertex3f(mPointCloud[i].mf64X, mPointCloud[i].mf64Y,
      mPointCloud[i].mf64Z);
  glEnd();

  glPointSize(1.0);
  glDisable(GL_POINT_SMOOTH);

  glPopAttrib();
}

void PointCloudControl::logBrowseClicked() {
  QString filename = QFileDialog::getOpenFileName(this,
    "Open Log File", mpUi->logEdit->text(),
    "Point cloud log files (*.*)");

  if (!filename.isNull())
    setLogFilename(filename);
}

void PointCloudControl::colorChanged(const QString& role, const QColor& color) {
  GLView::getInstance().update();
}

void PointCloudControl::pointSizeChanged(double f64PointSize) {
  setPointSize(f64PointSize);
}

void PointCloudControl::showPointsToggled(bool bChecked) {
  setShowPoints(bChecked);
}

void PointCloudControl::smoothPointsToggled(bool bChecked) {
  setSmoothPoints(bChecked);
}

void PointCloudControl::render(GLView& view, Scene& scene) {
  if (mpUi->showPointsCheckBox->isChecked())
    renderPoints(mpUi->pointSizeSpinBox->value(),
      mpUi->smoothPointsCheckBox->isChecked());
}
