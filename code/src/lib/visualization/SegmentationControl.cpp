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

#include "visualization/SegmentationControl.h"

#include "visualization/DEMControl.h"
#include "base/Timestamp.h"
#include "data-structures/TransGrid.h"
#include "data-structures/Cell.h"
#include "utils/Colors.h"

#include "ui_SegmentationControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

SegmentationControl::SegmentationControl(bool showSegmentation) :
    mUi(new Ui_SegmentationControl()),
    mDEM(0) {
  mUi->setupUi(this);
  connect(&View3d::getInstance().getScene(), SIGNAL(render(View3d&, Scene3d&)),
    this, SLOT(render(View3d&, Scene3d&)));
  connect(&DEMControl::getInstance(),
    SIGNAL(demUpdated(const TransGrid<double, Cell, 2>&)), this,
    SLOT(demUpdated(const TransGrid<double, Cell, 2>&)));
  mK = mUi->kSpinBox->value();
  setShowSegmentation(showSegmentation);
}

SegmentationControl::~SegmentationControl() {
  if (mDEM)
    delete mDEM;
  delete mUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void SegmentationControl::setK(double value) {
  mK = value;
  mUi->kSpinBox->setValue(value);
}

void SegmentationControl::setShowSegmentation(bool showSegmentation) {
  mUi->showSegmentationCheckBox->setChecked(showSegmentation);
  View3d::getInstance().update();
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void SegmentationControl::renderSegmentation() {
  glPushAttrib(GL_CURRENT_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  for (auto it = mComponents.begin(); it != mComponents.end(); ++it) {
    auto color = Colors::genColor(std::distance(mComponents.begin(), it));
    for (auto itV = it->second.getVertexBegin();
        itV != it->second.getVertexEnd(); ++itV) {
      const Cell& cell = (*mDEM)[*itV];
      const double sampleMean =
        std::get<0>(cell.getHeightEstimator().getDist().getMode());
      const Grid<double, Cell, 2>::Coordinate ulPoint =
        mDEM->getULCoordinates(*itV);
      const Grid<double, Cell, 2>::Coordinate urPoint =
        mDEM->getURCoordinates(*itV);
      const Grid<double, Cell, 2>::Coordinate lrPoint =
        mDEM->getLRCoordinates(*itV);
      const Grid<double, Cell, 2>::Coordinate llPoint =
        mDEM->getLLCoordinates(*itV);
      glBegin(GL_QUADS);
      glColor3f(color.mRed, color.mGreen, color.mBlue);
      glVertex3f(ulPoint(0), ulPoint(1), sampleMean);
      glVertex3f(urPoint(0), urPoint(1), sampleMean);
      glVertex3f(lrPoint(0), lrPoint(1), sampleMean);
      glVertex3f(llPoint(0), llPoint(1), sampleMean);
      glEnd();
    }
  }
  glPopAttrib();
}

void SegmentationControl::render(View3d& view, Scene3d& scene) {
  if (mUi->showSegmentationCheckBox->isChecked() && mDEM)
    renderSegmentation();
}

void SegmentationControl::segment() {
  const double before = Timestamp::now();
  DEMGraph* graph = new DEMGraph(*mDEM);
  GraphSegmenter<DEMGraph>::segment(*graph, mComponents, graph->getVertices(),
    mK);
  const double after = Timestamp::now();
  mUi->timeSpinBox->setValue(after - before);
  mUi->showSegmentationCheckBox->setEnabled(true);
  View3d::getInstance().update();
  emit segmentUpdated(*mDEM, *graph, mComponents);
}

void SegmentationControl::demUpdated(const TransGrid<double, Cell, 2>& dem) {
  if (mDEM)
    delete mDEM;
  mDEM = new TransGrid<double, Cell, 2>(dem);
  segment();
}

void SegmentationControl::kChanged(double value) {
  setK(value);
  if (mDEM)
    segment();
}

void SegmentationControl::showSegmentationToggled(bool checked) {
  setShowSegmentation(checked);
}
