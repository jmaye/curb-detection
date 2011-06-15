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

#include "visualization/GLView.h"

#include <QtCore/QFileInfo>
#include <QtGui/QWheelEvent>
#include <QtGui/QMouseEvent>

#include <FTGL/ftgl.h>

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

GLView::GLView(QWidget* pParent) :
  QGLWidget(pParent),
  mpFont(0),
  mMouseVector(2, 0),
  mViewportVector(4, 0),
  mProjectionVector(16, 0.0),
  mModelviewVector(16, 0.0) {
  setFont("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf");

  connect(&mCamera, SIGNAL(positionChanged(const std::vector<double>&)), this,
    SLOT(cameraPositionChanged(const std::vector<double>&)));
  connect(&mCamera, SIGNAL(viewpointChanged(const std::vector<double>&)), this,
    SLOT(cameraViewpointChanged(const std::vector<double>&)));
  connect(&mCamera, SIGNAL(rangeChanged(const std::vector<double>&)), this,
    SLOT(cameraRangeChanged(const std::vector<double>&)));

  connect(&mScene, SIGNAL(translationChanged(const std::vector<double>&)), this,
    SLOT(sceneTranslationChanged(const std::vector<double>&)));
  connect(&mScene, SIGNAL(rotationChanged(const std::vector<double>&)), this,
    SLOT(sceneRotationChanged(const std::vector<double>&)));
  connect(&mScene, SIGNAL(scaleChanged(double)), this,
    SLOT(sceneScaleChanged(double)));
}

GLView::~GLView() {
  if (mpFont)
    delete mpFont;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

Camera& GLView::getCamera() {
  return mCamera;
}

const Camera& GLView::getCamera() const {
  return mCamera;
}

Scene& GLView::getScene() {
  return mScene;
}

const Scene& GLView::getScene() const {
  return mScene;
}


void GLView::setColor(const QColor& color) {
  glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
}

void GLView::setColor(const Palette& palette, const QString& role) {
  setColor(palette.getColor(role));
}

void GLView::setFont(const QString& filename) {
  if (mFontFilename != filename) {
    if (mpFont) {
      delete mpFont;
      mpFont = 0;
    }
    this->mFontFilename = filename;

    emit fontChanged(mFontFilename);
    update();
  }
}

const QString& GLView::getFont() const {
  return mFontFilename;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

std::vector<double> GLView::unproject(const QPoint& point, double f64Distance) {
  std::vector<double> resultVector(3, 0.0);

  double f64Near = mCamera.getRange()[0];
  double f64Far = mCamera.getRange()[1];
  double f64Z = (1.0 / f64Near - 1.0 / f64Distance) / (1.0 / f64Near - 1.0 /
    f64Far);

  gluUnProject(point.x(), -point.y(), f64Z,
    &mModelviewVector[0], &mProjectionVector[0], &mViewportVector[0],
    &resultVector[0], &resultVector[1], &resultVector[2]);

  return resultVector;
}

void GLView::render(double f64X, double f64Y, double f64Z, const QString& text,
  double f64Scale, bool bFaceX, bool bFaceY, bool bFaceZ) {
  if (!mpFont) {
    QFileInfo fileInfo(mFontFilename);
    if (fileInfo.isFile() && fileInfo.isReadable()) {
      mpFont = new FTPolygonFont(mFontFilename.toAscii().constData());
      mpFont->UseDisplayList(false);
      mpFont->FaceSize(100);
    }
  }

  if (mpFont) {
    glPushMatrix();
    glTranslatef(f64X, f64Y, f64Z);
    if (bFaceZ)
      glRotatef(-mScene.getRotation()[0] * 180.0 / M_PI, 0, 0, 1);
    if (bFaceY)
      glRotatef(-mScene.getRotation()[1] * 180.0 / M_PI, 0, 1, 0);
    if (bFaceX)
      glRotatef(-mScene.getRotation()[2] * 180.0 / M_PI, 1, 0, 0);
    glRotatef(90.0, 1, 0, 0);
    glRotatef(-90.0, 0, 1, 0);
    glScalef(mScene.getScale() * 1e-2, mScene.getScale() * 1e-2,
      mScene.getScale() * 1e-2);
    mpFont->Render(text.toAscii().constData());
    glPopMatrix();
  }
}

void GLView::mousePressEvent(QMouseEvent* event) {
  mMouseVector[0] = event->globalX();
  mMouseVector[1] = event->globalY();
}

void GLView::mouseMoveEvent(QMouseEvent* event) {
  int i32DeltaX = event->globalX() - mMouseVector[0];
  int i32DeltaY = event->globalY() - mMouseVector[1];

  if (event->buttons() == Qt::LeftButton) {
    mScene.setRotation(
      mScene.getRotation()[0] - M_PI / width() * i32DeltaX,
      mScene.getRotation()[1] + M_PI / height() * i32DeltaY,
      mScene.getRotation()[2]);
  }
  else if (event->buttons() == Qt::RightButton) {
    QPoint mouseLocal = mapFromGlobal(QPoint(mMouseVector[0], mMouseVector[1]));
    QPoint eventLocal = mapFromGlobal(QPoint(event->globalPos()));

    double f64Distance = mCamera.getViewpointDistance();
    std::vector<double> mouseUnprojectedVector = unproject(mouseLocal,
      f64Distance);
    std::vector<double> eventUnprojectedVector = unproject(eventLocal,
      f64Distance);

    mScene.setTranslation(
      mScene.getTranslation()[0] + (eventUnprojectedVector[0] -
        mouseUnprojectedVector[0]),
      mScene.getTranslation()[1] + (eventUnprojectedVector[1] -
        mouseUnprojectedVector[1]),
      mScene.getTranslation()[2] + (eventUnprojectedVector[2] -
        mouseUnprojectedVector[2]));
  }

  mMouseVector[0] = event->globalX();
  mMouseVector[1] = event->globalY();
}

void GLView::wheelEvent(QWheelEvent* event) {
  double f64DeltaScale = 1e-2;
  mScene.setScale(mScene.getScale() * (1.0 + f64DeltaScale * event->delta() /
    8.0));
}

void GLView::initializeGL() {
  glEnable(GL_DEPTH_TEST);

  glEnable (GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GLView::resizeGL(int i32Width, int i32Height) {
  glViewport(0, 0, i32Width, i32Height);
  mCamera.setup(*this, i32Width, i32Height);
}

void GLView::paintGL() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  mCamera.setup(*this, width(), height());
  mScene.setup(*this);

  glGetIntegerv(GL_VIEWPORT, &mViewportVector[0]);
  glGetDoublev(GL_PROJECTION_MATRIX, &mProjectionVector[0]);
  glGetDoublev(GL_MODELVIEW_MATRIX, &mModelviewVector[0]);

  mScene.render(*this);
}

void GLView::paintEvent(QPaintEvent* event) {
  QGLWidget::paintEvent(event);
  emit updated();
}

void GLView::cameraPositionChanged(const std::vector<double>& positionVector) {
  update();
}

void GLView::cameraViewpointChanged(const std::vector<double>&
  viewpointVector) {
  update();
}

void GLView::cameraRangeChanged(const std::vector<double>& rangeVector) {
  update();
}

void GLView::sceneTranslationChanged(const std::vector<double>&
  translationVector) {
  update();
}

void GLView::sceneRotationChanged(const std::vector<double>& rotationVector) {
  update();
}

void GLView::sceneScaleChanged(double f64Scale) {
  update();
}
