#ifndef SCENE_H
#define SCENE_H

#include <QtCore/QObject>

#include <vector>

class GLView;

class Scene :
  public QObject {
Q_OBJECT

public:
  Scene();
  ~Scene();

  void setTranslation(double f64X, double f64Y, double f64Z);
  const std::vector<double>& getTranslation() const;
  void setRotation(double f64Yaw, double f64Pitch, double f64Roll);
  const std::vector<double>& getRotation() const;
  void setScale(double f64Scale);
  double getScale() const;

  void setup(GLView& view);
  void render(GLView& view);

protected:
  double correctAngle(double f64Angle) const;

  std::vector<double> mTranslationVector;
  std::vector<double> mRotationVector;
  double mf64Scale;

signals:
  void translationChanged(const std::vector<double>& translationVector);
  void rotationChanged(const std::vector<double>& rotationVector);
  void scaleChanged(double f64Scale);
  void render(GLView& view, Scene& scene);

};

#endif
