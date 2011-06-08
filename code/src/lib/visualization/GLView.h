#ifndef GLVIEW_H
#define GLVIEW_H

#include "visualization/Singleton.h"
#include "visualization/Palette.h"
#include "visualization/Camera.h"
#include "visualization/Scene.h"

#include <QtOpenGL/QGLWidget>
#include <QtGui/QColor>
#include <QtCore/QString>
#include <QtCore/QPoint>

#include <vector>

class FTPolygonFont;

class GLView :
  public QGLWidget,
  public Singleton<GLView> {
Q_OBJECT

public:
  GLView(QWidget* pParent = 0);
  ~GLView();

  Camera& getCamera();
  const Camera& getCamera() const;
  Scene& getScene();
  const Scene& getScene() const;
  void setColor(const QColor& color);
  void setColor(const Palette& palette, const QString& role);
  void setFont(const QString& filename);
  const QString& getFont() const;
  std::vector<double> unproject(const QPoint& point, double distance);
  void render(double f64X, double f64Y, double f64Z, const QString& text,
    double f64Scale = 1.0, bool bFaceX = false, bool bFaceY = false,
    bool bFaceZ = false);

protected:
  virtual void mousePressEvent(QMouseEvent* event);
  virtual void mouseMoveEvent(QMouseEvent* event);
  virtual void wheelEvent(QWheelEvent* event);
  virtual void initializeGL();
  virtual void resizeGL(int i32Width, int i32Height);
  virtual void paintGL();
  virtual void paintEvent(QPaintEvent* event);

  QString mFontFilename;
  FTPolygonFont* mpFont;
  Camera mCamera;
  Scene mScene;
  std::vector<int> mMouseVector;
  std::vector<int> mViewportVector;
  std::vector<double> mProjectionVector;
  std::vector<double> mModelviewVector;

protected slots:
  void cameraPositionChanged(const std::vector<double>& positionVector);
  void cameraViewpointChanged(const std::vector<double>& viewpointVector);
  void cameraRangeChanged(const std::vector<double>& rangeVector);
  void sceneTranslationChanged(const std::vector<double>& translationVector);
  void sceneRotationChanged(const std::vector<double>& rotationVector);
  void sceneScaleChanged(double f64Scale);

signals:
  void fontChanged(const QString& filename);
  void updated();

};

#endif // GLVIEW_H
