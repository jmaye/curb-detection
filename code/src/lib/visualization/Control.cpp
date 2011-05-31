#include "visualization/Control.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Control::Control() :
  mMenu(this) {
}

Control::~Control() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

QMenu& Control::getMenu() {
  return mMenu;
}

const QMenu& Control::getMenu() const {
  return mMenu;
}
