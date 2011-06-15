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
