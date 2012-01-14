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

/** \file Palette.h
    \brief This file contains a palette implementation for OpenGL
  */

#ifndef PALETTE_H
#define PALETTE_H

#include "exceptions/OutOfBoundException.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtGui/QColor>

#include <map>

/** The Palette class represents a palette in OpenGL.
    \brief Palette for OpenGL
  */
class Palette :
  public QObject {
Q_OBJECT
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  Palette(const Palette& other);
  /// Assignment operator
  Palette& operator = (const Palette& other);
  /** @}
    */

public:
  /** \name Type definitions
    @{
    */
  /// Iterator for the palette
  typedef std::map<QString, QColor>::const_iterator Iterator;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  Palette();
  /// Destructor
  ~Palette();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns iterator at the start of the map
  Iterator getColorBegin() const;
  /// Returns iterator at the end of the map
  Iterator getColorEnd() const;
  /// Returns color role
  const QString& getRole(const Iterator& it) const;
  /// Sets color role
  void setColor(const QString& role, const QColor& color);
  /// Returns a color
  const QColor& getColor(const Iterator& it) const;
  /// Returns a color
  const QColor& getColor(const QString& role) const
    throw (OutOfBoundException<std::string>);
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Mapping between colors and role
  std::map<QString, QColor> mColors;
  /** @}
    */

signals:
  /** \name Qt signals
    @{
    */
  /// Color has changed
  void colorChanged(const QString& role, const QColor& color);
  /** @}
    */

};

#endif // PALETTE_H
