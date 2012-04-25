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

#include "visualization/ViewControl.h"

#include "ui_ViewControl.h"

#include <QtGui/QFileDialog>
#include <QtCore/QDir>
#include <QtGui/QPixmap>

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ViewControl::ViewControl(bool showFog, bool showGround, bool showAxes) :
  mUi(new Ui_ViewControl()) {
  mUi->setupUi(this);
  mUi->colorChooser->setPalette(&mPalette);
  connect(&mPalette, SIGNAL(colorChanged(const QString&, const QColor&)),
    this, SLOT(colorChanged(const QString&, const QColor&)));
  connect(&GLView::getInstance(),
    SIGNAL(fontChanged(const QString&)), this,
    SLOT(fontChanged(const QString&)));
  fontChanged(GLView::getInstance().getFont());
  connect(&GLView::getInstance().getCamera(),
    SIGNAL(positionChanged(const std::vector<double>&)), this,
    SLOT(cameraPositionChanged(const std::vector<double>&)));
  cameraPositionChanged(GLView::getInstance().getCamera().getPosition());
  connect(&GLView::getInstance().getCamera(),
    SIGNAL(viewpointChanged(const std::vector<double>&)), this,
    SLOT(cameraViewpointChanged(const std::vector<double>&)));
  cameraViewpointChanged(GLView::getInstance().getCamera().getViewpoint());
  connect(&GLView::getInstance().getScene(),
    SIGNAL(translationChanged(const std::vector<double>&)), this,
    SLOT(sceneTranslationChanged(const std::vector<double>&)));
  sceneTranslationChanged(GLView::getInstance().getScene().getTranslation());
  connect(&GLView::getInstance().getScene(),
    SIGNAL(rotationChanged(const std::vector<double>&)), this,
    SLOT(sceneRotationChanged(const std::vector<double>&)));
  sceneRotationChanged(GLView::getInstance().getScene().getRotation());
  connect(&GLView::getInstance().getScene(), SIGNAL(scaleChanged(double)),
    this, SLOT(sceneScaleChanged(double)));
  sceneScaleChanged(GLView::getInstance().getScene().getScale());
  connect(&GLView::getInstance().getScene(), SIGNAL(render(GLView&, Scene&)),
    this, SLOT(render(GLView&, Scene&)));
  connect(&GLView::getInstance(), SIGNAL(updated()), this, SLOT(dumpFrame()));
  setBackgroundColor(Qt::white);
  setFogColor(Qt::white);
  setGroundColor(Qt::lightGray);
  setGroundRadius(30.0);
  setShowFog(showFog);
  setShowGround(showGround);
  setShowAxes(showAxes);
  setDumpDirectory(QDir::current().path());
  setDumpFrameSize(1280, 720);
  setDumpAll(false);
  setRotateFrames(false);
  setFrameRotation(1.0 * M_PI / 180.0);
}

