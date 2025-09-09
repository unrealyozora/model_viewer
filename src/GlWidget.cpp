#include "GlWidget.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"
#include <QDebug>
#include <QKeyEvent>
#include <QOpenGLContext>
#include <QTimer>
#include <qcursor.h>
#include <qevent.h>
#include <qnamespace.h>
#include <qopenglext.h>
#include <qwidget.h>
#include <stb_image.h>

GlWidget::GlWidget(QWidget* parent) : QOpenGLWidget(parent) {
  QTimer* renderTimer = new QTimer(this);
  connect(renderTimer, &QTimer::timeout, this,
          QOverload<>::of(&GlWidget::update));
  renderTimer->start(16);
  testModelPath = "assets/backpack/backpack.obj";
}

void GlWidget::initializeGL() {
  QCursor::setPos(mapToGlobal(rect().center()));
  setFocus(); // this should be placed in the constructor instead
  timer = new QElapsedTimer();
  timer->start();
  lastFrame = 0.0f;
  initializeOpenGLFunctions();
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glEnable(GL_DEPTH_TEST);

  stbi_set_flip_vertically_on_load(true);
  modelShader =
      new Shader("shaders/model_shader.vs", "shaders/model_shader.fs");
  testCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f),
                          glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
  testModel = new Model(testModelPath);
}

void GlWidget::resizeGL(int w, int h) {

};

void GlWidget::paintGL() {
  float currentFrame = timer->elapsed() / 1000.0f;
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;
  processInput(deltaTime);
  modelShader->use();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glm::mat4 view;
  view = testCamera->GetViewMatrix();
  glm::mat4 projection;
  projection = glm::perspective(glm::radians(testCamera->Zoom), 800.0f / 600.0f,
                                0.1f, 100.0f);
  modelShader->setMat4("view", view);
  modelShader->setMat4("projection", projection);

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
  model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

  modelShader->setMat4("model", model);
  testModel->Draw(*modelShader);
  update();
}

void GlWidget::keyPressEvent(QKeyEvent* e) {
  if (!e->isAutoRepeat()) {
    keys[e->key()] = true;
  }
  switch (e->key()) {
    // i added this case to test, actually it would be better to put it directly
    // in main widget
  case Qt::Key_Escape:
    QCoreApplication::instance()->quit();
  case Qt::Key_Space:
    testCamera->InitialPosition();
  };
}

void GlWidget::keyReleaseEvent(QKeyEvent* e) {
  if (!e->isAutoRepeat()) {
    keys[e->key()] = false;
  }
}

void GlWidget::processInput(float deltaTime) {
  if (keys[Qt::Key_W]) {
    testCamera->ProcessKeyboard(Camera::FORWARD, deltaTime);
  }
  if (keys[Qt::Key_S]) {
    testCamera->ProcessKeyboard(Camera::BACKWARD, deltaTime);
  }
  if (keys[Qt::Key_A]) {
    testCamera->ProcessKeyboard(Camera::LEFT, deltaTime);
  }
  if (keys[Qt::Key_D]) {
    testCamera->ProcessKeyboard(Camera::RIGHT, deltaTime);
  }
}

void GlWidget::mouseMoveEvent(QMouseEvent* event) {
  float dx = -(event->pos().x() - mapFromGlobal(QCursor::pos()).x());
  float dy = (event->pos().y() - mapFromGlobal(QCursor::pos()).y());

  if (event->buttons() && Qt::RightButton) {
    testCamera->ProcessMouseMovement(dx, dy);
  }
}

void GlWidget::wheelEvent(QWheelEvent* event) {
  // to check
  float degrees = event->angleDelta().y() / 8;
  float steps = degrees / 15;
  if (steps == 0)
    return;
  testCamera->ProcessMouseWheel(steps);
}
