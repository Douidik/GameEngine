#include "EnginePCH.h"
#include "Renderer.h"
#include "Component/Mesh/StaticMeshComponent.h"
#include "Component/Camera/CameraComponent.h"

std::vector<IDrawableComponent *> Renderer::spDrawables;
std::unique_ptr<Shader> Renderer::spStaticMeshShader;
std::unique_ptr<Shader> Renderer::spSkeletalMeshShader;
std::unique_ptr<ICameraComponent> Renderer::spCamera;

template<>
Shader* Renderer::GetShader<StaticMeshComponent>() {
    return spStaticMeshShader.get();
}
template<>
Shader* Renderer::GetShader<SkeletalMeshComponent>() {
    return spSkeletalMeshShader.get();
}

void Renderer::Update() {

    spStaticMeshShader->bind();
    spStaticMeshShader->setUniform("uView", spCamera->CreateTransformMatrix());
    spStaticMeshShader->setUniform("uProj", spCamera->CreateProjectionMatrix());

    spStaticMeshShader->setUniform("uLightPos", { 1,1,1 });
    spStaticMeshShader->setUniform("uViewPos", spCamera->Position);
    spStaticMeshShader->setUniform("uLightColor", { 1,1,1 });

    spStaticMeshShader->setUniform("uAmbientStrength", 0.1);
    spStaticMeshShader->setUniform("uSpecularStrength", 1);
/*
    spSkeletalMeshShader->bind();
    spSkeletalMeshShader->setUniform("uView", spCamera->CreateTransformMatrix());
    spSkeletalMeshShader->setUniform("uProj", spCamera->CreateProjectionMatrix());

    spSkeletalMeshShader->setUniform("uLightPos", {1, 1, 1});
    spSkeletalMeshShader->setUniform("uViewPos", spCamera->Position);
    spSkeletalMeshShader->setUniform("uLightColor", {1, 1, 1});

    spSkeletalMeshShader->setUniform("uAmbientStrength", 0.2);
    spSkeletalMeshShader->setUniform("uSpecularStrength", 1);
    */
}

void Renderer::AddDrawable(IDrawableComponent *ppDrawable) {
    if (ppDrawable != nullptr) {
        spDrawables.push_back(ppDrawable);
    }
}

void Renderer::DeleteDrawable(IDrawableComponent *ppDrawable) {
    if (ppDrawable != nullptr) {
        std::vector<IDrawableComponent *>::iterator it = std::find(spDrawables.begin(), spDrawables.end(),
                                                                   ppDrawable);
        if (it != spDrawables.end()) {
            spDrawables.erase(it);
        } else {
            std::cerr << "Drawable \"" << ppDrawable->getName() << "\"is not in renderer" << std::endl;
        }
    }
}
template<>
void Renderer::SetShader<StaticMeshComponent>(Shader *pShader) {
    spStaticMeshShader.reset(pShader);
}
template<>
void Renderer::SetShader<SkeletalMeshComponent>(Shader *pShader) {
    spSkeletalMeshShader.reset(pShader);
}

