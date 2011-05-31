#ifndef DEMCONTROL_H
#define DEMCONTROL_H

#include "data-structures/DEM.h"
#include "data-structures/PointCloud.h"
#include "visualization/Control.h"
#include "visualization/Singleton.h"
#include "visualization/GLView.h"

#include <QtCore/QString>
#include <QtGui/QColor>

class Ui_DEMControl;

class DEMControl :
  public Control,
  public Singleton<DEMControl> {
Q_OBJECT

public:
  DEMControl(bool bShowDEM = true);
  ~DEMControl();

  void setLineColor(const QColor& color);
  void setLineSize(double f64LineSize);
  void setShowDEM(bool bShowDEM);
  void setSmoothLines(bool bSmoothLines);

protected:
  void renderDEM(double f64Size, bool bSmooth);

  Ui_DEMControl* mpUi;
  Palette mPalette;
  DEM* mpDEM;
  const PointCloud* mpPointCloud;

protected slots:
  void colorChanged(const QString& role, const QColor& color);
  void lineSizeChanged(double f64LineSize);
  void showDEMToggled(bool bChecked);
  void smoothLinesToggled(bool bChecked);
  void pointCloudRead(const PointCloud* pPointCloud);
  void demChanged();
  void render(GLView& view);

signals:
  void demUpdated(DEM* pDEM);

};

#endif // DEMCONTROL_H
