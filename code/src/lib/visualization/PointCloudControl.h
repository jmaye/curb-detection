#ifndef POINTCLOUDCONTROL_H
#define POINTCLOUDCONTROL_H

#include "data-structures/PointCloud.h"
#include "visualization/Control.h"
#include "visualization/Singleton.h"
#include "visualization/GLView.h"
#include "visualization/Scene.h"

#include <QtCore/QString>
#include <QtGui/QColor>

class Ui_PointCloudControl;

class PointCloudControl :
  public Control,
  public Singleton<PointCloudControl> {
Q_OBJECT

public:
  PointCloudControl(bool bShowPoints = true);
  ~PointCloudControl();

  void setPointColor(const QColor& color);
  void setPointSize(double f64PointSize);
  void setShowPoints(bool bShowPoints);
  void setSmoothPoints(bool bSmoothPoints);
  void setLogFilename(const QString& filename);

protected:
  void renderPoints(double f64Size, bool bSmooth);

  Ui_PointCloudControl* mpUi;
  Palette mPalette;
  PointCloud mPointCloud;

protected slots:
  void logBrowseClicked();
  void colorChanged(const QString& role, const QColor& color);
  void pointSizeChanged(double f64PointSize);
  void showPointsToggled(bool bChecked);
  void smoothPointsToggled(bool bChecked);
  void render(GLView& view, Scene& scene);

signals:
  void pointCloudRead(const PointCloud* pPointCloud);

};

#endif // POINTCLOUDCONTROL_H
