#ifndef MESH_H
#define MESH_H

#include "../Shader/Shader.h"
#include <QOpenGLFunctions_3_3_Core>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <string>
#include <vector>

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoord;
};

struct Texture {
  unsigned int ID;
  std::string type;
  std::string path;
};

class Mesh : public QOpenGLFunctions_3_3_Core {
public:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;

  Mesh(const std::vector<Vertex>& vertices,
       const std::vector<unsigned int>& indices,
       const std::vector<Texture>& textures);
  void Draw(Shader& shader);

private:
  unsigned int VAO, VBO, EBO;
  void setupMesh();
};

#endif // !MESH_H
