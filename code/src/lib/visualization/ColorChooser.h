#ifndef COLORCHOOSER_H
#define COLORCHOOSER_H

#include "visualization/Palette.h"

#include <QtCore/QSignalMapper>
#include <QtGui/QWidget>
#include <QtGui/QGridLayout>

class ColorChooser :
  public QWidget {
Q_OBJECT

public:
  ColorChooser(QWidget* pParent = 0);
  ~ColorChooser();

  void setPalette(Palette* pPalette);
  Palette* getPalette() const;

protected:
  QGridLayout mLayout;
  QSignalMapper mSignalMapper;
  Palette* mpPalette;

protected slots:
  void buttonClicked(const QString& role);
  void colorChanged(const QString& role, const QColor& color);

};

#endif // COLORCHOOSER_H
