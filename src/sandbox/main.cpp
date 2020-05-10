#include "Core.h"
#include "Context/Window.h"
#include "Component/Camera/FreeCameraComponent.h"
#include "Component/Mesh/StaticMeshComponent.h"
#include <Scene/Scene.h>

int main() {
    Core::Init::ContextParams params(3, 4, "Sandbox Application", 1280, 720);
    assert(Core::Initialize(params));

    Shader staticMeshShader("shaders/StaticMesh.vs.glsl", "shaders/StaticMesh.fs.glsl");
    Renderer::SetShader<StaticMeshComponent>(&staticMeshShader);
    Shader skeletalMeshShader("shaders/SkeletalMesh.vs.glsl", "shaders/SkeletalMesh.fs.glsl");
    Renderer::SetShader<SkeletalMeshComponent>(&skeletalMeshShader);

    GameObject player("player");
    FreeCameraComponent camera("camera", 3.0f, 0.5, 90);
    player.addComponent(&camera);

    GameObject model("model");
    StaticMeshComponent mesh("mesh", "../resources/models/suzanne/suzanne.obj");
    model.addComponent(&mesh);

    Scene world("World");
    world.addGameObject(&model);
    world.addGameObject(&player);

    Renderer::SetCamera(&camera);

    while (Window::GetIsRunning()) {
        Renderer::Update();
        world.update();
        Window::Update();
    }

    return 0;
}
