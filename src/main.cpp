#include "MainWindow.h"
#include <QApplication>
#include <QDir>
#include <QSurfaceFormat>

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  QSurfaceFormat format;
  format.setVersion(3, 3);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);

  QDir::setCurrent("../");

  MainWindow* window = new MainWindow();
  window->resize(1024, 512);
  window->show();
  return app.exec();
}
