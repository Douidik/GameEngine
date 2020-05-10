#pragma once

#include "VertexArray.h"
#include "Buffer/ElementBuffer.h"
#include "Primitives/Drawable.h"
#include "Component/Camera/CameraComponent.h"

class SkeletalMeshComponent;

class StaticMeshComponent;

class Scene;

class Renderer {
public:
    static void Update();

    template<typename T>
    static void DrawMesh(T *pMeshComponent) {
        Shader* pShader = GetShader<T>();
        pShader->bind();
        pShader->setUniform("uModel", pMeshComponent->CreateTransformMatrix());

    }

    template<typename T>
    static void SetShader(Shader *pShader);

    template<typename T>
    static Shader *GetShader();

    inline static void SetCamera(ICameraComponent *pCamera) { spCamera.reset(pCamera); }

    inline static ICameraComponent *GetCamera() { return spCamera.get(); }

    static void AddDrawable(IDrawableComponent *ppDrawable);

    static void DeleteDrawable(IDrawableComponent *ppDrawable);


private:
    static std::unique_ptr<ICameraComponent> spCamera;
    static std::unique_ptr<Shader> spStaticMeshShader;
    static std::unique_ptr<Shader> spSkeletalMeshShader;
    static std::vector<IDrawableComponent *> spDrawables;

};

