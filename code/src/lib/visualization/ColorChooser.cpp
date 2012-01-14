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

#include "visualization/ColorChooser.h"

#include <QtGui/QLabel>
#include <QtGui/QFrame>
#include <QtGui/QPushButton>
#include <QtGui/QColorDialog>
#include <QtGui/QColor>
#include <QtCore/QString>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ColorChooser::ColorChooser(QWidget* parent) :
  QWidget(parent),
  mLayout(this),
  mPalette(0) {
  mLayout.setContentsMargins(0, 0, 0, 0);
  connect(&mSignalMapper, SIGNAL(mapped(const QString&)), this,
    SLOT(buttonClicked(const QString&)));
}

ColorChooser::~ColorChooser() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void ColorChooser::setPalette(Palette* palette) {
  while (mLayout.count()) {
    if (mLayout.itemAt(0)->widget())
      delete mLayout.itemAt(0)->widget();
  }
  if (this->mPalette)
    this->mPalette->disconnect(
      SIGNAL(colorChanged(const QString&, const QColor&)));
  this->mPalette = palette;
  if (this->mPalette) {
    connect(this->mPalette, SIGNAL(colorChanged(const QString&,
      const QColor&)), this, SLOT(colorChanged(const QString&, const QColor&)));
    for (Palette::Iterator it = this->mPalette->getColorBegin();
        it != this->mPalette->getColorEnd(); ++it)
      colorChanged(this->mPalette->getRole(it), this->mPalette->getColor(it));
  }
}

Palette* ColorChooser::getPalette() const {
  return mPalette;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void ColorChooser::buttonClicked(const QString& role) {
  QColor color = QColorDialog::getColor(mPalette->getColor(role), this,
    "Choose " + role + " Color");
  if (color.isValid())
    mPalette->setColor(role, color);
}

void ColorChooser::colorChanged(const QString& role, const QColor& color) {
  if (!mSignalMapper.mapping(role)) {
    int row = mLayout.rowCount();
    QLabel* label = new QLabel(role + " color:", this);
    QFrame* frame = new QFrame(this);
    frame->setAutoFillBackground(true);
    frame->setFrameShape(QFrame::Box);
    frame->setFrameShadow(QFrame::Raised);
    frame->setMinimumWidth(50);
    QPushButton* button = new QPushButton("Choose...", this);
    mLayout.addWidget(label, row, 0);
    mLayout.setColumnStretch(1, 1);
    mLayout.addWidget(frame, row, 2);
    mLayout.addWidget(button, row, 3);
    connect(button, SIGNAL(clicked()), &mSignalMapper, SLOT(map()));
    mSignalMapper.setMapping(button, role);
  }
  QPalette palette;
  palette.setColor(QPalette::Window, color);
  int index = mLayout.indexOf((QWidget*)mSignalMapper.mapping(role));
  QWidget* frame = mLayout.itemAt(index - 1)->widget();
  frame->setPalette(palette);
}
