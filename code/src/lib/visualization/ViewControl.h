#ifndef VIEWCONTROL_H
#define VIEWCONTROL_H

#include "visualization/Control.h"
#include "visualization/Singleton.h"
#include "visualization/GLView.h"

#include <QtCore/QString>
#include <QtGui/QColor>

#include <vector>

class Ui_ViewControl;

class ViewControl :
  public Control,
  public Singleton<ViewControl> {
Q_OBJECT

public:
  ViewControl(bool bShowFog = true, bool bShowGround = true,
    bool bShowAxes = true);
  ~ViewControl();

  void setBackgroundColor(const QColor& color);
  void setFogColor(const QColor& color);
  void setGroundColor(const QColor& color);
  void setGroundRadius(double f64Radius);
  void setGroundElevation(double f64Elevation);
  void setShowFog(bool bShowFog);
  void setShowGround(bool bShowGround);
  void setShowAxes(bool bShowAxes);
  void setDumpDirectory(const QString& dirname);
  void setDumpFrameSize(size_t width, size_t height);
  void setDumpFormat(const QString& format);
  void setDumpAll(bool bDumpAll);

public slots:
  void dumpFrame();

protected:
  void renderBackground();
  void renderFog(double f64Start, double f64End, double f64Density);
  void renderGround(double f64Radius, double f64Elevation, double f64AngleStep,
    double f64RangeStep);
  void renderAxes(double f64Length);
  void dumpFrame(const QString& format, int i32Frame, size_t width,
    size_t height);

  Ui_ViewControl* mpUi;
  Palette mPalette;

protected slots:
  void fontBrowseClicked();
  void translationChanged();
  void rotationChanged();
  void scaleChanged();
  void groundRadiusChanged(double f64Radius);
  void groundElevationChanged(double f64Elevation);
  void showFogToggled(bool bChecked);
  void showGroundToggled(bool bChecked);
  void showAxesToggled(bool bChecked);
  void dumpDirBrowseClicked();
  void dumpClicked();
  void dumpAllToggled(bool bChecked);
  void colorChanged(const QString& role, const QColor& color);
  void fontChanged(const QString& filename);
  void translationChanged(const std::vector<double>& translationVector);
  void rotationChanged(const std::vector<double>& rotationVector);
  void scaleChanged(double f64Scale);
  void render(GLView& view);

};

#endif
