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

#ifndef PALETTE_H
#define PALETTE_H

#include "exceptions/OutOfBoundException.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtGui/QColor>

#include <map>

class Palette :
  public QObject {
Q_OBJECT

public:
  typedef std::map<QString, QColor>::const_iterator Iterator;

  Palette();
  ~Palette();

  Iterator getColorBegin() const;
  Iterator getColorEnd() const;
  const QString& getRole(const Iterator& it) const;
  void setColor(const QString& role, const QColor& color);
  const QColor& getColor(const Iterator& it) const;
  const QColor& getColor(const QString& role) const throw (OutOfBoundException);

protected:
  std::map<QString, QColor> mColorsMap;

signals:
  void colorChanged(const QString& role, const QColor& color);

};

#endif // PALETTE_H
