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

/** \file Control.h
    \brief This file defines a Qt control
  */

#ifndef CONTROL_H
#define CONTROL_H

#include <QtGui/QWidget>
#include <QtGui/QMenu>

/** The Control class represents a Qt control.
    \brief Qt control
  */
class Control :
  public QWidget {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  Control(const Control& other);
  /// Assignment operator
  Control& operator = (const Control& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  Control();
  /// Destructor
  virtual ~Control();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the menu
  QMenu& getMenu();
  /// Returns the menu
  const QMenu& getMenu() const;
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Menu
  QMenu mMenu;
  /** @}
    */

};

#endif // CONTROL_H