ViewControl::~ViewControl() {
  delete mUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void ViewControl::setBackgroundColor(const QColor& color) {
  mPalette.setColor("Background", color);
}

void ViewControl::setFogColor(const QColor& color) {
  mPalette.setColor("Fog", color);
}

void ViewControl::setGroundColor(const QColor& color) {
  mPalette.setColor("Ground", color);
}

void ViewControl::setGroundRadius(double radius) {
  mUi->groundXSpinBox->setValue(radius);
  mUi->groundYSpinBox->setValue(radius);
  GLView::getInstance().update();
}

void ViewControl::setGroundElevation(double elevation) {
  mUi->groundZSpinBox->setValue(elevation);
  GLView::getInstance().update();
}

void ViewControl::setShowFog(bool showFog) {
  mUi->showFogCheckBox->setChecked(showFog);
  GLView::getInstance().update();
}

void ViewControl::setShowGround(bool showGround) {
  mUi->showGroundCheckBox->setChecked(showGround);
  GLView::getInstance().update();
}

void ViewControl::setShowAxes(bool showAxes) {
  mUi->showAxesCheckBox->setChecked(showAxes);
  GLView::getInstance().update();
}

void ViewControl::setDumpDirectory(const QString& dirname) {
  QDir dir(dirname);
  mUi->dumpDirEdit->setText(dir.absolutePath());
}

void ViewControl::setDumpFrameSize(size_t width, size_t height) {
  mUi->frameWidthSpinBox->setValue(width);
  mUi->frameHeightSpinBox->setValue(height);
}

void ViewControl::setDumpFormat(const QString& format) {
  mUi->dumpFormatEdit->setText(format);
}

void ViewControl::setDumpAll(bool dumpAll) {
  if (dumpAll)
    connect(&GLView::getInstance(), SIGNAL(updated()), this, SLOT(dumpFrame()));
  else
    GLView::getInstance().disconnect(SIGNAL(updated()));
  mUi->dumpAllCheckBox->setChecked(dumpAll);
}


void ViewControl::setRotateFrames(bool rotateFrames) {
  mUi->rotateFramesCheckBox->setChecked(rotateFrames);
}

void ViewControl::setFrameRotation(double yaw) {
  mUi->frameRotationSpinBox->setValue(yaw * 180.0 / M_PI);
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void ViewControl::dumpFrame() {
  static bool dumping = false;
  if (dumping)
    return;
  dumping = true;
  QApplication::processEvents();
  dumpFrame(mUi->dumpFormatEdit->text(), mUi->frameSpinBox->value(),
    mUi->frameWidthSpinBox->value(), mUi->frameHeightSpinBox->value());
  if (mUi->dumpAllCheckBox->isChecked() &&
      mUi->rotateFramesCheckBox->isChecked())
    GLView::getInstance().getScene().setRotation(
      (mUi->sceneYawSpinBox->value() + mUi->frameRotationSpinBox->value())
        * M_PI / 180.0,
      mUi->scenePitchSpinBox->value() * M_PI / 180.0,
      mUi->sceneRollSpinBox->value() * M_PI / 180.0);
  dumping = false;
}

void ViewControl::renderBackground() {
  glPushAttrib(GL_CURRENT_BIT);
  QColor backgroundColor = mPalette.getColor("Background");
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
    backgroundColor.blueF(), 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPopAttrib();
}

void ViewControl::renderFog(double start, double end, double density) {
  glPushAttrib(GL_CURRENT_BIT);
  QColor color = mPalette.getColor("Fog");
  float colorfv[] = {color.redF(), color.greenF(), color.blueF(), 1.0};
  double scale = GLView::getInstance().getScene().getScale();
  double distance = GLView::getInstance().getCamera().getViewpointDistance();
  glFogi(GL_FOG_MODE, GL_LINEAR);
  glFogfv(GL_FOG_COLOR, colorfv);
  glFogf(GL_FOG_DENSITY, density);
  glHint(GL_FOG_HINT, GL_DONT_CARE);
  glFogf(GL_FOG_START, distance + start * scale);
  glFogf(GL_FOG_END, distance + end * scale);
  glPopAttrib();
}

void ViewControl::renderGround(double radius, double elevation, double
  angleStep, double rangeStep) {
  glPushAttrib(GL_CURRENT_BIT);
  glBegin(GL_LINES);
  GLView::getInstance().setColor(mPalette, "Ground");
  for (double angle = -M_PI; angle < M_PI; angle += angleStep) {
    glVertex3f(rangeStep * sin(angle), rangeStep * cos(angle), elevation);
    glVertex3f(radius * sin(angle), radius * cos(angle), elevation);
  }
  glEnd();
  for (double range = rangeStep; ; range += rangeStep) {
    if (range > radius)
      range = radius;
    glBegin(GL_LINE_STRIP);
    for (double angle = -M_PI; angle <= M_PI; angle += angleStep)
      for (double theta = angle; theta <= angle + angleStep;
        theta += angleStep / range)
        glVertex3f(range * sin(theta), range * cos(theta), elevation);
    glEnd();
    if (range == radius)
      break;
  }
  glPopAttrib();
}

void ViewControl::renderAxes(double length) {
  glPushAttrib(GL_CURRENT_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_LINES);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(length, 0.0, 0.0);
  glEnd();
  GLView::getInstance().render(length, 0.0, 0.0, "X", 0.2 * length, true, true,
    true);
  glBegin(GL_LINES);
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, length, 0.0);
  glEnd();
  GLView::getInstance().render(0.0, length, 0.0, "Y", 0.2 * length, true, true,
    true);
  glBegin(GL_LINES);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, length);
  glEnd();
  GLView::getInstance().render(0, 0, length, "Z", 0.2 * length, true, true,
    true);
  glPopAttrib();
}

