#include "GlWidget.h"
#include "Camera/Camera.h"
#include "Shader/Shader.h"
#include "Texture/Texture.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/trigonometric.hpp"
#include <QDebug>
#include <QKeyEvent>
#include <QOpenGLContext>
#include <QTimer>
#include <qnamespace.h>
#include <qopenglext.h>
#include <stb_image.h>

GlWidget::GlWidget(QWidget* parent) : QOpenGLWidget(parent) {
  QTimer* renderTimer = new QTimer(this);
  connect(renderTimer, &QTimer::timeout, this,
          QOverload<>::of(&GlWidget::update));
  renderTimer->start(16);
}

void GlWidget::initializeGL() {
  setFocus(); // this should be placed in the constructor instead
  timer = new QElapsedTimer();
  timer->start();
  lastFrame = 0.0f;
  initializeOpenGLFunctions();
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glEnable(GL_DEPTH_TEST);

  testShader = new Shader("shaders/test.vs", "shaders/test.fs");
  testCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f),
                          glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GlWidget::VERTICES), GlWidget::VERTICES,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                        (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  texture1 = new Texture("assets/container.jpg", GL_TEXTURE0);
  texture2 = new Texture("assets/awesomeface.png", GL_TEXTURE1);

  testShader->use();
  testShader->setInt("texture1", 0);
  testShader->setInt("texture2", 1);
}

void GlWidget::resizeGL(int w, int h) {

};

void GlWidget::paintGL() {
  float currentFrame = timer->elapsed() / 1000.0f;
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;
  processInput(deltaTime);
  testShader->use();
  glActiveTexture(GL_TEXTURE0);
  texture1->bind();

  glActiveTexture(GL_TEXTURE1);
  texture2->bind();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glm::mat4 view;
  view = testCamera->GetViewMatrix();
  glm::mat4 projection;
  projection = glm::perspective(glm::radians(testCamera->Zoom), 800.0f / 600.0f,
                                0.1f, 100.0f);
  testShader->setMat4("view", view);
  testShader->setMat4("projection", projection);

  glBindVertexArray(VAO);
  for (unsigned int i = 0; i < 10; i++) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, cubePositions[i]);
    float angle = 20.0f * i;
    model =
        glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    testShader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }
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
