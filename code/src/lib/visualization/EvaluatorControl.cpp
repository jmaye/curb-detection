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

#include "visualization/EvaluatorControl.h"

#include "ui_EvaluatorControl.h"

#include "visualization/DEMControl.h"
#include "visualization/PointCloudControl.h"
#include "visualization/BPControl.h"
#include "exceptions/IOException.h"
#include "data-structures/TransGrid.h"
#include "data-structures/Cell.h"
#include "utils/Colors.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

EvaluatorControl::EvaluatorControl(bool showGroundTruth) :
    mUi(new Ui_EvaluatorControl()),
    mDEM(0) {
  mUi->setupUi(this);
  connect(&GLView::getInstance().getScene(), SIGNAL(render(GLView&, Scene&)),
    this, SLOT(render(GLView&, Scene&)));
  connect(&DEMControl::getInstance(),
    SIGNAL(demUpdated(const TransGrid<double, Cell, 2>&)), this,
    SLOT(demUpdated(const TransGrid<double, Cell, 2>&)));
  connect(&PointCloudControl::getInstance(),
    SIGNAL(pointCloudRead(const std::string&)), this,
    SLOT(pointCloudRead(const std::string&)));
  connect(&BPControl::getInstance(),
    SIGNAL(bpUpdated(const TransGrid<double, Cell, 2>&, const DEMGraph&,
    const DEMGraph::VertexContainer&)), this,
    SLOT(bpUpdated(const TransGrid<double, Cell, 2>&, const DEMGraph&,
    const DEMGraph::VertexContainer&)));
  setShowGroundTruth(showGroundTruth);
}

EvaluatorControl::~EvaluatorControl() {
  if (mDEM)
    delete mDEM;
  delete mUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void EvaluatorControl::setShowGroundTruth(bool showGroundTruth) {
  mUi->showGroundTruthCheckBox->setChecked(showGroundTruth);
  GLView::getInstance().update();
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void EvaluatorControl::renderGroundTruth() {
  glPushAttrib(GL_CURRENT_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  for (auto it = mVertices.begin(); it != mVertices.end(); ++it) {
    const Eigen::Matrix<double, 2, 1> point =  mDEM->getCoordinates(it->first);
    const Cell& cell = (*mDEM)[it->first];
    const double sampleMean =
      std::get<0>(cell.getHeightEstimator().getDist().getMode());
    auto color = Colors::genColor(it->second);
    const Grid<double, Cell, 2>::Coordinate ulPoint =
      mDEM->getULCoordinates(it->first);
    const Grid<double, Cell, 2>::Coordinate urPoint =
      mDEM->getURCoordinates(it->first);
    const Grid<double, Cell, 2>::Coordinate lrPoint =
      mDEM->getLRCoordinates(it->first);
    const Grid<double, Cell, 2>::Coordinate llPoint =
      mDEM->getLLCoordinates(it->first);
    glBegin(GL_QUADS);
    glColor3f(color.mRed, color.mGreen, color.mBlue);
    glVertex3f(ulPoint(0), ulPoint(1), sampleMean);
    glVertex3f(urPoint(0), urPoint(1), sampleMean);
    glVertex3f(lrPoint(0), lrPoint(1), sampleMean);
    glVertex3f(llPoint(0), llPoint(1), sampleMean);
    glEnd();
  }
  glPopAttrib();
}

void EvaluatorControl::showGroundTruthToggled(bool checked) {
  setShowGroundTruth(checked);
}

void EvaluatorControl::render(GLView& view, Scene& scene) {
  if (mUi->showGroundTruthCheckBox->isChecked())
    renderGroundTruth();
}

void EvaluatorControl::labelDEM() {
  mVertices.clear();
  std::ifstream gtFile(mGTFilename.c_str());
  try {
    gtFile >> mEvaluator;
  }
  catch (IOException& e) {
    return;
  }
  const Grid<double, Cell, 2>::Index& numCells = mDEM->getNumCells();
  for (size_t i = 0; i < numCells(0); ++i)
    for (size_t j = 0; j < numCells(1); ++j) {
      const Cell& cell =
        (*mDEM)[(Eigen::Matrix<size_t, 2, 1>() << i, j).finished()];
      if (!cell.getHeightEstimator().getDist().getKappa())
        continue;
      const Eigen::Matrix<double, 2, 1> point = 
        mDEM->getCoordinates((Eigen::Matrix<size_t, 2, 1>() << i, j).
        finished());
      mVertices[(Eigen::Matrix<size_t, 2, 1>() << i, j).finished()] =
        mEvaluator.getLabel(point);
    }
  mUi->showGroundTruthCheckBox->setEnabled(true);
  GLView::getInstance().update();
}

void EvaluatorControl::pointCloudRead(const std::string& filename) {
  mGTFilename.clear();
  size_t pos = filename.find(".csv");
  if (pos == 0)
    pos = filename.find(".log");
  if (pos) {
    mGTFilename = filename.substr(0, filename.size() - 4);
    mGTFilename.append(".gt");
    labelDEM();
  }
}

void EvaluatorControl::demUpdated(const TransGrid<double, Cell, 2>& dem) {
  if (mDEM)
    delete mDEM;
  mDEM = new TransGrid<double, Cell, 2>(dem);
  labelDEM();
}

void EvaluatorControl::bpUpdated(const TransGrid<double, Cell, 2>& dem, const
    DEMGraph& graph, const DEMGraph::VertexContainer& vertices) {
  const double vMeasure = mEvaluator.evaluate(dem, graph, vertices);
  mUi->vMeasureSpinBox->setValue(vMeasure);
  mUi->vMeasureSpinBox->setEnabled(true);
}
