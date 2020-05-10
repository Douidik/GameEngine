#pragma once

#include "Primitives/Component.h"
#include "Util/Math.h"
#include "Util/Input.h"


class ICameraComponent : public IComponent {
public:
    virtual glm::mat4 CreateTransformMatrix() override;

    virtual glm::mat4 CreateProjectionMatrix();

protected:
    ICameraComponent(const std::string &name, float speed, float sensitivity, float fieldOfView, int tags = 0);

private:
    virtual void update() override;

protected:
    virtual void move() = 0;

    virtual void look() = 0;

protected:
    glm::dvec2 mLastMousePosition;
    float mSpeed;
    float mSensitivity;
    float mFieldOfView;
};

