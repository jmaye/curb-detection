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

#include "visualization/CurbsControl.h"

#include "visualization/BPControl.h"
#include "data-structures/TransGrid.h"
#include "data-structures/Cell.h"

#include "ui_CurbsControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

CurbsControl::CurbsControl(bool showCurbs) :
    mUi(new Ui_CurbsControl()),
    mDEM(0),
    mGraph(0) {
  mUi->setupUi(this);
  mUi->colorChooser->setPalette(&mPalette);
  connect(&mPalette, SIGNAL(colorChanged(const QString&, const QColor&)),
    this, SLOT(colorChanged(const QString&, const QColor&)));
  connect(&View3d::getInstance().getScene(), SIGNAL(render(View3d&, Scene3d&)),
    this, SLOT(render(View3d&, Scene3d&)));
  connect(&BPControl::getInstance(),
    SIGNAL(bpUpdated(const TransGrid<double, Cell, 2>&, const DEMGraph&,
    const DEMGraph::VertexContainer&)), this,
    SLOT(bpUpdated(const TransGrid<double, Cell, 2>&, const DEMGraph&,
    const DEMGraph::VertexContainer&)));
  setLineColor(Qt::red);
  setLineSize(1.0);
  setShowCurbs(showCurbs);
  setSmoothLines(true);
}

