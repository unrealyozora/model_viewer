#ifndef SHADER_H
#define SHADER_H
#include <QOpenGLFunctions>
#include <glm/glm.hpp>
#include <string>
class Shader : protected QOpenGLFunctions {
public:
  unsigned int ID;
  Shader(const std::string& vertexPath, const std::string& fragmentPath);
  void use();
  void setBool(const std::string& name, bool value);
  void setInt(const std::string& name, int value);
  void setFloat(const std::string& name, float value);
  void setVec3(const std::string& name, float x, float y, float z);
  void setVec3(const std::string& name, glm::vec3 vec);
  void setMat4(const std::string& name, glm::mat4 mat);
  void checkShaderCompilation(unsigned int& id);
  void checkShaderLinking(unsigned int& id);
};

#endif // !SHADER_H
