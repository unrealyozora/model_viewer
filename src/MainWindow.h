#ifndef VIEW_MAIN_WINDOW_H
#define VIEW_MAIN_WINDOW_H
#include <QMainWindow>
#include <QWidget>

class MainWindow : public QMainWindow {
  Q_OBJECT

private:
  static std::string modelPath;
  static std::string fallbackPath;

public:
  MainWindow();
  void OpenFile();
  static const std::string& getModelPath();
  void setModelPath(const QString& path);
signals:
  void updateModelPath();
};

#endif // !VIEW_MAIN_WINDOW_H
