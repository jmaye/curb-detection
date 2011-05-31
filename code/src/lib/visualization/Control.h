#ifndef CONTROL_H
#define CONTROL_H

#include <QtGui/QWidget>
#include <QtGui/QMenu>

class Control :
  public QWidget {
Q_OBJECT

public:
  Control();
  ~Control();

  QMenu& getMenu();
  const QMenu& getMenu() const;

protected:
  QMenu mMenu;

};

#endif // CONTROL_H