void ViewControl::dumpFrame(const QString& format, int frame, size_t width,
  size_t height) {
  QDir dir(mUi->dumpDirEdit->text());
  if (dir.isReadable()) {
    QString filename;
    QPixmap pixmap;
    filename.sprintf(format.toAscii().constData(), frame);
    pixmap = GLView::getInstance().renderPixmap(width, height, true);
    QFileInfo fileInfo(dir, filename);
    if (pixmap.save(fileInfo.absoluteFilePath()))
      mUi->frameSpinBox->setValue(frame + 1);
  }
}

void ViewControl::fontBrowseClicked() {
  QString filename = QFileDialog::getOpenFileName(this,
    "Open Font File", mUi->fontEdit->text(),
    "TrueType font files (*.ttf)");
  if (!filename.isNull())
    GLView::getInstance().setFont(filename);
}

void ViewControl::groundRadiusChanged(double radius) {
  setGroundRadius(radius);
}

void ViewControl::groundElevationChanged(double elevation) {
  setGroundElevation(elevation);
}

void ViewControl::cameraPositionChanged() {
  GLView::getInstance().getCamera().setPosition(
    mUi->cameraXSpinBox->value(),
    mUi->cameraYSpinBox->value(),
    mUi->cameraZSpinBox->value());
}

void ViewControl::cameraViewpointChanged() {
  GLView::getInstance().getCamera().setViewpoint(
    mUi->cameraViewXSpinBox->value(),
    mUi->cameraViewYSpinBox->value(),
    mUi->cameraViewZSpinBox->value());
}

void ViewControl::sceneTranslationChanged() {
  GLView::getInstance().getScene().setTranslation(
    mUi->sceneXSpinBox->value(),
    mUi->sceneYSpinBox->value(),
    mUi->sceneZSpinBox->value());
}

void ViewControl::sceneRotationChanged() {
  GLView::getInstance().getScene().setRotation(
    mUi->sceneYawSpinBox->value() * M_PI / 180.0,
    mUi->scenePitchSpinBox->value() * M_PI / 180.0,
    mUi->sceneRollSpinBox->value() * M_PI / 180.0);
}

void ViewControl::sceneScaleChanged() {
  GLView::getInstance().getScene().setScale(mUi->sceneScaleSpinBox->value());
}

void ViewControl::showFogToggled(bool checked) {
  setShowFog(checked);
}

void ViewControl::showGroundToggled(bool checked) {
  setShowGround(checked);
}

void ViewControl::showAxesToggled(bool checked) {
  setShowAxes(checked);
}

void ViewControl::dumpDirBrowseClicked() {
  QString dirname = QFileDialog::getExistingDirectory(this,
    "Select Dump Directory", mUi->dumpDirEdit->text());
  if (!dirname.isNull())
    mUi->dumpDirEdit->setText(dirname);
}

void ViewControl::dumpClicked() {
  dumpFrame();
}

void ViewControl::dumpAllToggled(bool checked) {
  setDumpAll(checked);
}

