#include <QOpenGLFunctions_3_3_Core>
#include <glm/vec3.hpp>

class Light : public QOpenGLFunctions_3_3_Core {
private:
  glm::vec3 pos;
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
  glm::vec3 direction;

public:
  Light();
  const glm::vec3& getAmbient();
  const glm::vec3& getDiffuse();
  const glm::vec3& getSpecular();
  const glm::vec3& getDirection();
  const glm::vec3& getPos();
};
