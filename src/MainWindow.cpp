#include "MainWindow.h"
#include "GlWidget.h"
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>

std::string MainWindow::modelPath = "";
std::string MainWindow::fallbackPath = "assets/base/base.obj";
MainWindow::MainWindow() {
  QMenuBar* menuBar = new QMenuBar();
  QMenu* fileMenu = new QMenu("File", this);
  QAction* openAction = new QAction("Open", this);
  GlWidget* glWidget = new GlWidget(this, getModelPath());
  menuBar->addMenu(fileMenu);
  fileMenu->addAction(openAction);
  setMenuBar(menuBar);
  setCentralWidget(glWidget);

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
