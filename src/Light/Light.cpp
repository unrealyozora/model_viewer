#include "Light.h"

Light::Light() {
  ambient = glm::vec3(0.0f, 1.0f, 1.0f);
  diffuse = glm::vec3(0.785f, 0.329f, 0.989f);
  specular = glm::vec3(0.32f, 0.54f, 0.78f);
}

const glm::vec3& Light::getAmbient() const { return ambient; }
const glm::vec3& Light::getDiffuse() const { return diffuse; }
const glm::vec3& Light::getSpecular() const { return specular; }
