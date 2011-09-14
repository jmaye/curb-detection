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

#include "visualization/MLControl.h"

#include "visualization/SegmentationControl.h"
#include "statistics/Randomizer.h"
#include "helpers/InitML.h"

#include "ui_MLControl.h"

#include <limits>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

MLControl::MLControl(bool showML) :
  mUi(new Ui_MLControl()),
  mDEM(Grid<double, Cell, 2>::Coordinate(0.0, 0.0),
    Grid<double, Cell, 2>::Coordinate(4.0, 4.0),
    Grid<double, Cell, 2>::Coordinate(0.1, 0.1)) {
  mUi->setupUi(this);
  connect(&GLView::getInstance().getScene(), SIGNAL(render(GLView&, Scene&)),
    this, SLOT(render(GLView&, Scene&)));
  connect(&SegmentationControl::getInstance(),
    SIGNAL(segmentUpdated(const Grid<double, Cell, 2>&, const DEMGraph&, const
    GraphSegmenter<DEMGraph>::Components&)), this,
    SLOT(segmentUpdated(const Grid<double, Cell, 2>&, const DEMGraph&, const
    GraphSegmenter<DEMGraph>::Components&)));
  mMaxIter = mUi->maxIterSpinBox->value();
  mTol =  mUi->tolSpinBox->value();
  setShowML(showML);
}

MLControl::~MLControl() {
  delete mUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void MLControl::setMaxIter(size_t maxIter) {
  mMaxIter = maxIter;
  mUi->maxIterSpinBox->setValue(maxIter);
}

void MLControl::setTolerance(double tol) {
  mTol = tol;
  mUi->tolSpinBox->setValue(tol);
}

void MLControl::setShowML(bool showML) {
  mUi->showMLCheckBox->setChecked(showML);
  GLView::getInstance().update();
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void MLControl::renderML() {
  const Eigen::Matrix<double, 2, 1>& resolution = mDEM.getResolution();
  glPushAttrib(GL_CURRENT_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  for (DEMGraph::ConstVertexIterator it = mVertices.begin(); it !=
    mVertices.end(); ++it) {
    const Eigen::Matrix<double, 2, 1> point =  mDEM.getCoordinates(it->first);
    const Cell& cell = mDEM[it->first];
    const double sampleMean = cell.getHeightEstimator().getMean();
    glBegin(GL_POLYGON);
    glColor3f(mColors[it->second].mRedColor, mColors[it->second].mGreenColor,
      mColors[it->second].mBlueColor);
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
  glPopAttrib();
}

void MLControl::render(GLView& view, Scene& scene) {
  if (mUi->showMLCheckBox->isChecked())
    renderML();
}

void MLControl::maxIterChanged(int maxIter) {
  setMaxIter(maxIter);
  runML();
}

void MLControl::tolChanged(double tol) {
  setTolerance(tol);
  runML();
}

void MLControl::segmentUpdated(const Grid<double, Cell, 2>& dem, const DEMGraph&
  graph, const GraphSegmenter<DEMGraph>::Components& components) {
  mDEM = dem;
  if (Helpers::initML(dem, graph, components, mPoints, mPointsMapping, mC, mV,
    mW)) {
    runML();
    mColors.clear();
    mColors.reserve(components.size());
    for (size_t i = 0; i < components.size(); ++i) {
      Color color;
      getColor(color);
      mColors.push_back(color);
    }
  }
}

void MLControl::runML() {
  if (mPoints.size()) {
    EstimatorML<MixtureDistribution<LinearRegression<3>, Eigen::Dynamic>, 3,
      Eigen::Dynamic> estMixtPlane(mC, mV, mW, mMaxIter, mTol);
    const size_t numIter = estMixtPlane.addPoints(mPoints.begin(),
      mPoints.end());
    mUi->iterSpinBox->setValue(numIter);
    const Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>&
      responsibilities = estMixtPlane.getResponsibilities();
    mVertices.clear();
    for (size_t i = 0; i < (size_t)responsibilities.rows(); ++i) {
      double max = -std::numeric_limits<double>::infinity();
      size_t argmax = 0;
      for (size_t j = 0; j < (size_t)responsibilities.cols(); ++j)
        if (responsibilities(i, j) > max) {
          max = responsibilities(i, j);
          argmax = j;
        }
      mVertices[mPointsMapping[i]] = argmax;
    }
    mUi->showMLCheckBox->setEnabled(true);
    GLView::getInstance().update();
  }
}

void MLControl::getColor(Color& color) const {
  const static Randomizer<double> randomizer;
  double h = randomizer.sampleUniform(0, 360);
  const double s = 1.0;
  const double v = 1.0;
  h /= 60.0;
  const int i = floor(h);
  const double f =  h - i;
  const double p = v * (1 - s);
  const double q = v * (1 - s * f);
  const double t = v * (1 - s * (1 - f));
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

void MLControl::showMLToggled(bool checked) {
  setShowML(checked);
}
