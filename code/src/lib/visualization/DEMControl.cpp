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

#include "ui_DEMControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

DEMControl::DEMControl(bool showDEM) :
  mUi(new Ui_DEMControl()),
  mDEM(Grid<double, Cell, 2>::Coordinate(0.0, 0.0),
    Grid<double, Cell, 2>::Coordinate(4.0, 4.0),
    Grid<double, Cell, 2>::Coordinate(0.1, 0.1)) {
  mUi->setupUi(this);
  mUi->colorChooser->setPalette(&mPalette);
  connect(&mPalette, SIGNAL(colorChanged(const QString&, const QColor&)),
    this, SLOT(colorChanged(const QString&, const QColor&)));
  connect(&GLView::getInstance().getScene(), SIGNAL(render(GLView&, Scene&)),
    this, SLOT(render(GLView&, Scene&)));
  connect(&PointCloudControl::getInstance(),
    SIGNAL(pointCloudRead(const PointCloud<double, 3>&)), this,
    SLOT(pointCloudRead(const PointCloud<double, 3>&)));
  setLineColor(Qt::black);
  setLineSize(1.0);
  setShowDEM(showDEM);
  setSmoothLines(true);
  const double minX = mUi->rangeMinXSpinBox->value();
  const double minY = mUi->rangeMinYSpinBox->value();
  const double maxX = mUi->rangeMaxXSpinBox->value();
  const double maxY = mUi->rangeMaxYSpinBox->value();
  const double cellSizeX = mUi->resXSpinBox->value();
  const double cellSizeY = mUi->resYSpinBox->value();
  mDEM = Grid<double, Cell, 2>(Grid<double, Cell, 2>::Coordinate(minX, minY),
    Grid<double, Cell, 2>::Coordinate(maxX, maxY),
    Grid<double, Cell, 2>::Coordinate(cellSizeX, cellSizeY));
  mUi->numCellsXSpinBox->setValue(mDEM.getNumCells()(0));
  mUi->numCellsYSpinBox->setValue(mDEM.getNumCells()(1));
}

DEMControl::~DEMControl() {
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
  GLView::getInstance().update();
}

void DEMControl::setShowDEM(bool showDEM) {
  mUi->showDEMCheckBox->setChecked(showDEM);
  GLView::getInstance().update();
}

void DEMControl::setSmoothLines(bool smoothLines) {
  mUi->smoothLinesCheckBox->setChecked(smoothLines);
  GLView::getInstance().update();
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
  GLView::getInstance().setColor(mPalette, "DEM");
  const Grid<double, Cell, 2>::Coordinate& resolution = mDEM.getResolution();
  const Grid<double, Cell, 2>::Index& numCells = mDEM.getNumCells();
  for (size_t i = 0; i < numCells(0); ++i)
    for (size_t j = 0; j < numCells(1); ++j) {
      const Eigen::Matrix<double, 2, 1> point = 
        mDEM.getCoordinates((Eigen::Matrix<size_t, 2, 1>() << i, j).finished());
      const Cell& cell =
        mDEM[(Eigen::Matrix<size_t, 2, 1>() << i, j).finished()];
      const double sampleMean = cell.getHeightEstimator().getPostPredDist()
        .getMean();
      if (cell.getHeightEstimator().getValid() == false)
        continue;
      glVertex3f(point(0) + resolution(0) / 2.0, point(1) + resolution(1) / 2.0,
        sampleMean);
      glVertex3f(point(0) + resolution(0) / 2.0, point(1) - resolution(1) / 2.0,
        sampleMean);
      glVertex3f(point(0) - resolution(0) / 2.0, point(1) - resolution(1) / 2.0,
        sampleMean);
      glVertex3f(point(0) - resolution(0) / 2.0, point(1) + resolution(1) / 2.0,
        sampleMean);
    }
  glEnd();
  glLineWidth(1.0);
  glDisable(GL_LINE_SMOOTH);
  glPopAttrib();
}

void DEMControl::colorChanged(const QString& role, const QColor& color) {
  GLView::getInstance().update();
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
  const double before = Timestamp::now();
  mDEM = Grid<double, Cell, 2>(Eigen::Matrix<double, 2, 1>(minX, minY),
    Eigen::Matrix<double, 2, 1>(maxX, maxY),
    Eigen::Matrix<double, 2, 1>(cellSizeX, cellSizeY));
  mUi->numCellsXSpinBox->setValue(mDEM.getNumCells()(0));
  mUi->numCellsYSpinBox->setValue(mDEM.getNumCells()(1));
  for (PointCloud<double, 3>::ConstPointIterator it =
    mPointCloud.getPointBegin(); it != mPointCloud.getPointEnd(); ++it) {
    const Eigen::Matrix<double, 2, 1> point = (*it).segment(0, 2);
    if (mDEM.isInRange(point))
      mDEM(point).addPoint((*it)(2));
  }
  const double after = Timestamp::now();
  mUi->timeSpinBox->setValue(after - before);

  double mean = 0;
  double variance = 0;
  size_t count = 0;
  const Grid<double, Cell, 2>::Index& numCells = mDEM.getNumCells();
  for (size_t i = 0; i < numCells(0); ++i)
    for (size_t j = 0; j < numCells(1); ++j) {
      const Eigen::Matrix<double, 2, 1> point = 
        mDEM.getCoordinates((Eigen::Matrix<size_t, 2, 1>() << i, j).finished());
      const Cell& cell =
        mDEM[(Eigen::Matrix<size_t, 2, 1>() << i, j).finished()];
      const double sampleMean = cell.getHeightEstimator().getPostPredDist()
        .getMean();
      const double sampleVariance = cell.getHeightEstimator().getPostPredDist()
        .getVariance();
      if (cell.getHeightEstimator().getValid()) {
        mean += sampleMean;
        variance += sampleVariance;
        count++;
      }
    }
  mean /= count;
  variance /= count;
  for (size_t i = 0; i < numCells(0); ++i)
    for (size_t j = 0; j < numCells(1); ++j) {
      const Eigen::Matrix<double, 2, 1> point = 
        mDEM.getCoordinates((Eigen::Matrix<size_t, 2, 1>() << i, j).finished());
      Cell& cell =
        mDEM[(Eigen::Matrix<size_t, 2, 1>() << i, j).finished()];
      const double sampleMean = cell.getHeightEstimator().getPostPredDist()
        .getMean();
      if (cell.getHeightEstimator().getValid()) {
        if (NormalDistribution<1>(mean, variance)(sampleMean) == 0) {
          cell.reset();
        }
      }
    }

  GLView::getInstance().update();
  emit demUpdated(mDEM);
}

void DEMControl::pointCloudRead(const PointCloud<double, 3>& pointCloud) {
  mPointCloud = pointCloud;
  mUi->showDEMCheckBox->setEnabled(true);
  demChanged();
}

void DEMControl::render(GLView& view, Scene& scene) {
  if (mUi->showDEMCheckBox->isChecked())
    renderDEM(mUi->lineSizeSpinBox->value(),
      mUi->smoothLinesCheckBox->isChecked());
}
