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
  mTranslationVector(3, 0.0),
  mRotationVector(3, 0.0),
  mf64Scale(1.0),
  mProjectionVector(2, 0.0) {
  setFont("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf");
  setTranslation(20.0, 0.0, 0.0);
  setRotation(-10.0 * M_PI / 180.0, -5.0 * M_PI / 180.0, 0.0);
  setScale(1.0);
}

GLView::~GLView() {
  if (mpFont)
    delete mpFont;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

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

void GLView::setTranslation(double f64X, double f64Y, double f64Z) {
  if ((f64X != mTranslationVector[0]) || (f64Y != mTranslationVector[1]) ||
    (f64Z != mTranslationVector[2])) {
    mTranslationVector[0] = f64X;
    mTranslationVector[1] = f64Y;
    mTranslationVector[2] = f64Z;

    emit translationChanged(mTranslationVector);
    update();
  }
}

const std::vector<double>& GLView::getTranslation() const {
  return mTranslationVector;
}

void GLView::setRotation(double f64Yaw, double f64Pitch, double f64Roll) {
  if ((f64Yaw != mRotationVector[0]) || (f64Pitch != mRotationVector[1]) ||
    (f64Roll != mRotationVector[2])) {
    mRotationVector[0] = correctAngle(f64Yaw);
    mRotationVector[1] = correctAngle(f64Pitch);
    mRotationVector[2] = correctAngle(f64Roll);

    emit rotationChanged(mRotationVector);
    update();
  }
}

const std::vector<double>& GLView::getRotation() const {
  return mRotationVector;
}

void GLView::setScale(double f64Scale) {
  if (this->mf64Scale != f64Scale) {
    this->mf64Scale = f64Scale;

    emit scaleChanged(this->mf64Scale);
    update();
  }
}

double GLView::getScale() const {
  return mf64Scale;
}

double GLView::getViewpointDistance() const {
  return sqrt(mTranslationVector[0] * mTranslationVector[0] +
    mTranslationVector[1] * mTranslationVector[1] +
    mTranslationVector[2] * mTranslationVector[2]);
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

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
      glRotatef(-mRotationVector[0] * 180.0 / M_PI, 0, 0, 1);
    if (bFaceY)
      glRotatef(-mRotationVector[1] * 180.0 / M_PI, 0, 1, 0);
    if (bFaceX)
      glRotatef(-mRotationVector[2] * 180.0 / M_PI, 1, 0, 0);
    glRotatef(90.0, 1, 0, 0);
    glRotatef(-90.0, 0, 1, 0);
    glScalef(f64Scale * 1e-2, f64Scale * 1e-2, f64Scale * 1e-2);
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

  if (event->buttons() == Qt::LeftButton)
    setRotation(mRotationVector[0] - M_PI / width() * i32DeltaX,
      mRotationVector[1] + M_PI / height() * i32DeltaY, mRotationVector[2]);
  else if (event->buttons() == Qt::RightButton)
    setTranslation(mTranslationVector[0] - 2.0 * mProjectionVector[0] /
      width() * i32DeltaY, mTranslationVector[1] - 2.0 * mProjectionVector[1] /
      height() * i32DeltaX, mTranslationVector[2]);

  mMouseVector[0] = event->globalX();
  mMouseVector[1] = event->globalY();
}

void GLView::wheelEvent(QWheelEvent* event) {
  double f64DeltaScale = 1e-2;
  setScale(mf64Scale * (1.0 + f64DeltaScale * event->delta() / 8.0));
}

void GLView::initializeGL() {
  glEnable(GL_DEPTH_TEST);

  glEnable (GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GLView::resizeGL(int i32Width, int i32Height) {
  glViewport(0, 0, i32Width, i32Height);

  double f64Aspect = (double)i32Width / i32Height;
  double f64Near = 0.001;
  double f64Far = 1000.0;
  double f64Fov = 45.0 * M_PI / 180.0;

  double f64Top = tan(f64Fov * 0.5) * f64Near;
  double f64Bottom = -f64Top;
  double f64Left = f64Aspect * f64Bottom;
  double f64Right = f64Aspect * f64Top;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(f64Left, f64Right, f64Bottom, f64Top, f64Near, f64Far);

  mProjectionVector[0] = 2.0 * f64Near / (f64Right - f64Left);
  mProjectionVector[1] = 2.0 * f64Near / (f64Top - f64Bottom);
}

void GLView::paintGL() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef(90.0, 0, 0, 1);
  glRotatef(90.0, 0, 1, 0);
  glTranslatef(mTranslationVector[0], mTranslationVector[1],
    mTranslationVector[2]);
  glRotatef(mRotationVector[2] * 180.0 / M_PI, 1, 0, 0);
  glRotatef(mRotationVector[1] * 180.0 / M_PI, 0, 1, 0);
  glRotatef(mRotationVector[0] * 180.0 / M_PI, 0, 0, 1);
  glScalef(mf64Scale, mf64Scale, mf64Scale);

  emit render(*this);
}

void GLView::paintEvent(QPaintEvent* event) {
  QGLWidget::paintEvent(event);
  emit updated();
}

double GLView::correctAngle(double f64Angle) const {
  if (f64Angle >= 0.0)
    while (f64Angle >= M_PI) f64Angle -= 2.0 * M_PI;
  else
    while (f64Angle < -M_PI) f64Angle += 2.0 * M_PI;

  return f64Angle;
}
