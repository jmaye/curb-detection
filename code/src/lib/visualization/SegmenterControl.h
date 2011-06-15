/******************************************************************************
 * Copyright (C) 2011 by Jerome Maye                                          *
 * jerome.maye@gmail.com                                                      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

#ifndef SEGMENTERCONTROL_H
#define SEGMENTERCONTROL_H

#include "visualization/Control.h"
#include "visualization/Singleton.h"
#include "visualization/GLView.h"
#include "visualization/Scene.h"
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
  void render(GLView& view, Scene& scene);
  void demUpdated(DEM* pDEM);
  void KChanged(int i32Value);
  void showSegmenterToggled(bool bChecked);

signals:
  void segmenterUpdated(DEM* pDEM,
    const std::multiset<Edge, EdgeCompare>* pEdgeSet);

};

#endif // SEGMENTERCONTROL_H
