#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
private:
  enum cameraMovement { FORWARD, BACKWARD, LEFT, RIGHT };
  static constexpr float YAW = -90.0f;
  static constexpr float PITCH = 0.0f;
  static constexpr float SPEED = 2.5f;
  static constexpr float SENSITIVITY = 0.1f;
  static constexpr float ZOOM = 45.0f;

  void UpdateCameraVectors();

public:
  float Zoom;
  float Pitch;
  float Yaw;
  float MovementSpeed;
  float MouseSensitivity;

  glm::vec3 Position;
  glm::vec3 Front;
  glm::vec3 Up;
  glm::vec3 Right;
  glm::vec3 WorldUp;

  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
         float pitch = PITCH);

  Camera(float posX, float posY, float posZ, float upX, float upY, float upZ,
         float yaw, float pitch);

  glm::mat4 GetViewMatrix();
};

#endif // !CAMERA_H
