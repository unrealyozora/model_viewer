#include "Light.h"

Light::Light() {
  pos = glm::vec3(1.2f, 1.0f, 0.0f);
  direction = glm::vec3(-0.2f, -1.0f, -0.3f);
  ambient = glm::vec3(0.0f, 1.0f, 1.0f);
  diffuse = glm::vec3(0.785f, 0.329f, 0.989f);
  specular = glm::vec3(0.32f, 0.54f, 0.78f);
}

const glm::vec3& Light::getPos() { return pos; }
const glm::vec3& Light::getDirection() { return direction; }
const glm::vec3& Light::getAmbient() { return ambient; }
const glm::vec3& Light::getDiffuse() { return diffuse; }
const glm::vec3& Light::getSpecular() { return specular; }
