#include "MainWindow.h"
#include "GlWidget.h"
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow() {
  QMenuBar* menuBar = new QMenuBar();
  QMenu* fileMenu = new QMenu("File", this);
  GlWidget* glWidget = new GlWidget(this);
  menuBar->addMenu(fileMenu);
  setMenuBar(menuBar);
  setCentralWidget(glWidget);
}
