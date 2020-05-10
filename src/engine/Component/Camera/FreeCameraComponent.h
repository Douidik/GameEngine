#pragma once

#include "CameraComponent.h"

class FreeCameraComponent : public ICameraComponent {
public:
    FreeCameraComponent(const std::string &name, float speed, float sensitivity, float fieldOfView, int tags = 0);

protected:
    virtual void move() override;

    virtual void look() override;
};

