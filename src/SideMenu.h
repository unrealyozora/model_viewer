#ifndef SIDE_MENU_H
#define SIDE_MENU_H
#include "GlWidget.h"
#include <QPushButton>
#include <QWidget>

class SideMenu : public QWidget {
  Q_OBJECT
private:
  QPushButton* randomColorTest;

public:
  SideMenu(QWidget* parent, GlWidget* glWidget);
signals:
  void newColor();
};

#endif // !SIDE_MENU_H
