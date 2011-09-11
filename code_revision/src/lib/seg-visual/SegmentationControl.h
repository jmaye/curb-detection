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

/** \file SegmentationControl.h
    \brief This file defines a Qt control for segmentation.
  */

#ifndef SEGMENTATIONCONTROL_H
#define SEGMENTATIONCONTROL_H

#include "visualization/Control.h"
#include "base/Singleton.h"
#include "visualization/GLView.h"
#include "visualization/Scene.h"
#include "data-structures/Grid.h"
#include "data-structures/Component.h"

#include <map>

class Cell;
class Ui_SegmentationControl;

/** The SegmentationControl class represents a Qt control for segmentation.
    \brief Qt control for segmentation
  */
class SegmentationControl :
  public Control,
  public Singleton<SegmentationControl> {
Q_OBJECT
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  SegmentationControl(const SegmentationControl& other);
  /// Assignment operator
  SegmentationControl& operator = (const SegmentationControl& other);
  /** @}
    */

  /** \name Private types definitions
    @{
    */
  /// Color type
  struct Color {
    /// Red component
    GLfloat mRedColor;
    /// Green component
    GLfloat mGreenColor;
    /// Blue component
    GLfloat mBlueColor;
  };
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs control with parameter
  SegmentationControl(bool showSegmentation = true);
  /// Destructor
  ~SegmentationControl();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Show segmentation
  void setShowSegmentation(bool showSegmentation);
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Renders the segmentation
  void renderSegmentation();
  /// Sets a color randomly
  void setColor(Color& color) const;
  /// Sets the segmentation parameter
  void setK(double value);
  /// Segment DEM
  void segment();
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Qt user interface
  Ui_SegmentationControl* mUi;
  /// DEM
  Grid<double, Cell, 2> mDEM;
  /// Segmented components
  std::map<size_t, Component<size_t, double> > mComponents;
  /// Segmentation parameter
  double mK;
  /// Mapping for the random colors
  std::map<size_t, Color> mColors;
  /** @}
    */

protected slots:
  /** \name Qt slots
    @{
    */
  /// Renders the segmentation
  void render(GLView& view, Scene& scene);
  /// DEM updated
  void demUpdated(const Grid<double, Cell, 2>& dem);
  /// Segmentation parameter changed
  void kChanged(double value);
  /// Show the segmentation
  void showSegmentationToggled(bool checked);
  /** @}
    */

signals:
  /** \name Qt signals
    @{
    */
  /** @}
    */

};

#endif // SEGMENTATIONCONTROL_H
