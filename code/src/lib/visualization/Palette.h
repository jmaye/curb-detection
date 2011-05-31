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
