#ifndef TEXTURE_H
#define TEXTURE_H
#include <QOpenGLFunctions>
#include <string>

class Texture : public QOpenGLFunctions {
public:
  Texture(const std::string& path, GLenum textureUnit = GL_TEXTURE0);
  ~Texture();

  void bind();
  unsigned int getID() const;

private:
  unsigned char* data;
  unsigned int ID;
  int width, height, nrChannels;
  GLenum unit;
};

#endif // !TEXTURE_H