CurbsControl::~CurbsControl() {
  if (mDEM)
    delete mDEM;
  if (mGraph)
    delete mGraph;
  delete mUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void CurbsControl::setLineColor(const QColor& color) {
  mPalette.setColor("Curb", color);
}

void CurbsControl::setLineSize(double lineSize) {
  mUi->lineSizeSpinBox->setValue(lineSize);
  View3d::getInstance().update();
}

void CurbsControl::setShowCurbs(bool showCurbs) {
  mUi->showCurbsCheckBox->setChecked(showCurbs);
  View3d::getInstance().update();
}

void CurbsControl::setSmoothLines(bool smoothLines) {
  mUi->smoothLinesCheckBox->setChecked(smoothLines);
  View3d::getInstance().update();
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

//void CurbsControl::renderCurbs(double size, bool smooth) {
//  glPushAttrib(GL_CURRENT_BIT);
//  if (size > 1.0)
//    glLineWidth(size);
//  else
//    glLineWidth(1.0);
//  if (smooth)
//    glEnable(GL_LINE_SMOOTH);
//  else
//    glDisable(GL_LINE_SMOOTH);
//  glBegin(GL_LINES);
//  View3d::getInstance().setColor(mPalette, "Curb");
//  const Eigen::Matrix<double, 2, 1>& resolution = mDEM->getResolution();
//  for (auto it = mGraph->getEdgeBegin(); it != mGraph->getEdgeEnd(); ++it) {
//    const DEMGraph::EdgeDescriptor e = mGraph->getEdge(it);
//    const DEMGraph::VertexDescriptor& v1 = mGraph->getHeadVertex(e);
//    const DEMGraph::VertexDescriptor& v2 = mGraph->getTailVertex(e);
//    if (mVertices[v1] != mVertices[v2]) {
//      const Eigen::Matrix<double, 2, 1> point1 = mDEM->getCoordinates(v1);
//      const Cell& cell1 = (*mDEM)[v1];
//      const double sampleMean1 =
//        std::get<0>(cell1.getHeightEstimator().getDist().getMode());
//      const Eigen::Matrix<double, 2, 1> point2 = mDEM->getCoordinates(v2);
//      const Cell& cell2 = (*mDEM)[v2];
//      const double sampleMean2 =
//        std::get<0>(cell2.getHeightEstimator().getDist().getMode());
//      Eigen::Matrix<double, 2, 1> point = point1;
//      if (v1(0) > v2(0))
//        point(0) -= resolution(0) / 2.0;
//      else if (v1(0) < v2(0))
//        point(0) += resolution(0) / 2.0;
//      else if (v1(1) > v2(1))
//        point(1) -= resolution(1) / 2.0;
//      else
//        point(1) += resolution(1) / 2.0;
//      glVertex3f(point(0), point(1), sampleMean1);
//      glVertex3f(point(0), point(1), sampleMean2);
//    }
//  }
//  glEnd();
//  glLineWidth(1.0);
//  glDisable(GL_POINT_SMOOTH);
//  glPopAttrib();
//}

void CurbsControl::renderCurbs(double size, bool smooth) {
  glPushAttrib(GL_CURRENT_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  View3d::getInstance().setColor(mPalette, "Curb");
  for (auto it = mGraph->getEdgeBegin(); it != mGraph->getEdgeEnd(); ++it) {
    const DEMGraph::EdgeDescriptor e = mGraph->getEdge(it);
    const DEMGraph::VertexDescriptor& v1 = mGraph->getHeadVertex(e);
    const DEMGraph::VertexDescriptor& v2 = mGraph->getTailVertex(e);
    if (mVertices[v1] != mVertices[v2]) {
      const Cell& cell1 = (*mDEM)[v1];
      const double sampleMean1 =
        std::get<0>(cell1.getHeightEstimator().getDist().getMode());
      const Cell& cell2 = (*mDEM)[v2];
      const double sampleMean2 =
        std::get<0>(cell2.getHeightEstimator().getDist().getMode());
      Eigen::Matrix<double, 2, 1> point1, point2, point3, point4;
      if (v1(0) > v2(0)) {
        point1 = mDEM->getLLCoordinates(v1);
        point2 = mDEM->getLRCoordinates(v1);
        point3 = mDEM->getURCoordinates(v2);
        point4 = mDEM->getULCoordinates(v2);
      }
      else if (v1(0) < v2(0)) {
        point1 = mDEM->getULCoordinates(v1);
        point2 = mDEM->getURCoordinates(v1);
        point3 = mDEM->getLRCoordinates(v2);
        point4 = mDEM->getLLCoordinates(v2);
      }
      else if (v1(1) > v2(1)) {
        point1 = mDEM->getURCoordinates(v1);
        point2 = mDEM->getLRCoordinates(v1);
        point3 = mDEM->getLLCoordinates(v2);
        point4 = mDEM->getULCoordinates(v2);
      }
      else {
        point1 = mDEM->getULCoordinates(v1);
        point2 = mDEM->getLLCoordinates(v1);
        point3 = mDEM->getLRCoordinates(v2);
        point4 = mDEM->getURCoordinates(v2);
      }
      glBegin(GL_QUADS);
      glVertex3f(point1(0), point1(1), sampleMean1);
      glVertex3f(point2(0), point2(1), sampleMean1);
      glVertex3f(point3(0), point3(1), sampleMean2);
      glVertex3f(point4(0), point4(1), sampleMean2);
      glEnd();
    }
  }
  glPopAttrib();
}

void CurbsControl::colorChanged(const QString& role, const QColor& color) {
  View3d::getInstance().update();
}

void CurbsControl::lineSizeChanged(double lineSize) {
  setLineSize(lineSize);
}

void CurbsControl::showCurbsToggled(bool checked) {
  setShowCurbs(checked);
}

void CurbsControl::smoothLinesToggled(bool checked) {
  setSmoothLines(checked);
}

void CurbsControl::render(View3d& view, Scene3d& scene) {
  if (mUi->showCurbsCheckBox->isChecked() && mDEM)
    renderCurbs(mUi->lineSizeSpinBox->value(),
      mUi->smoothLinesCheckBox->isChecked());
}

void CurbsControl::bpUpdated(const TransGrid<double, Cell, 2>& dem, const
    DEMGraph& graph, const DEMGraph::VertexContainer& vertices) {
  if (mDEM)
    delete mDEM;
  mDEM = new TransGrid<double, Cell, 2>(dem);
  if (mGraph)
    delete mGraph;
  mGraph = new DEMGraph(graph);
  mVertices = vertices;
  mUi->showCurbsCheckBox->setEnabled(true);
  View3d::getInstance().update();
}
