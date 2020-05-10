#pragma once

#include "EnginePCH.h"

struct Transform {
    Transform() : Position(0.0), Rotation(0.0), Scale(1.0), ParentTransform(nullptr) {}

    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::vec3 Scale;

    std::vector<Transform *> ChildTransforms;

    void setParentTransform(Transform *parentTransform) {
        parentTransform->ChildTransforms.push_back(this);
        ParentTransform = parentTransform;
    }

    Transform *getParentTransform() {
        return ParentTransform;
    }

    virtual glm::mat4 CreateTransformMatrix() {
        //Transform Matrix = IdentityMatrix * ScaleMatrix * RotateMatrix * Translate

        glm::mat4 matrix(1.0f);

        matrix = glm::scale(matrix, Scale);

        matrix = glm::rotate(matrix, Rotation.x, {1, 0, 0});
        matrix = glm::rotate(matrix, Rotation.y, {0, 1, 0});
        matrix = glm::rotate(matrix, Rotation.z, {0, 0, 1});

        matrix = glm::translate(matrix, Position);

        if (ParentTransform != nullptr)
            matrix = ParentTransform->CreateTransformMatrix() * matrix;

        return matrix;
    }

private:
    Transform *ParentTransform;
};  