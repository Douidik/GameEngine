#include "EnginePCH.h"
#include "CameraComponent.h"

glm::mat4 ICameraComponent::CreateTransformMatrix() {
    glm::mat4 matrix(1.0f);

    matrix = glm::rotate(matrix, glm::radians(Rotation.x), {1, 0, 0});
    matrix = glm::rotate(matrix, glm::radians(Rotation.y), {0, 1, 0});
    matrix = glm::rotate(matrix, glm::radians(Rotation.z), {0, 0, 1});

    matrix = glm::translate(matrix, -Position);

    return matrix;
}

glm::mat4 ICameraComponent::CreateProjectionMatrix() {
    return glm::perspective(glm::radians(mFieldOfView), 16.0f / 9.0f, 0.001f, 10000.0f);
}

ICameraComponent::ICameraComponent(const std::string &name, float speed, float sensitivity, float fieldOfView, int tags)
        : IComponent(name, ComponentTag::Camera | tags), mLastMousePosition(0.0), mSpeed(speed),
          mSensitivity(sensitivity), mFieldOfView(fieldOfView) {
    Input::LockMouse();
}

void ICameraComponent::update() {
    move();
    look();
}
