#include "Light.h"

Light::Light() {
  ambient = glm::vec3(0.0f, 1.0f, 1.0f);
  diffuse = glm::vec3(0.785f, 0.329f, 0.989f);
  specular = glm::vec3(0.32f, 0.54f, 0.78f);
}

const glm::vec3& Light::getAmbient() const { return ambient; }
const glm::vec3& Light::getDiffuse() const { return diffuse; }
const glm::vec3& Light::getSpecular() const { return specular; }

void Light::setSpecular(const glm::vec3& _specular) { specular = _specular; }
void Light::setAmbient(const glm::vec3& _ambient) { ambient = _ambient; }
void Light::setDiffuse(const glm::vec3& _diffuse) { diffuse = _diffuse; }

void Light::changeColor() {
  setAmbient(randomColor());
  setDiffuse(randomColor());
  setSpecular(randomColor());
}

glm::vec3 Light::randomColor() const {
  // TEST! THIS IS NOT RANDOM COLOR, FIX WHEN CONFIRMED WORKING
  return glm::vec3(0.8f, 0.5f, 0.4f);
}
