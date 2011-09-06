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

/** \file ColorChooser.h
    \brief This file contains a color chooser widget for Qt
  */

#ifndef COLORCHOOSER_H
#define COLORCHOOSER_H

#include "visualization/Palette.h"

#include <QtCore/QSignalMapper>
#include <QtGui/QWidget>
#include <QtGui/QGridLayout>

/** The ColorChooser class represents a color chooser widget for Qt.
    \brief Color chooser widget for Qt
  */
class ColorChooser :
  public QWidget {
Q_OBJECT
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  ColorChooser(const ColorChooser& other);
  /// Assignment operator
  ColorChooser& operator = (const ColorChooser& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs color chooser from parent
  ColorChooser(QWidget* parent = 0);
  /// Destructor
  ~ColorChooser();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the palette
  void setPalette(Palette* palette);
  /// Returns the palette
  Palette* getPalette() const;
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Layout of the widget
  QGridLayout mLayout;
  /// Signal mapper
  QSignalMapper mSignalMapper;
  /// Palette
  Palette* mPalette;
  /** @}
    */

protected slots:
  /** \name Qt slots
    @{
    */
  /// Button clicked
  void buttonClicked(const QString& role);
  /// Color changed
  void colorChanged(const QString& role, const QColor& color);
  /** @}
    */

};

#endif // COLORCHOOSER_H
