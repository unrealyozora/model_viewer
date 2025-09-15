#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
private:
  enum cameraMovement { FORWARD, BACKWARD, LEFT, RIGHT };
  static constexpr float YAW = -90.0f;
  static constexpr float PITCH = 0.0f;
  static constexpr float SPEED = 1.0f;
  static constexpr float SENSITIVITY = 0.1f;
  static constexpr float ZOOM = 45.0f;
  glm::vec3 INITIAL_POSITION;
  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Up;
  glm::vec3 Right;
  glm::vec3 WorldUp;

  void UpdateCameraVectors();

public:
  friend class GlWidget;
  float Zoom;
  float Pitch;
  float Yaw;
  float MovementSpeed;
  float MouseSensitivity;

  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
         float pitch = PITCH);

  Camera(float posX, float posY, float posZ, float upX, float upY, float upZ,
         float yaw, float pitch);

  glm::mat4 GetViewMatrix();
  glm::vec3 getPosition();
  glm::vec3 getFront();
  glm::vec3 getUp();
  glm::vec3 getRight();
  glm::vec3 getWorldUp();
  glm::vec3 getInitialPosition();

  void ProcessKeyboard(cameraMovement direction, float deltaTime);
  void ProcessMouseMovement(float xoffset, float yoffset,
                            bool constrainPitch = true);
  void ProcessMouseWheel(float yoffset);
  void InitialPosition();
};

#endif // !CAMERA_H
