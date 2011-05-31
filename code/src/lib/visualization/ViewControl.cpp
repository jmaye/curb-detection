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

  connect(&GLView::getInstance(),
    SIGNAL(translationChanged(const std::vector<double>&)), this,
    SLOT(translationChanged(const std::vector<double>&)));
  translationChanged(GLView::getInstance().getTranslation());
  connect(&GLView::getInstance(),
    SIGNAL(rotationChanged(const std::vector<double>&)), this,
    SLOT(rotationChanged(const std::vector<double>&)));
  rotationChanged(GLView::getInstance().getRotation());
  connect(&GLView::getInstance(), SIGNAL(scaleChanged(double)), this,
    SLOT(scaleChanged(double)));
  scaleChanged(GLView::getInstance().getScale());

  connect(&GLView::getInstance(), SIGNAL(render(GLView&)), this,
    SLOT(render(GLView&)));
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

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void ViewControl::dumpFrame() {
  dumpFrame(mpUi->dumpFormatEdit->text(), mpUi->frameSpinBox->value(),
    mpUi->frameWidthSpinBox->value(), mpUi->frameHeightSpinBox->value());
}

void ViewControl::renderBackground() {
  QColor backgroundColor = mPalette.getColor("Background");
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
    backgroundColor.blueF(), 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ViewControl::renderFog(double f64Start, double f64End, double f64Density) {
  QColor color = mPalette.getColor("Fog");
  float f32Colorfv[] = {color.redF(), color.greenF(), color.blueF(), 1.0};
  double f64Scale = GLView::getInstance().getScale();
  double f64Distance = GLView::getInstance().getViewpointDistance();

  glFogi(GL_FOG_MODE, GL_LINEAR);
  glFogfv(GL_FOG_COLOR, f32Colorfv);
  glFogf(GL_FOG_DENSITY, f64Density);
  glHint(GL_FOG_HINT, GL_DONT_CARE);
  glFogf(GL_FOG_START, f64Distance + f64Start * f64Scale);
  glFogf(GL_FOG_END, f64Distance + f64End * f64Scale);
}

void ViewControl::renderGround(double f64Radius, double f64Elevation,
  double f64AngleStep, double f64RangeStep) {
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
}

void ViewControl::renderAxes(double f64Length) {
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

void ViewControl::translationChanged() {
  GLView::getInstance().setTranslation(mpUi->xSpinBox->value(),
    mpUi->ySpinBox->value(), mpUi->zSpinBox->value());
}

void ViewControl::rotationChanged() {
  GLView::getInstance().setRotation(mpUi->yawSpinBox->value() * M_PI / 180.0,
    mpUi->pitchSpinBox->value() * M_PI / 180.0,
    mpUi->rollSpinBox->value() * M_PI / 180.0);
}

void ViewControl::scaleChanged() {
  GLView::getInstance().setScale(mpUi->scaleSpinBox->value());
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

void ViewControl::translationChanged(const std::vector<double>&
  translationVector) {
  mpUi->xSpinBox->blockSignals(true);
  mpUi->ySpinBox->blockSignals(true);
  mpUi->zSpinBox->blockSignals(true);
  
  mpUi->xSpinBox->setValue(translationVector[0]);
  mpUi->ySpinBox->setValue(translationVector[1]);
  mpUi->zSpinBox->setValue(translationVector[2]);

  mpUi->xSpinBox->blockSignals(false);
  mpUi->ySpinBox->blockSignals(false);
  mpUi->zSpinBox->blockSignals(false);
}

void ViewControl::rotationChanged(const std::vector<double>& rotationVector) {
  mpUi->yawSpinBox->blockSignals(true);
  mpUi->pitchSpinBox->blockSignals(true);
  mpUi->rollSpinBox->blockSignals(true);

  mpUi->yawSpinBox->setValue(rotationVector[0] * 180.0 / M_PI);
  mpUi->pitchSpinBox->setValue(rotationVector[1] * 180.0 / M_PI);
  mpUi->rollSpinBox->setValue(rotationVector[2] * 180.0 / M_PI);

  mpUi->yawSpinBox->blockSignals(false);
  mpUi->pitchSpinBox->blockSignals(false);
  mpUi->rollSpinBox->blockSignals(false);
}

void ViewControl::scaleChanged(double f64Scale) {
  mpUi->scaleSpinBox->blockSignals(true);
  mpUi->scaleSpinBox->setValue(f64Scale);
  mpUi->scaleSpinBox->blockSignals(false);
}

void ViewControl::render(GLView& view) {
  double radius = mpUi->groundXSpinBox->value();

  renderBackground();
  if (mpUi->showFogCheckBox->isChecked()) {
    glEnable(GL_FOG);
    renderFog(radius, 2.0 * radius, 1.0);
  }
  else
    glDisable(GL_FOG);
  if (mpUi->showGroundCheckBox->isChecked())
    renderGround(radius, mpUi->groundZSpinBox->value(), 30.0 * M_PI / 180.0,
      5.0);
  if (mpUi->showAxesCheckBox->isChecked())
    renderAxes(2.5);
}
