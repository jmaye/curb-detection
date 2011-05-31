#ifndef GLVIEW_H
#define GLVIEW_H

#include "visualization/Singleton.h"
#include "visualization/Palette.h"

#include <QtOpenGL/QGLWidget>
#include <QtGui/QColor>
#include <QtCore/QString>

#include <vector>

class FTPolygonFont;

class GLView :
  public QGLWidget,
  public Singleton<GLView> {
Q_OBJECT

public:
  GLView(QWidget* pParent = 0);
  ~GLView();

  void setColor(const QColor& color);
  void setColor(const Palette& palette, const QString& role);
  void setFont(const QString& filename);
  const QString& getFont() const;
  void setTranslation(double f64X, double f64Y, double f64Z);
  const std::vector<double>& getTranslation() const;
  void setRotation(double f64Yaw, double f64Pitch, double f64Roll);
  const std::vector<double>& getRotation() const;
  void setScale(double f64Scale);
  double getScale() const;
  double getViewpointDistance() const;
  void render(double f64X, double f64Y, double f64Z, const QString& text,
    double f64Scale = 1.0, bool bFaceX = false, bool bFaceY = false,
    bool bFaceZ = false);

protected:
  double correctAngle(double f64Angle) const;
  virtual void mousePressEvent(QMouseEvent* event);
  virtual void mouseMoveEvent(QMouseEvent* event);
  virtual void wheelEvent(QWheelEvent* event);
  virtual void initializeGL();
  virtual void resizeGL(int i32Width, int i32Height);
  virtual void paintGL();
  virtual void paintEvent(QPaintEvent* event);

  QString mFontFilename;
  FTPolygonFont* mpFont;
  std::vector<int> mMouseVector;
  std::vector<double> mTranslationVector;
  std::vector<double> mRotationVector;
  double mf64Scale;
  std::vector<double> mProjectionVector;

signals:
  void fontChanged(const QString& filename);
  void translationChanged(const std::vector<double>& translationVector);
  void rotationChanged(const std::vector<double>& rotationVector);
  void scaleChanged(double f64Scale);
  void render(GLView& view);
  void updated();

};

#endif // GLVIEW_H
