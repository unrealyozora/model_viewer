#include "PointLight.h"
#include "glm/ext/matrix_transform.hpp"

unsigned int PointLight::VAO = 0;
unsigned int PointLight::VBO = 0;
bool PointLight::initialized = false;

PointLight::PointLight(const glm::vec3& _position) {
  position = _position;
  initializeOpenGLFunctions();

  constant = 1.0f;
  linear = 0.09f;
  quadratic = 0.032f;

  shader = new Shader("shaders/light_shader.vs", "shaders/light_shader.fs");
  if (!initialized) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);
    initialized = true;
  }
};

const glm::vec3& PointLight::getPosition() const { return position; }
const float& PointLight::getConstant() const { return constant; }
const float& PointLight::getLinear() const { return linear; }
const float& PointLight::getQuadratic() const { return quadratic; }

void PointLight::Draw(const glm::mat4& view, const glm::mat4& projection) {
  shader->use();
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, position);
  model = glm::scale(model, glm::vec3(0.2f));
  shader->setMat4("view", view);
  shader->setMat4("projection", projection);
  shader->setMat4("model", model);
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
}
