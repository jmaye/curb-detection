#ifndef CAMERA_H
#define CAMERA_H

#include <QtCore/QObject>

#include <vector>

class GLView;

class Camera :
  public QObject {
Q_OBJECT

public:
  Camera(double f64X = -20.0, double f64Y = 0.0, double f64Z = 0.0,
    double f64Near = 0.1, double f64Far = 1000.0);
  ~Camera();

  void setPosition(double f64X, double f64Y, double f64Z);
  const std::vector<double>& getPosition() const;
  void setViewpoint(double f64X, double f64Y, double f64Z);
  const std::vector<double>& getViewpoint() const;
  void setRange(double f64Near, double f64Far);
  const std::vector<double>& getRange() const;
  const std::vector<double>& getProjection() const;
  double getViewpointDistance() const;

  void setup(GLView& view, double f64Width, double f64Height);

protected:
  std::vector<double> mPositionVector;
  std::vector<double> mViewpointVector;
  std::vector<double> mRangeVector;
  std::vector<double> mProjectionVector;

signals:
  void positionChanged(const std::vector<double>& positionVector);
  void viewpointChanged(const std::vector<double>& viewpointVector);
  void rangeChanged(const std::vector<double>& rangeVector);

};

#endif
