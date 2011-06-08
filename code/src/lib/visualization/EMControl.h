#ifndef EMCONTROL_H
#define EMCONTROL_H

#include "visualization/Control.h"
#include "visualization/Singleton.h"
#include "visualization/GLView.h"
#include "visualization/Scene.h"
#include "data-structures/DEM.h"
#include "data-structures/Edge.h"

#include <map>
#include <set>

#include <stdint.h>

class Ui_EMControl;

class EMControl :
  public Control,
  public Singleton<EMControl> {
Q_OBJECT

  struct Color {
    GLfloat mRedColorByte;
    GLfloat mGreenColorByte;
    GLfloat mBlueColorByte;
  };

public:
  EMControl(bool bShowEM = true);
  ~EMControl();

  void setShowEM(bool bShowEM);
  void setEMIterations(uint32_t u32Iterations);
  void setEMTolerance(double f64Tol);
  void setBPIterations(uint32_t u32Iterations);
  void setBPTolerance(double f64Tol);

protected:
  void renderEM();
  void setColor(Color& color) const;

  Ui_EMControl* mpUi;
  DEM* mpDEM;
  std::map<uint32_t, Color> mColorMap;
  const std::multiset<Edge, EdgeCompare>* mpEdgeSet;
  uint32_t mu32EMIterations;
  double mf64EMTolerance;
  uint32_t mu32BPIterations;
  double mf64BPTolerance;

protected slots:
  void render(GLView& view, Scene& scene);
  void showEMToggled(bool bChecked);
  void EMIterationsChanged(int i32Iterations);
  void EMToleranceChanged(double f64Tol);
  void BPIterationsChanged(int i32Iterations);
  void BPToleranceChanged(double f64Tol);
  void runEMPushed();
  void segmenterUpdated(DEM* pDEM,
    const std::multiset<Edge, EdgeCompare>* pEdgeSet);

};

#endif // EMCONTROL_H
