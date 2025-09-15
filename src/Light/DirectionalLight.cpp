#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() {
  direction = glm::vec3(-0.2f, -1.0f, -0.3f);
};

const glm::vec3& DirectionalLight::getDirection() const { return direction; }
