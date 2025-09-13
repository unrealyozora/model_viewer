#include "Camera/Camera.h"
#include "Light/Light.h"
#include "MainWindow.h"
#include "Model/Model.h"
#include "Shader/Shader.h"
#include <QElapsedTimer>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <glm/glm.hpp>

class GlWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
  Q_OBJECT
public:
  // STRONG ASSUMPTION: PARENT IS ALWAYS OF TYPE MainWindow
  GlWidget(MainWindow* parent, const std::string& modelPath);

  Shader* modelShader;
  Camera* testCamera;
  Light* testLight;
  std::string testModelPath;
  Model* testModel;
  QElapsedTimer* timer;
  float deltaTime = 0.0f;
  float lastFrame = 0.0f;
  bool keys[1024] = {false};

protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void keyPressEvent(QKeyEvent* e) override;
  void keyReleaseEvent(QKeyEvent* e) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void wheelEvent(QWheelEvent* event) override;
  void processInput(float deltaTime);
  void changeModelPath(const std::string& path);
public slots:
  void onModelPathUpdated();
};
