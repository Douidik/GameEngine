#include "EnginePCH.h"
#include "FreeCameraComponent.h"

FreeCameraComponent::FreeCameraComponent(const std::string &name, float speed, float sensitivity, float fieldOfView,
                                         int tags)
        : ICameraComponent(name, speed, sensitivity, fieldOfView, ComponentTag::FreeCamera | tags) {
}

void FreeCameraComponent::move() {
    glm::vec3 movement(0.0f);

    if (Input::IsKeyPressed(GLFW_KEY_W)) {
        movement.x -= cos(glm::radians(Rotation.y + 90));
        movement.y -= sin(glm::radians(Rotation.x));
        movement.z -= sin(glm::radians(Rotation.y + 90));
    }
    if (Input::IsKeyPressed(GLFW_KEY_S)) {
        movement.x += cos(glm::radians(Rotation.y + 90));
        movement.y += sin(glm::radians(Rotation.x));
        movement.z += sin(glm::radians(Rotation.y + 90));
    }

    if (Input::IsKeyPressed(GLFW_KEY_A)) {
        movement.x -= cos(glm::radians(Rotation.y));
        movement.z -= sin(glm::radians(Rotation.y));
    }
    if (Input::IsKeyPressed(GLFW_KEY_D)) {
        movement.x += cos(glm::radians(Rotation.y));
        movement.z += sin(glm::radians(Rotation.y));
    }
    if (Input::IsKeyPressed(GLFW_KEY_SPACE)) {
        movement.y += 1;
    }
    if (Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
        movement.y -= 1;
    }


    Position += movement * mSpeed * Window::GetDeltaTime<float>();
}

void FreeCameraComponent::look() {
    glm::dvec2 mousePosition = Input::GetMousePosition();
    glm::vec2 mouseMovement = {mousePosition.y - mLastMousePosition.y, mousePosition.x - mLastMousePosition.x};
    mLastMousePosition = mousePosition;
    Rotation += glm::vec3(mouseMovement, 0.0) * mSensitivity * Window::GetDeltaTime<float>();

    Util::Math::Clamp<float>(Rotation.x, -90, 90);
    Util::Math::ClampLoop<float>(Rotation.y, 0, 360);
}
