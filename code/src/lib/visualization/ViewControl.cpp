#include "visualization/ViewControl.h"

#include "ui_ViewControl.h"

#include <QtGui/QFileDialog>
#include <QtCore/QDir>
#include <QtGui/QPixmap>

#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ViewControl::ViewControl(bool bShowFog, bool bShowGround, bool bShowAxes) :
  mpUi(new Ui_ViewControl()) {
  mpUi->setupUi(this);

  mpUi->colorChooser->setPalette(&mPalette);

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

  setShowFog(bShowFog);
  setShowGround(bShowGround);
  setShowAxes(bShowAxes);

  setDumpDirectory(QDir::current().path());
  setDumpFrameSize(1280, 720);
  setDumpAll(false);
  setRotateFrames(false);
  setFrameRotation(1.0 * M_PI / 180.0);
}

ViewControl::~ViewControl() {
  delete mpUi;
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

void ViewControl::setGroundRadius(double f64Radius) {
  mpUi->groundXSpinBox->setValue(f64Radius);
  mpUi->groundYSpinBox->setValue(f64Radius);
  GLView::getInstance().update();
}

void ViewControl::setGroundElevation(double f64Elevation) {
  mpUi->groundZSpinBox->setValue(f64Elevation);
  GLView::getInstance().update();
}

void ViewControl::setShowFog(bool bShowFog) {
  mpUi->showFogCheckBox->setChecked(bShowFog);
  GLView::getInstance().update();
}

void ViewControl::setShowGround(bool bShowGround) {
  mpUi->showGroundCheckBox->setChecked(bShowGround);
  GLView::getInstance().update();
}

void ViewControl::setShowAxes(bool bShowAxes) {
  mpUi->showAxesCheckBox->setChecked(bShowAxes);
  GLView::getInstance().update();
}

void ViewControl::setDumpDirectory(const QString& dirname) {
  QDir dir(dirname);
  mpUi->dumpDirEdit->setText(dir.absolutePath());
}

void ViewControl::setDumpFrameSize(size_t width, size_t height) {
  mpUi->frameWidthSpinBox->setValue(width);
  mpUi->frameHeightSpinBox->setValue(height);
}

void ViewControl::setDumpFormat(const QString& format) {
  mpUi->dumpFormatEdit->setText(format);
}

void ViewControl::setDumpAll(bool bDumpAll) {
  if (bDumpAll)
    connect(&GLView::getInstance(), SIGNAL(updated()), this, SLOT(dumpFrame()));
  else
    GLView::getInstance().disconnect(SIGNAL(updated()));
    
  mpUi->dumpAllCheckBox->setChecked(bDumpAll);
}


void ViewControl::setRotateFrames(bool bRotateFrames) {
  mpUi->rotateFramesCheckBox->setChecked(bRotateFrames);
}

void ViewControl::setFrameRotation(double f64Yaw) {
  mpUi->frameRotationSpinBox->setValue(f64Yaw * 180.0 / M_PI);
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void ViewControl::dumpFrame() {
  static bool bDumping = false;
  if (bDumping)
    return;

  bDumping = true;
  QApplication::processEvents();

  dumpFrame(mpUi->dumpFormatEdit->text(), mpUi->frameSpinBox->value(),
    mpUi->frameWidthSpinBox->value(), mpUi->frameHeightSpinBox->value());
  if (mpUi->dumpAllCheckBox->isChecked() &&
      mpUi->rotateFramesCheckBox->isChecked())
    GLView::getInstance().getScene().setRotation(
      (mpUi->sceneYawSpinBox->value() + mpUi->frameRotationSpinBox->value())
        * M_PI / 180.0,
      mpUi->scenePitchSpinBox->value() * M_PI / 180.0,
      mpUi->sceneRollSpinBox->value() * M_PI / 180.0);

  bDumping = false;
}

void ViewControl::renderBackground() {
  glPushAttrib(GL_CURRENT_BIT);
  QColor backgroundColor = mPalette.getColor("Background");
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
    backgroundColor.blueF(), 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPopAttrib();
}

void ViewControl::renderFog(double f64Start, double f64End, double f64Density) {
  glPushAttrib(GL_CURRENT_BIT);

  QColor color = mPalette.getColor("Fog");
  float f32Colorfv[] = {color.redF(), color.greenF(), color.blueF(), 1.0};
  double f64Scale = GLView::getInstance().getScene().getScale();
  double f64Distance = GLView::getInstance().getCamera().getViewpointDistance();

  glFogi(GL_FOG_MODE, GL_LINEAR);
  glFogfv(GL_FOG_COLOR, f32Colorfv);
  glFogf(GL_FOG_DENSITY, f64Density);
  glHint(GL_FOG_HINT, GL_DONT_CARE);
  glFogf(GL_FOG_START, f64Distance + f64Start * f64Scale);
  glFogf(GL_FOG_END, f64Distance + f64End * f64Scale);

  glPopAttrib();
}

void ViewControl::renderGround(double f64Radius, double f64Elevation,
  double f64AngleStep, double f64RangeStep) {
  glPushAttrib(GL_CURRENT_BIT);

  glBegin(GL_LINES);
  GLView::getInstance().setColor(mPalette, "Ground");
  for (double f64Angle = -M_PI; f64Angle < M_PI; f64Angle += f64AngleStep) {
    glVertex3f(f64RangeStep * sin(f64Angle), f64RangeStep * cos(f64Angle),
      f64Elevation);
    glVertex3f(f64Radius * sin(f64Angle), f64Radius * cos(f64Angle),
      f64Elevation);
  }
  glEnd();

  for (double f64Range = f64RangeStep; ; f64Range += f64RangeStep) {
    if (f64Range > f64Radius)
      f64Range = f64Radius;

    glBegin(GL_LINE_STRIP);
    for (double f64Angle = -M_PI; f64Angle <= M_PI; f64Angle += f64AngleStep)
      for (double f64Theta = f64Angle; f64Theta <= f64Angle + f64AngleStep;
        f64Theta += f64AngleStep / f64Range)
        glVertex3f(f64Range * sin(f64Theta), f64Range * cos(f64Theta),
          f64Elevation);
    glEnd();

    if (f64Range == f64Radius)
      break;
  }

  glPopAttrib();
}

void ViewControl::renderAxes(double f64Length) {
  glPushAttrib(GL_CURRENT_BIT);
  glBegin(GL_LINES);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(f64Length, 0.0, 0.0);
  glEnd();
  GLView::getInstance().render(f64Length, 0.0, 0.0, "X", 0.2 * f64Length,
    true, true, true);

  glBegin(GL_LINES);
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, f64Length, 0.0);
  glEnd();
  GLView::getInstance().render(0.0, f64Length, 0.0, "Y", 0.2 * f64Length,
    true, true, true);

  glBegin(GL_LINES);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(0.0, 0.0, 0.0);
  glVertex3f(0.0, 0.0, f64Length);
  glEnd();
  GLView::getInstance().render(0, 0, f64Length, "Z", 0.2 * f64Length,
    true, true, true);
  glPopAttrib();
}

void ViewControl::dumpFrame(const QString& format, int i32Frame, size_t width,
  size_t height) {
  QDir dir(mpUi->dumpDirEdit->text());
  if (dir.isReadable()) {
    QString filename;
    QPixmap pixmap;

    filename.sprintf(format.toAscii().constData(), i32Frame);
    pixmap = GLView::getInstance().renderPixmap(width, height);

    QFileInfo fileInfo(dir, filename);
    if (pixmap.save(fileInfo.absoluteFilePath()))
      mpUi->frameSpinBox->setValue(i32Frame + 1);
  }
}

void ViewControl::fontBrowseClicked() {
  QString filename = QFileDialog::getOpenFileName(this,
    "Open Font File", mpUi->fontEdit->text(),
    "TrueType font files (*.ttf)");

  if (!filename.isNull())
    GLView::getInstance().setFont(filename);
}

void ViewControl::groundRadiusChanged(double f64Radius) {
  setGroundRadius(f64Radius);
}

void ViewControl::groundElevationChanged(double f64Elevation) {
  setGroundElevation(f64Elevation);
}

void ViewControl::cameraPositionChanged() {
  GLView::getInstance().getCamera().setPosition(
    mpUi->cameraXSpinBox->value(),
    mpUi->cameraYSpinBox->value(),
    mpUi->cameraZSpinBox->value());
}

void ViewControl::cameraViewpointChanged() {
  GLView::getInstance().getCamera().setViewpoint(
    mpUi->cameraViewXSpinBox->value(),
    mpUi->cameraViewYSpinBox->value(),
    mpUi->cameraViewZSpinBox->value());
}

void ViewControl::sceneTranslationChanged() {
  GLView::getInstance().getScene().setTranslation(
    mpUi->sceneXSpinBox->value(),
    mpUi->sceneYSpinBox->value(),
    mpUi->sceneZSpinBox->value());
}

void ViewControl::sceneRotationChanged() {
  GLView::getInstance().getScene().setRotation(
    mpUi->sceneYawSpinBox->value() * M_PI / 180.0,
    mpUi->scenePitchSpinBox->value() * M_PI / 180.0,
    mpUi->sceneRollSpinBox->value() * M_PI / 180.0);
}

void ViewControl::sceneScaleChanged() {
  GLView::getInstance().getScene().setScale(mpUi->sceneScaleSpinBox->value());
}

void ViewControl::showFogToggled(bool bChecked) {
  setShowFog(bChecked);
}

void ViewControl::showGroundToggled(bool bChecked) {
  setShowGround(bChecked);
}

void ViewControl::showAxesToggled(bool bChecked) {
  setShowAxes(bChecked);
}

void ViewControl::dumpDirBrowseClicked() {
  QString dirname = QFileDialog::getExistingDirectory(this,
    "Select Dump Directory", mpUi->dumpDirEdit->text());

  if (!dirname.isNull())
    mpUi->dumpDirEdit->setText(dirname);
}

void ViewControl::dumpClicked() {
  dumpFrame();
}

void ViewControl::dumpAllToggled(bool bChecked) {
  setDumpAll(bChecked);
}

void ViewControl::colorChanged(const QString& role, const QColor& color) {
  GLView::getInstance().update();
}

void ViewControl::fontChanged(const QString& filename) {
  mpUi->fontEdit->blockSignals(true);
  mpUi->fontEdit->setText(filename);
  mpUi->fontEdit->blockSignals(false);
}

void ViewControl::cameraPositionChanged(const std::vector<double>&
  positionVector) {
  mpUi->cameraXSpinBox->blockSignals(true);
  mpUi->cameraYSpinBox->blockSignals(true);
  mpUi->cameraZSpinBox->blockSignals(true);

  mpUi->cameraXSpinBox->setValue(positionVector[0]);
  mpUi->cameraYSpinBox->setValue(positionVector[1]);
  mpUi->cameraZSpinBox->setValue(positionVector[2]);

  mpUi->cameraXSpinBox->blockSignals(false);
  mpUi->cameraYSpinBox->blockSignals(false);
  mpUi->cameraZSpinBox->blockSignals(false);
}

void ViewControl::cameraViewpointChanged(const std::vector<double>&
  viewpointVector) {
  mpUi->cameraViewXSpinBox->blockSignals(true);
  mpUi->cameraViewYSpinBox->blockSignals(true);
  mpUi->cameraViewZSpinBox->blockSignals(true);

  mpUi->cameraViewXSpinBox->setValue(viewpointVector[0]);
  mpUi->cameraViewYSpinBox->setValue(viewpointVector[1]);
  mpUi->cameraViewZSpinBox->setValue(viewpointVector[2]);

  mpUi->cameraViewXSpinBox->blockSignals(false);
  mpUi->cameraViewYSpinBox->blockSignals(false);
  mpUi->cameraViewZSpinBox->blockSignals(false);
}

void ViewControl::sceneTranslationChanged(const std::vector<double>&
  translationVector) {
  mpUi->sceneXSpinBox->blockSignals(true);
  mpUi->sceneYSpinBox->blockSignals(true);
  mpUi->sceneZSpinBox->blockSignals(true);

  mpUi->sceneXSpinBox->setValue(translationVector[0]);
  mpUi->sceneYSpinBox->setValue(translationVector[1]);
  mpUi->sceneZSpinBox->setValue(translationVector[2]);

  mpUi->sceneXSpinBox->blockSignals(false);
  mpUi->sceneYSpinBox->blockSignals(false);
  mpUi->sceneZSpinBox->blockSignals(false);
}

void ViewControl::sceneRotationChanged(const std::vector<double>&
  rotationVector) {
  mpUi->sceneYawSpinBox->blockSignals(true);
  mpUi->scenePitchSpinBox->blockSignals(true);
  mpUi->sceneRollSpinBox->blockSignals(true);

  mpUi->sceneYawSpinBox->setValue(rotationVector[0] * 180.0 / M_PI);
  mpUi->scenePitchSpinBox->setValue(rotationVector[1] * 180.0 / M_PI);
  mpUi->sceneRollSpinBox->setValue(rotationVector[2] * 180.0 / M_PI);

  mpUi->sceneYawSpinBox->blockSignals(false);
  mpUi->scenePitchSpinBox->blockSignals(false);
  mpUi->sceneRollSpinBox->blockSignals(false);
}

void ViewControl::sceneScaleChanged(double f64Scale) {
  mpUi->sceneScaleSpinBox->blockSignals(true);
  mpUi->sceneScaleSpinBox->setValue(f64Scale);
  mpUi->sceneScaleSpinBox->blockSignals(false);
}

void ViewControl::render(GLView& view, Scene& scene) {
  double f64Radius = mpUi->groundXSpinBox->value();

  renderBackground();
  if (mpUi->showFogCheckBox->isChecked()) {
    glEnable(GL_FOG);
    renderFog(f64Radius, 2.0 * f64Radius, 1.0);
  }
  else
    glDisable(GL_FOG);
  if (mpUi->showGroundCheckBox->isChecked())
    renderGround(f64Radius, mpUi->groundZSpinBox->value(), 30.0 * M_PI / 180.0,
      5.0);
  if (mpUi->showAxesCheckBox->isChecked())
    renderAxes(2.5);
}
