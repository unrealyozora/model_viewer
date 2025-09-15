#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H
#include "Light.h"

class DirectionalLight : public Light {
private:
  glm::vec3 direction;

public:
  DirectionalLight();
  const glm::vec3& getDirection() const;
};

#endif // !DIRECTIONAL_LIGHT_H
