#ifndef BASE_LIGHT_H
#define BASE_LIGHT_H
#include <QOpenGLFunctions_3_3_Core>
#include <glm/vec3.hpp>

class Light : public QOpenGLFunctions_3_3_Core {
private:
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;

public:
  Light();
  const glm::vec3& getAmbient() const;
  const glm::vec3& getDiffuse() const;
  const glm::vec3& getSpecular() const;

  void setAmbient(const glm::vec3& _ambient);
  void setDiffuse(const glm::vec3& _diffuse);
  void setSpecular(const glm::vec3& _specular);

  void changeColor();
  glm::vec3 randomColor() const;
};

#endif // !BASE_LIGHT_H
