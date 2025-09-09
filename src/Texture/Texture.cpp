#include "Texture.h"
#include <gl/gl.h>
#include <stb_image.h>

Texture::Texture(const std::string& path, GLenum textureUnit)
    : unit(textureUnit) {

  initializeOpenGLFunctions();

  glGenTextures(1, &ID);
  glActiveTexture(unit);
  glBindTexture(GL_TEXTURE_2D, ID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  stbi_set_flip_vertically_on_load(true);
  data = stbi_load(path.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    qDebug() << "Failed to load texture";
  }
  stbi_image_free(data);
}

Texture::~Texture() { glDeleteTextures(1, &ID); }

void Texture::bind() {
  glActiveTexture(unit);
  glBindTexture(GL_TEXTURE_2D, ID);
}

unsigned int Texture::getID() const { return ID; }
