#ifndef MODEL_H
#define MODEL_H

#include "../Mesh/Mesh.h"
#include "../Shader/Shader.h"
#include <QOpenGLFunctions_3_3_Core>
#include <assimp/material.h>
#include <assimp/scene.h>
#include <memory>

class Model : public QOpenGLFunctions_3_3_Core {
public:
  Model(std::string path);
  void Draw(Shader& shader);

private:
  std::vector<std::unique_ptr<Mesh>> meshes;
  std::string directory;
  std::vector<Texture> textures_loaded;

  void loadModel(std::string path);
  void processNode(aiNode* node, const aiScene* scene);
  std::unique_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);
  std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
                                            std::string typeName);
  unsigned int TextureFromFile(const char* fullPath, bool gamma = false);
};

#endif // !MODEL_H
