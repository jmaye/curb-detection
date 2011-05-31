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

ColorChooser::ColorChooser(QWidget* pParent) :
  QWidget(pParent),
  mLayout(this),
  mpPalette(0) {
  mLayout.setContentsMargins(0, 0, 0, 0);

  connect(&mSignalMapper, SIGNAL(mapped(const QString&)), this,
    SLOT(buttonClicked(const QString&)));
}

ColorChooser::~ColorChooser() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void ColorChooser::setPalette(Palette* pPalette) {
  while (mLayout.count()) {
    if (mLayout.itemAt(0)->widget())
      delete mLayout.itemAt(0)->widget();
  }
  if (this->mpPalette)
    this->mpPalette->disconnect(
      SIGNAL(colorChanged(const QString&, const QColor&)));

  this->mpPalette = pPalette;

  if (this->mpPalette) {
    connect(this->mpPalette, SIGNAL(colorChanged(const QString&,
      const QColor&)), this, SLOT(colorChanged(const QString&, const QColor&)));
    for (Palette::Iterator it = this->mpPalette->getColorBegin();
        it != this->mpPalette->getColorEnd(); ++it)
      colorChanged(this->mpPalette->getRole(it), this->mpPalette->getColor(it));
  }
}

Palette* ColorChooser::getPalette() const {
  return mpPalette;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void ColorChooser::buttonClicked(const QString& role) {
  QColor color = QColorDialog::getColor(mpPalette->getColor(role), this,
    "Choose " + role + " Color");
  if (color.isValid())
    mpPalette->setColor(role, color);
}

void ColorChooser::colorChanged(const QString& role, const QColor& color) {
  if (!mSignalMapper.mapping(role)) {
    int i32Row = mLayout.rowCount();

    QLabel* label = new QLabel(role + " color:", this);
    QFrame* frame = new QFrame(this);
    frame->setAutoFillBackground(true);
    frame->setFrameShape(QFrame::Box);
    frame->setFrameShadow(QFrame::Raised);
    frame->setMinimumWidth(50);
    QPushButton* button = new QPushButton("Choose...", this);

    mLayout.addWidget(label, i32Row, 0);
    mLayout.setColumnStretch(1, 1);
    mLayout.addWidget(frame, i32Row, 2);
    mLayout.addWidget(button, i32Row, 3);

    connect(button, SIGNAL(clicked()), &mSignalMapper, SLOT(map()));
    mSignalMapper.setMapping(button, role);
  }

  QPalette palette;
  palette.setColor(QPalette::Window, color);
  int i32Index = mLayout.indexOf((QWidget*)mSignalMapper.mapping(role));
  QWidget* frame = mLayout.itemAt(i32Index - 1)->widget();
  frame->setPalette(palette);
}
