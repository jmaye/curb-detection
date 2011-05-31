#ifndef SEGMENTERCONTROL_H
#define SEGMENTERCONTROL_H

#include "visualization/Control.h"
#include "visualization/Singleton.h"
#include "visualization/GLView.h"
#include "data-structures/DEM.h"
#include "data-structures/Edge.h"

#include <set>

#include <stdint.h>

class Ui_SegmenterControl;

class SegmenterControl :
  public Control,
  public Singleton<SegmenterControl> {
Q_OBJECT

  struct Color {
    GLfloat mRedColorByte;
    GLfloat mGreenColorByte;
    GLfloat mBlueColorByte;
  };

public:
  SegmenterControl(bool bShowSegmenter = true);
  ~SegmenterControl();

  void setShowSegmenter(bool bShowSegmenter);

protected:
  void renderSegmenter();
  void setColor(Color& color) const;
  void setK(int i32K);

  Ui_SegmenterControl* mpUi;
  DEM* mpDEM;
  uint32_t mu32K;
  std::map<uint32_t, Color> mColorMap;
  std::map<std::pair<uint32_t, uint32_t>, uint32_t> mLabelsMap;
  std::map<uint32_t, uint32_t> mSupportsMap;
  std::multiset<Edge, EdgeCompare> mEdgeSet;

protected slots:
  void render(GLView& view);
  void demUpdated(DEM* pDEM);
  void KChanged(int i32Value);
  void showSegmenterToggled(bool bChecked);

signals:
  void segmenterUpdated(DEM* pDEM, const std::map<std::pair<uint32_t, uint32_t>,
    uint32_t>* pLabelsMap, const std::map<uint32_t, uint32_t>* pSupportsMap,
    const std::multiset<Edge, EdgeCompare>* pEdgeSet);

};

#endif // SEGMENTERCONTROL_H