void ViewControl::colorChanged(const QString& role, const QColor& color) {
  GLView::getInstance().update();
}

void ViewControl::fontChanged(const QString& filename) {
  mUi->fontEdit->blockSignals(true);
  mUi->fontEdit->setText(filename);
  mUi->fontEdit->blockSignals(false);
}

void ViewControl::cameraPositionChanged(const std::vector<double>& position) {
  mUi->cameraXSpinBox->blockSignals(true);
  mUi->cameraYSpinBox->blockSignals(true);
  mUi->cameraZSpinBox->blockSignals(true);
  mUi->cameraXSpinBox->setValue(position[0]);
  mUi->cameraYSpinBox->setValue(position[1]);
  mUi->cameraZSpinBox->setValue(position[2]);
  mUi->cameraXSpinBox->blockSignals(false);
  mUi->cameraYSpinBox->blockSignals(false);
  mUi->cameraZSpinBox->blockSignals(false);
}

void ViewControl::cameraViewpointChanged(const std::vector<double>& viewpoint) {
  mUi->cameraViewXSpinBox->blockSignals(true);
  mUi->cameraViewYSpinBox->blockSignals(true);
  mUi->cameraViewZSpinBox->blockSignals(true);
  mUi->cameraViewXSpinBox->setValue(viewpoint[0]);
  mUi->cameraViewYSpinBox->setValue(viewpoint[1]);
  mUi->cameraViewZSpinBox->setValue(viewpoint[2]);
  mUi->cameraViewXSpinBox->blockSignals(false);
  mUi->cameraViewYSpinBox->blockSignals(false);
  mUi->cameraViewZSpinBox->blockSignals(false);
}

void ViewControl::sceneTranslationChanged(const std::vector<double>&
  translation) {
  mUi->sceneXSpinBox->blockSignals(true);
  mUi->sceneYSpinBox->blockSignals(true);
  mUi->sceneZSpinBox->blockSignals(true);
  mUi->sceneXSpinBox->setValue(translation[0]);
  mUi->sceneYSpinBox->setValue(translation[1]);
  mUi->sceneZSpinBox->setValue(translation[2]);
  mUi->sceneXSpinBox->blockSignals(false);
  mUi->sceneYSpinBox->blockSignals(false);
  mUi->sceneZSpinBox->blockSignals(false);
}

void ViewControl::sceneRotationChanged(const std::vector<double>& rotation) {
  mUi->sceneYawSpinBox->blockSignals(true);
  mUi->scenePitchSpinBox->blockSignals(true);
  mUi->sceneRollSpinBox->blockSignals(true);
  mUi->sceneYawSpinBox->setValue(rotation[0] * 180.0 / M_PI);
  mUi->scenePitchSpinBox->setValue(rotation[1] * 180.0 / M_PI);
  mUi->sceneRollSpinBox->setValue(rotation[2] * 180.0 / M_PI);
  mUi->sceneYawSpinBox->blockSignals(false);
  mUi->scenePitchSpinBox->blockSignals(false);
  mUi->sceneRollSpinBox->blockSignals(false);
}

void ViewControl::sceneScaleChanged(double scale) {
  mUi->sceneScaleSpinBox->blockSignals(true);
  mUi->sceneScaleSpinBox->setValue(scale);
  mUi->sceneScaleSpinBox->blockSignals(false);
}

void ViewControl::render(GLView& view, Scene& scene) {
  double radius = mUi->groundXSpinBox->value();
  renderBackground();
  if (mUi->showFogCheckBox->isChecked()) {
    glEnable(GL_FOG);
    renderFog(radius, 2.0 * radius, 1.0);
  }
  else
    glDisable(GL_FOG);
  if (mUi->showGroundCheckBox->isChecked())
    renderGround(radius, mUi->groundZSpinBox->value(), 30.0 * M_PI / 180.0,
      5.0);
  if (mUi->showAxesCheckBox->isChecked())
    renderAxes(2.5);
}
