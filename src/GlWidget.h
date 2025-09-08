#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>

class GlWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
  Q_OBJECT
public:
  GlWidget(QWidget *parent) : QOpenGLWidget(parent) {}

  constexpr static float VERTICES[12] = {0.5f,  0.5f,  0.0f,  0.5f,
                                         -0.5f, 0.0f,  -0.5f, -0.5f,
                                         0.0f,  -0.5f, 0.5f,  0.0f};
  constexpr static unsigned int INDICES[6] = {0, 1, 3, 1, 2, 3};
  unsigned int VAO, VBO, EBO;
  unsigned int shaderProgram;
  static const char *VERTEX_SHADER;
  static const char *FRAGMENT_SHADER;
  void checkShaderCompilation(unsigned int &id);
  void checkShaderLinking(unsigned int &id);

protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
};
