#include "SideMenu.h"
#include <QHBoxLayout>

SideMenu::SideMenu(QWidget* parent, GlWidget* glWidget) : QWidget(parent) {
  QHBoxLayout* layout = new QHBoxLayout(this);

  layout->setAlignment(Qt::AlignCenter | Qt::AlignBottom);
  randomColorTest = new QPushButton("Random Color", this);
  connect(randomColorTest, &QPushButton::clicked, this,
          [glWidget]() { glWidget->randDirColor(); });
};
