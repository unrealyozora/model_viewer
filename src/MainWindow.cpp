#include "MainWindow.h"
#include "GlWidget.h"
#include "SideMenu.h"
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QVBoxLayout>

std::string MainWindow::modelPath = "";
std::string MainWindow::fallbackPath = "assets/backpack/backpack.obj";
MainWindow::MainWindow() {
  QMenuBar* menuBar = new QMenuBar();
  QMenu* fileMenu = new QMenu("File", this);
  QAction* openAction = new QAction("Open", this);
  fileMenu->addAction(openAction);
  menuBar->addMenu(fileMenu);
  setMenuBar(menuBar);

  QWidget* central = new QWidget(this);
  QHBoxLayout* hLayout = new QHBoxLayout(central);

  GlWidget* glWidget = new GlWidget(this, getModelPath());
  hLayout->addWidget(glWidget, 1);
  setCentralWidget(central);
  SideMenu* sideMenu = new SideMenu(this, glWidget);
  sideMenu->setMinimumWidth(70);
  sideMenu->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
  hLayout->addWidget(sideMenu);

  connect(openAction, &QAction::triggered, this, &MainWindow::OpenFile);
}

const std::string& MainWindow::getModelPath() {
  if (!modelPath.empty()) {

    return MainWindow::modelPath;
  } else {
    return MainWindow::fallbackPath;
  }
}

void MainWindow::setModelPath(const QString& path) {
  modelPath = path.toStdString();
}

void MainWindow::OpenFile() {
  QString filepath = QFileDialog::getOpenFileName(
      this, "Select a file", "", "Model file (*.obj);; Every file (*.*)");
  if (!filepath.isEmpty()) {
    setModelPath(filepath);
    emit updateModelPath();
  } else {
    QMessageBox invalideFileMsg;
    invalideFileMsg.setWindowTitle("Error");
    invalideFileMsg.setText("<p align='center'>Invalid model format<br></p>");
    invalideFileMsg.exec();
  }
}
