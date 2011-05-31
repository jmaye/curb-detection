#include "visualization/DEMControl.h"

#include "visualization/PointCloudControl.h"

#include "ui_DEMControl.h"

#include <iostream>
#include <fstream>

#include <stdint.h>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

DEMControl::DEMControl(bool bShowDEM) :
  mpUi(new Ui_DEMControl()),
  mpPointCloud(0) {
  mpUi->setupUi(this);

  mpUi->colorChooser->setPalette(&mPalette);
  connect(&mPalette, SIGNAL(colorChanged(const QString&, const QColor&)),
    this, SLOT(colorChanged(const QString&, const QColor&)));

  connect(&GLView::getInstance(), SIGNAL(render(GLView&)), this,
    SLOT(render(GLView&)));

  connect(&PointCloudControl::getInstance(),
    SIGNAL(pointCloudRead(const PointCloud*)), this,
    SLOT(pointCloudRead(const PointCloud*)));

  setLineColor(Qt::gray);

  setLineSize(1.0);
  setShowDEM(bShowDEM);
  setSmoothLines(true);

  double f64X = mpUi->xSpinBox->value();
  double f64Y = mpUi->ySpinBox->value();
  double f64CellSizeX = mpUi->cellSizeXSpinBox->value();
  double f64CellSizeY = mpUi->cellSizeYSpinBox->value();
  double f64HeightFilterMin = mpUi->heightFilterMinSpinBox->value();
  double f64HeightFilterMax = mpUi->heightFilterMaxSpinBox->value();
  uint32_t u32CellsNbrX = mpUi->cellNbrXSpinBox->value();
  uint32_t u32CellsNbrY = mpUi->cellNbrYSpinBox->value();
  mpDEM = new DEM(f64CellSizeX, f64CellSizeY, u32CellsNbrX, u32CellsNbrY,
    f64HeightFilterMin, f64HeightFilterMax, f64X, f64Y);
}

DEMControl::~DEMControl() {
  delete mpDEM;
  delete mpUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void DEMControl::setLineColor(const QColor& color) {
  mPalette.setColor("DEM", color);
}

void DEMControl::setLineSize(double f64LineSize) {
  mpUi->lineSizeSpinBox->setValue(f64LineSize);
  GLView::getInstance().update();
}

void DEMControl::setShowDEM(bool bShowDEM) {
  mpUi->showDEMCheckBox->setChecked(bShowDEM);
  GLView::getInstance().update();
}

void DEMControl::setSmoothLines(bool bSmoothLines) {
  mpUi->smoothLinesCheckBox->setChecked(bSmoothLines);
  GLView::getInstance().update();
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void DEMControl::renderDEM(double f64Size, bool bSmooth) {
  if (f64Size > 1.0)
    glLineWidth(f64Size);
  else
    glLineWidth(1.0);

  if (bSmooth)
    glEnable(GL_LINE_SMOOTH);
  else
    glDisable(GL_LINE_SMOOTH);

  glBegin(GL_LINES);
  GLView::getInstance().setColor(mPalette, "DEM");
  for (uint32_t i = 0; i < mpDEM->getCellsNbrX(); i++) {
    for (uint32_t j =  0; j < mpDEM->getCellsNbrY(); j++) {
      Point2D cellCenter = (*(const DEM*)mpDEM)(i, j).getCellCenter();
      Point2D cellSize = (*(const DEM*)mpDEM)(i, j).getCellSize();
      double f64CellHeightMean = (*(const DEM*)mpDEM)(i, j).getHeightDist().
        getMean();

      glVertex3f(cellCenter.mf64X + cellSize.mf64X / 2.0,
        cellCenter.mf64Y + cellSize.mf64Y / 2.0, f64CellHeightMean);
      glVertex3f(cellCenter.mf64X + cellSize.mf64X / 2.0,
        cellCenter.mf64Y - cellSize.mf64Y / 2.0, f64CellHeightMean);
      glVertex3f(cellCenter.mf64X - cellSize.mf64X / 2.0,
        cellCenter.mf64Y - cellSize.mf64Y / 2.0, f64CellHeightMean);
      glVertex3f(cellCenter.mf64X - cellSize.mf64X / 2.0,
        cellCenter.mf64Y + cellSize.mf64Y / 2.0, f64CellHeightMean);

      glVertex3f(cellCenter.mf64X + cellSize.mf64X / 2.0,
        cellCenter.mf64Y + cellSize.mf64Y / 2.0, f64CellHeightMean);
      glVertex3f(cellCenter.mf64X - cellSize.mf64X / 2.0,
        cellCenter.mf64Y + cellSize.mf64Y / 2.0, f64CellHeightMean);
      glVertex3f(cellCenter.mf64X + cellSize.mf64X / 2.0,
        cellCenter.mf64Y - cellSize.mf64Y / 2.0, f64CellHeightMean);
      glVertex3f(cellCenter.mf64X - cellSize.mf64X / 2.0,
        cellCenter.mf64Y - cellSize.mf64Y / 2.0, f64CellHeightMean);

    }
  }
  glEnd();

  glLineWidth(1.0);
  glDisable(GL_LINE_SMOOTH);
}

void DEMControl::colorChanged(const QString& role, const QColor& color) {
  GLView::getInstance().update();
}

void DEMControl::lineSizeChanged(double f64LineSize) {
  setLineSize(f64LineSize);
}

void DEMControl::showDEMToggled(bool bChecked) {
  setShowDEM(bChecked);
}

void DEMControl::smoothLinesToggled(bool bChecked) {
  setSmoothLines(bChecked);
}

void DEMControl::demChanged() {
  double f64X = mpUi->xSpinBox->value();
  double f64Y = mpUi->ySpinBox->value();
  double f64CellSizeX = mpUi->cellSizeXSpinBox->value();
  double f64CellSizeY = mpUi->cellSizeYSpinBox->value();
  double f64HeightFilterMin = mpUi->heightFilterMinSpinBox->value();
  double f64HeightFilterMax = mpUi->heightFilterMaxSpinBox->value();
  uint32_t u32CellsNbrX = mpUi->cellNbrXSpinBox->value();
  uint32_t u32CellsNbrY = mpUi->cellNbrYSpinBox->value();
  delete mpDEM;
  mpDEM = new DEM(f64CellSizeX, f64CellSizeY, u32CellsNbrX, u32CellsNbrY,
    f64HeightFilterMin, f64HeightFilterMax, f64X, f64Y);
  if (mpPointCloud != 0) {
    mpDEM->addPointCloud(*mpPointCloud);
    emit demUpdated(mpDEM);
  }
  GLView::getInstance().update();
}

void DEMControl::pointCloudRead(const PointCloud* pPointCloud) {
  mpPointCloud = pPointCloud;
  demChanged();
  GLView::getInstance().update();
}

void DEMControl::render(GLView& view) {
  if (mpUi->showDEMCheckBox->isChecked())
    renderDEM(mpUi->lineSizeSpinBox->value(),
      mpUi->smoothLinesCheckBox->isChecked());
}
