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

#include "visualization/DEMControl.h"

#include "visualization/PointCloudControl.h"
#include "base/Timestamp.h"
#include "data-structures/TransGrid.h"
#include "data-structures/Cell.h"

#include "ui_DEMControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

DEMControl::DEMControl(bool showDEM) :
    mUi(new Ui_DEMControl()),
    mDEM(0) {
  mUi->setupUi(this);
  mUi->colorChooser->setPalette(&mPalette);
  connect(&mPalette, SIGNAL(colorChanged(const QString&, const QColor&)),
    this, SLOT(colorChanged(const QString&, const QColor&)));
  connect(&View3d::getInstance().getScene(), SIGNAL(render(View3d&, Scene3d&)),
    this, SLOT(render(View3d&, Scene3d&)));
  connect(&PointCloudControl::getInstance(),
    SIGNAL(pointCloudRead(const PointCloud<double, 3>&)), this,
    SLOT(pointCloudRead(const PointCloud<double, 3>&)));
  setLineColor(Qt::black);
  setLineSize(1.0);
  setShowDEM(showDEM);
  setSmoothLines(true);
  mUi->numCellsXSpinBox->setValue(0);
  mUi->numCellsYSpinBox->setValue(0);
}

DEMControl::~DEMControl() {
  if (mDEM)
    delete mDEM;
  delete mUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void DEMControl::setLineColor(const QColor& color) {
  mPalette.setColor("DEM", color);
}

void DEMControl::setLineSize(double lineSize) {
  mUi->lineSizeSpinBox->setValue(lineSize);
  View3d::getInstance().update();
}

void DEMControl::setShowDEM(bool showDEM) {
  mUi->showDEMCheckBox->setChecked(showDEM);
  View3d::getInstance().update();
}

void DEMControl::setSmoothLines(bool smoothLines) {
  mUi->smoothLinesCheckBox->setChecked(smoothLines);
  View3d::getInstance().update();
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void DEMControl::renderDEM(double size, bool smooth) {
  glPushAttrib(GL_CURRENT_BIT);
  if (size > 1.0)
    glLineWidth(size);
  else
    glLineWidth(1.0);
  if (smooth)
    glEnable(GL_LINE_SMOOTH);
  else
    glDisable(GL_LINE_SMOOTH);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBegin(GL_QUADS);
  View3d::getInstance().setColor(mPalette, "DEM");
  const Grid<double, Cell, 2>::Index& numCells = mDEM->getNumCells();
  for (size_t i = 0; i < numCells(0); ++i)
    for (size_t j = 0; j < numCells(1); ++j) {
      const Grid<double, Cell, 2>::Index
        index((Grid<double, Cell, 2>::Index() << i, j).finished());
      const Cell& cell = (*mDEM)[index];
      if (!cell.getHeightEstimator().getDist().getKappa())
        continue;
      const double sampleMean =
        std::get<0>(cell.getHeightEstimator().getDist().getMode());
      const Grid<double, Cell, 2>::Coordinate ulPoint =
        mDEM->getULCoordinates(index);
      const Grid<double, Cell, 2>::Coordinate urPoint =
        mDEM->getURCoordinates(index);
      const Grid<double, Cell, 2>::Coordinate lrPoint =
        mDEM->getLRCoordinates(index);
      const Grid<double, Cell, 2>::Coordinate llPoint =
        mDEM->getLLCoordinates(index);
      glVertex3f(ulPoint(0), ulPoint(1), sampleMean);
      glVertex3f(urPoint(0), urPoint(1), sampleMean);
      glVertex3f(lrPoint(0), lrPoint(1), sampleMean);
      glVertex3f(llPoint(0), llPoint(1), sampleMean);
    }
  glEnd();
  glLineWidth(1.0);
  glDisable(GL_LINE_SMOOTH);
  glPopAttrib();
}

void DEMControl::colorChanged(const QString& role, const QColor& color) {
  View3d::getInstance().update();
}

void DEMControl::lineSizeChanged(double lineSize) {
  setLineSize(lineSize);
}

void DEMControl::showDEMToggled(bool checked) {
  setShowDEM(checked);
}

void DEMControl::smoothLinesToggled(bool checked) {
  setSmoothLines(checked);
}

void DEMControl::demChanged() {
  const double minX = mUi->rangeMinXSpinBox->value();
  const double minY = mUi->rangeMinYSpinBox->value();
  const double maxX = mUi->rangeMaxXSpinBox->value();
  const double maxY = mUi->rangeMaxYSpinBox->value();
  const double cellSizeX = mUi->resXSpinBox->value();
  const double cellSizeY = mUi->resYSpinBox->value();
  const double sensorVariance = mUi->sensorSpinBox->value();
  const double before = Timestamp::now();
  if (mDEM)
    delete mDEM;
  mDEM = new
    TransGrid<double, Cell, 2>(Eigen::Matrix<double, 2, 1>(minX, minY),
    Eigen::Matrix<double, 2, 1>(maxX, maxY),
    Eigen::Matrix<double, 2, 1>(cellSizeX, cellSizeY));
  mUi->numCellsXSpinBox->setValue(mDEM->getNumCells()(0));
  mUi->numCellsYSpinBox->setValue(mDEM->getNumCells()(1));
  for (auto it = mPointCloud.getPointBegin(); it != mPointCloud.getPointEnd();
      ++it) {
    const Eigen::Matrix<double, 2, 1> point = (*it).segment(0, 2);
    if (mDEM->isInRange(point)) {
      if (!(*mDEM)(point).getHeightEstimator().getDist().getKappa())
        (*mDEM)(point).setSensorVariance(sensorVariance);
      (*mDEM)(point).addPoint((*it)(2));
    }
  }
  const double after = Timestamp::now();
  mUi->timeSpinBox->setValue(after - before);
  View3d::getInstance().update();
  emit demUpdated(*mDEM);
}

void DEMControl::pointCloudRead(const PointCloud<double, 3>& pointCloud) {
  mPointCloud = pointCloud;
  mUi->showDEMCheckBox->setEnabled(true);
  demChanged();
}

void DEMControl::render(View3d& view, Scene3d& scene) {
  if (mUi->showDEMCheckBox->isChecked() && mDEM)
    renderDEM(mUi->lineSizeSpinBox->value(),
      mUi->smoothLinesCheckBox->isChecked());
}
