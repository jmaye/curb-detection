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

#include "seg-visual/SegmentationControl.h"

#include "visualization/DEMControl.h"
#include "data-structures/Cell.h"
#include "data-structures/DEMGraph.h"
#include "segmenter/GraphSegmenter.h"
#include "statistics/Randomizer.h"

#include "ui_SegmentationControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

SegmentationControl::SegmentationControl(bool showSegmentation) :
  mUi(new Ui_SegmentationControl()),
  mDEM(Eigen::Matrix<double, 2, 1>(0.0, 0.0),
    Eigen::Matrix<double, 2, 1>(4.0, 4.0),
    Eigen::Matrix<double, 2, 1>(0.1, 0.1)) {
  mUi->setupUi(this);
  connect(&GLView::getInstance().getScene(), SIGNAL(render(GLView&, Scene&)),
    this, SLOT(render(GLView&, Scene&)));
  connect(&DEMControl::getInstance(),
    SIGNAL(demUpdated(const Grid<double, Cell, 2>&)), this,
    SLOT(demUpdated(const Grid<double, Cell, 2>&)));
  mK = mUi->kSpinBox->value();
  setShowSegmentation(showSegmentation);
}

SegmentationControl::~SegmentationControl() {
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
  GLView::getInstance().update();
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void SegmentationControl::renderSegmentation() {
  Eigen::Matrix<double, 2, 1> resolution = mDEM.getResolution();
  Eigen::Matrix<size_t, 2, 1> numCells = mDEM.getNumCells();
  glPushAttrib(GL_CURRENT_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  std::tr1::unordered_map<size_t, Component<Grid<double, Cell, 2>::Index,
    double> >::const_iterator it;
  std::vector<Color>::const_iterator itC;
  for (it = mComponents.begin(), itC = mColors.begin(); it != mComponents.end();
    ++it, ++itC) {
    Component<Grid<double, Cell, 2>::Index, double>::ConstVertexIterator itV;
    for (itV = it->second.getVertexBegin(); itV != it->second.getVertexEnd();
      ++itV) {
      Grid<double, Cell, 2>::Index index = *itV;
      Eigen::Matrix<double, 2, 1> point =  mDEM.getCoordinates(index);
      const Cell& cell = mDEM[index];
      double sampleMean = cell.getHeightEstimator().getMean();
      glBegin(GL_POLYGON);
      glColor3f(itC->mRedColor, itC->mGreenColor, itC->mBlueColor);
      glVertex3f(point(0) + resolution(0) / 2.0, point(1) + resolution(1) / 2.0,
        sampleMean);
      glVertex3f(point(0) + resolution(0) / 2.0, point(1) - resolution(1) / 2.0,
        sampleMean);
      glVertex3f(point(0) - resolution(0) / 2.0, point(1) - resolution(1) / 2.0,
        sampleMean);
      glVertex3f(point(0) - resolution(0) / 2.0, point(1) + resolution(1) / 2.0,
        sampleMean);
      glEnd();
    }
  }
  glPopAttrib();
}

void SegmentationControl::render(GLView& view, Scene& scene) {
  if (mUi->showSegmentationCheckBox->isChecked())
    renderSegmentation();
}

void SegmentationControl::segment() {
  DEMGraph graph(mDEM);
  GraphSegmenter<DEMGraph>::segment(graph, mComponents, graph.getVertices(),
    mK);
  mColors.resize(mComponents.size());
  for (std::vector<Color>::iterator it = mColors.begin(); it != mColors.end();
    ++it)
    getColor(*it);
  mUi->showSegmentationCheckBox->setEnabled(true);
  GLView::getInstance().update();
}

void SegmentationControl::demUpdated(const Grid<double, Cell, 2>& dem) {
  mDEM = dem;
  segment();
}

void SegmentationControl::kChanged(double value) {
  setK(value);
  segment();
}

void SegmentationControl::getColor(Color& color) const {
  static Randomizer<double> randomizer;
  double h = randomizer.sampleUniform(0, 360);
  double s = 1.0;
  double v = 1.0;
  h /= 60.0;
  int i = floor(h);
  double f =  h - i;
  double p = v * (1 - s);
  double q = v * (1 - s * f);
  double t = v * (1 - s * (1 - f));
  switch (i) {
    case 0:
      color.mRedColor = v ;
      color.mGreenColor = t;
      color.mBlueColor = p;
      break;
    case 1:
      color.mRedColor = q;
      color.mGreenColor = v;
      color.mBlueColor = p;
      break;
    case 2:
      color.mRedColor = p;
      color.mGreenColor = v;
      color.mBlueColor = t;
      break;
    case 3:
      color.mRedColor = p;
      color.mGreenColor = q;
      color.mBlueColor = v;
      break;
    case 4:
      color.mRedColor = t;
      color.mGreenColor = p;
      color.mBlueColor = v;
      break;
    default:
      color.mRedColor = v;
      color.mGreenColor = p;
      color.mBlueColor = q;
      break;
  }
}

void SegmentationControl::showSegmentationToggled(bool checked) {
  setShowSegmentation(checked);
}
