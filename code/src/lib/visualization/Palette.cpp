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
  return mColorsMap.begin();
}

Palette::Iterator Palette::getColorEnd() const {
  return mColorsMap.end();
}

const QString& Palette::getRole(const Iterator& it) const {
  return it->first;
}

void Palette::setColor(const QString& role, const QColor& color) {
  if (mColorsMap[role] != color) {
    mColorsMap[role] = color;
    emit colorChanged(role, color);
  }
}

const QColor& Palette::getColor(const Iterator& it) const {
  return it->second;
}

const QColor& Palette::getColor(const QString& role) const
  throw (OutOfBoundException) {
  std::map<QString, QColor>::const_iterator it = mColorsMap.find(role);

  if (it != mColorsMap.end())
    return it->second;
  else
    throw OutOfBoundException("Palette::getColor(): color role undefined");
}
