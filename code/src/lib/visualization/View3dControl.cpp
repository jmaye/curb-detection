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

#include "visualization/View3dControl.h"

#include <cmath>

#include <QtGui/QFileDialog>
#include <QtCore/QDir>
#include <QtGui/QPixmap>

#include "ui_View3dControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

View3dControl::View3dControl(bool showFog, bool showGround, bool showAxes) :
    mUi(new Ui_View3dControl()) {
  mUi->setupUi(this);
  mUi->colorChooser->setPalette(&mPalette);
  connect(&mPalette, SIGNAL(colorChanged(const QString&, const QColor&)),
    this, SLOT(colorChanged(const QString&, const QColor&)));
  connect(&View3d::getInstance(),
    SIGNAL(fontChanged(const QString&)), this,
    SLOT(fontChanged(const QString&)));
  fontChanged(View3d::getInstance().getFont());
  connect(&View3d::getInstance().getCamera(),
    SIGNAL(positionChanged(const std::vector<double>&)), this,
    SLOT(cameraPositionChanged(const std::vector<double>&)));
  cameraPositionChanged(View3d::getInstance().getCamera().getPosition());
  connect(&View3d::getInstance().getCamera(),
    SIGNAL(viewpointChanged(const std::vector<double>&)), this,
    SLOT(cameraViewpointChanged(const std::vector<double>&)));
  cameraViewpointChanged(View3d::getInstance().getCamera().getViewpoint());
  connect(&View3d::getInstance().getScene(),
    SIGNAL(translationChanged(const std::vector<double>&)), this,
    SLOT(sceneTranslationChanged(const std::vector<double>&)));
  sceneTranslationChanged(View3d::getInstance().getScene().getTranslation());
  connect(&View3d::getInstance().getScene(),
    SIGNAL(rotationChanged(const std::vector<double>&)), this,
    SLOT(sceneRotationChanged(const std::vector<double>&)));
  sceneRotationChanged(View3d::getInstance().getScene().getRotation());
  connect(&View3d::getInstance().getScene(), SIGNAL(scaleChanged(double)),
    this, SLOT(sceneScaleChanged(double)));
  sceneScaleChanged(View3d::getInstance().getScene().getScale());
  connect(&View3d::getInstance().getScene(), SIGNAL(render(View3d&, Scene3d&)),
    this, SLOT(render(View3d&, Scene3d&)));
  connect(&View3d::getInstance(), SIGNAL(updated()), this, SLOT(dumpFrame()));
  connect(&View3d::getInstance(), SIGNAL(resized()), this, SLOT(resized()));
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

View3dControl::~View3dControl() {
  delete mUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void View3dControl::setBackgroundColor(const QColor& color) {
  mPalette.setColor("Background", color);
}

void View3dControl::setFogColor(const QColor& color) {
  mPalette.setColor("Fog", color);
}

void View3dControl::setGroundColor(const QColor& color) {
  mPalette.setColor("Ground", color);
}

void View3dControl::setGroundRadius(double radius) {
  mUi->groundXSpinBox->setValue(radius);
  mUi->groundYSpinBox->setValue(radius);
  View3d::getInstance().update();
}

void View3dControl::setGroundElevation(double elevation) {
  mUi->groundZSpinBox->setValue(elevation);
  View3d::getInstance().update();
}

void View3dControl::setShowFog(bool showFog) {
  mUi->showFogCheckBox->setChecked(showFog);
  View3d::getInstance().update();
}

void View3dControl::setShowGround(bool showGround) {
  mUi->showGroundCheckBox->setChecked(showGround);
  View3d::getInstance().update();
}

void View3dControl::setShowAxes(bool showAxes) {
  mUi->showAxesCheckBox->setChecked(showAxes);
  View3d::getInstance().update();
}

void View3dControl::setDumpDirectory(const QString& dirname) {
  QDir dir(dirname);
  mUi->dumpDirEdit->setText(dir.absolutePath());
}

void View3dControl::setDumpFrameSize(size_t width, size_t height) {
  mUi->frameWidthSpinBox->setValue(width);
  mUi->frameHeightSpinBox->setValue(height);
}

void View3dControl::setDumpFormat(const QString& format) {
  mUi->dumpFormatEdit->setText(format);
}

void View3dControl::setDumpAll(bool dumpAll) {
  if (dumpAll)
    connect(&View3d::getInstance(), SIGNAL(updated()), this, SLOT(dumpFrame()));
  else
    View3d::getInstance().disconnect(SIGNAL(updated()));
  mUi->dumpAllCheckBox->setChecked(dumpAll);
}

void View3dControl::setRotateFrames(bool rotateFrames) {
  mUi->rotateFramesCheckBox->setChecked(rotateFrames);
}

void View3dControl::setFrameRotation(double yaw) {
  mUi->frameRotationSpinBox->setValue(yaw * 180.0 / M_PI);
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void View3dControl::dumpFrame() {
  static bool dumping = false;
  if (dumping)
    return;
  dumping = true;
  QApplication::processEvents();
  dumpFrame(mUi->dumpFormatEdit->text(), mUi->frameSpinBox->value(),
    mUi->frameWidthSpinBox->value(), mUi->frameHeightSpinBox->value());
  if (mUi->dumpAllCheckBox->isChecked() &&
      mUi->rotateFramesCheckBox->isChecked())
    View3d::getInstance().getScene().setRotation(
      (mUi->sceneYawSpinBox->value() + mUi->frameRotationSpinBox->value())
        * M_PI / 180.0,
      mUi->scenePitchSpinBox->value() * M_PI / 180.0,
      mUi->sceneRollSpinBox->value() * M_PI / 180.0);
  dumping = false;
}

void View3dControl::renderBackground() {
  glPushAttrib(GL_CURRENT_BIT);
  QColor backgroundColor = mPalette.getColor("Background");
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
    backgroundColor.blueF(), 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPopAttrib();
}

void View3dControl::renderFog(double start, double end, double density) {
  glPushAttrib(GL_CURRENT_BIT);
  QColor color = mPalette.getColor("Fog");
  float colorfv[] = {(float)color.redF(), (float)color.greenF(),
    (float)color.blueF(), 1.0};
  double scale = View3d::getInstance().getScene().getScale();
  double distance = View3d::getInstance().getCamera().getViewpointDistance();
  glFogi(GL_FOG_MODE, GL_LINEAR);
  glFogfv(GL_FOG_COLOR, colorfv);
  glFogf(GL_FOG_DENSITY, density);
  glHint(GL_FOG_HINT, GL_DONT_CARE);
  glFogf(GL_FOG_START, distance + start * scale);
  glFogf(GL_FOG_END, distance + end * scale);
  glPopAttrib();
}

void View3dControl::renderGround(double radius, double elevation, double
    angleStep, double rangeStep) {
  glPushAttrib(GL_CURRENT_BIT);
  glBegin(GL_LINES);
  View3d::getInstance().setColor(mPalette, "Ground");
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

void View3dControl::renderAxes(double length) {
  glPushAttrib(GL_CURRENT_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_LINES);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(length, 0.0, 0.0);
  glEnd();
  View3d::getInstance().render(length, 0.0, 0.0, "X", 0.0, 0.2 * length, true,
    true, true);
  glBegin(GL_LINES);
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, length, 0.0);
  glEnd();
  View3d::getInstance().render(0.0, length, 0.0, "Y", 0.0, 0.2 * length, true,
    true, true);
  glBegin(GL_LINES);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, length);
  glEnd();
  View3d::getInstance().render(0.0, 0.0, length, "Z", 0.0, 0.2 * length, true,
    true, true);
  glPopAttrib();
}

void View3dControl::dumpFrame(const QString& format, int frame, size_t width,
    size_t height) {
  QDir dir(mUi->dumpDirEdit->text());
  if (dir.isReadable()) {
    QString filename;
    QPixmap pixmap;
    filename.sprintf(format.toAscii().constData(), frame);
    pixmap = View3d::getInstance().renderPixmap(width, height);
    QFileInfo fileInfo(dir, filename);
    if (pixmap.save(fileInfo.absoluteFilePath()))
      mUi->frameSpinBox->setValue(frame + 1);
  }
}

void View3dControl::fontBrowseClicked() {
  QString filename = QFileDialog::getOpenFileName(this,
    "Open Font File", mUi->fontEdit->text(),
    "TrueType font files (*.ttf)");
  if (!filename.isNull())
    View3d::getInstance().setFont(filename);
}

void View3dControl::groundRadiusChanged(double radius) {
  setGroundRadius(radius);
}

void View3dControl::groundElevationChanged(double elevation) {
  setGroundElevation(elevation);
}

void View3dControl::cameraPositionChanged() {
  View3d::getInstance().getCamera().setPosition(
    mUi->cameraXSpinBox->value(),
    mUi->cameraYSpinBox->value(),
    mUi->cameraZSpinBox->value());
}

void View3dControl::cameraViewpointChanged() {
  View3d::getInstance().getCamera().setViewpoint(
    mUi->cameraViewXSpinBox->value(),
    mUi->cameraViewYSpinBox->value(),
    mUi->cameraViewZSpinBox->value());
}

void View3dControl::sceneTranslationChanged() {
  View3d::getInstance().getScene().setTranslation(
    mUi->sceneXSpinBox->value(),
    mUi->sceneYSpinBox->value(),
    mUi->sceneZSpinBox->value());
}

void View3dControl::sceneRotationChanged() {
  View3d::getInstance().getScene().setRotation(
    mUi->sceneYawSpinBox->value() * M_PI / 180.0,
    mUi->scenePitchSpinBox->value() * M_PI / 180.0,
    mUi->sceneRollSpinBox->value() * M_PI / 180.0);
}

void View3dControl::sceneScaleChanged() {
  View3d::getInstance().getScene().setScale(mUi->sceneScaleSpinBox->value());
}

void View3dControl::showFogToggled(bool checked) {
  setShowFog(checked);
}

void View3dControl::showGroundToggled(bool checked) {
  setShowGround(checked);
}

void View3dControl::showAxesToggled(bool checked) {
  setShowAxes(checked);
}

void View3dControl::dumpDirBrowseClicked() {
  QString dirname = QFileDialog::getExistingDirectory(this,
    "Select Dump Directory", mUi->dumpDirEdit->text());
  if (!dirname.isNull())
    mUi->dumpDirEdit->setText(dirname);
}

void View3dControl::dumpClicked() {
  dumpFrame();
}

void View3dControl::dumpAllToggled(bool checked) {
  setDumpAll(checked);
}

void View3dControl::colorChanged(const QString& role, const QColor& color) {
  View3d::getInstance().update();
}

void View3dControl::fontChanged(const QString& filename) {
  mUi->fontEdit->blockSignals(true);
  mUi->fontEdit->setText(filename);
  mUi->fontEdit->blockSignals(false);
}

void View3dControl::cameraPositionChanged(const std::vector<double>& position) {
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

void View3dControl::cameraViewpointChanged(const std::vector<double>&
    viewpoint) {
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

void View3dControl::sceneTranslationChanged(const std::vector<double>&
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

void View3dControl::sceneRotationChanged(const std::vector<double>& rotation) {
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

void View3dControl::sceneScaleChanged(double scale) {
  mUi->sceneScaleSpinBox->blockSignals(true);
  mUi->sceneScaleSpinBox->setValue(scale);
  mUi->sceneScaleSpinBox->blockSignals(false);
}

void View3dControl::render(View3d& view, Scene3d& scene) {
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

void View3dControl::resized() {
  setDumpFrameSize(View3d::getInstance().rect().width(),
    View3d::getInstance().rect().height());
}
