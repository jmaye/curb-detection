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

#include "visualization/Palette.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Palette::Palette() {
}

Palette::~Palette() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

Palette::Iterator Palette::getColorBegin() const {
  return mColors.begin();
}

Palette::Iterator Palette::getColorEnd() const {
  return mColors.end();
}

const QString& Palette::getRole(const Iterator& it) const {
  return it->first;
}

void Palette::setColor(const QString& role, const QColor& color) {
  if (mColors[role] != color) {
    mColors[role] = color;
    emit colorChanged(role, color);
  }
}

const QColor& Palette::getColor(const Iterator& it) const {
  return it->second;
}

const QColor& Palette::getColor(const QString& role) const
    throw (OutOfBoundException<std::string>) {
  std::map<QString, QColor>::const_iterator it = mColors.find(role);
  if (it != mColors.end())
    return it->second;
  else
    throw OutOfBoundException<std::string>(role.toStdString(),
      "Palette::getColor(): color role undefined", __FILE__, __LINE__);
}
