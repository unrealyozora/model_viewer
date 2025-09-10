#include "MainWindow.h"
#include <QApplication>
#include <QDir>
#include <QSurfaceFormat>

int main(int argc, char* argv[]) {

  QApplication app(argc, argv);
  QDir::setCurrent("../");

  QSurfaceFormat format;
  format.setVersion(3, 3);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);

  qDebug() << QDir::current();

  MainWindow* window = new MainWindow();
  window->resize(1024, 512);
  window->show();
  return app.exec();
}
