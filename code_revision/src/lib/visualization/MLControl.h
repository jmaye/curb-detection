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

/** \file MLControl.h
    \brief This file defines a Qt control for ML segmentation.
  */

#ifndef MLCONTROL_H
#define MLCONTROL_H

#include "visualization/Control.h"
#include "base/Singleton.h"
#include "visualization/GLView.h"
#include "visualization/Scene.h"
#include "data-structures/Grid.h"
#include "data-structures/Cell.h"
#include "data-structures/Component.h"

#include <tr1/unordered_map>
#include <vector>

class Ui_MLControl;

/** The MLControl class represents a Qt control for ML segmentation.
    \brief Qt control for ML segmentation
  */
class MLControl :
  public Control,
  public Singleton<MLControl> {
Q_OBJECT
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  MLControl(const MLControl& other);
  /// Assignment operator
  MLControl& operator = (const MLControl& other);
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
  MLControl(bool showML = true);
  /// Destructor
  ~MLControl();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Show ML segmentation
  void setShowML(bool showMLSegmentation);
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Renders the ML segmentation
  void renderML();
  /// Returns a random color
  void getColor(Color& color) const;
  /// Sets the ML parameter
  void setK(double value);
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Qt user interface
  Ui_MLControl* mUi;
  /// DEM
  Grid<double, Cell, 2> mDEM;
  /// Segmented components
  std::tr1::unordered_map<size_t, Component<Grid<double, Cell, 2>::Index,
    double> > mComponents;
  /// Segmentation parameter
  double mK;
  /// Vector of random colors
  std::vector<Color> mColors;
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
  /// Show the ML segmentation
  void showMLToggled(bool checked);
  /** @}
    */

signals:
  /** \name Qt signals
    @{
    */
  /** @}
    */

};

#endif // MLCONTROL_H
