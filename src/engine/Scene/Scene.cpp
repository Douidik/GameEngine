#include "EnginePCH.h"
#include "Scene.h"

Scene::Scene(const std::string &name) {
    setName(name);
}

void Scene::addGameObject(GameObject *pGameObject) {
    if (pGameObject != nullptr)
        mGameObjects.push_back(pGameObject);
    else {
        std::cerr << "Game object is nullptr" << std::endl;
    }
}

void Scene::removeGameObject(GameObject *pGameObject) {
    bool isFound = false;
    mGameObjects.erase(std::remove_if(mGameObjects.begin(), mGameObjects.end(), [&](GameObject *gameObject) {
        isFound = pGameObject == gameObject;
        return isFound;
    }));
    if (!isFound) {
        std::cerr << "Failed to find game object: \"" << pGameObject->getName() << "\" in scene: \"" << mName << "\"."
                  << std::endl;
    }
}

void Scene::removeGameObject(const std::string &name) {
    bool isFound = false;
    mGameObjects.erase(std::remove_if(mGameObjects.begin(), mGameObjects.end(), [&](GameObject *gameObject) {
        isFound = name == gameObject->getName();
        return isFound;
    }));
    if (!isFound) {
        std::cerr << "Failed to find game object: \"" << name << "\" in scene: \"" << mName << "\"." << std::endl;
    }
}

GameObject *Scene::getGameObject(const std::string &name) {
    bool isFound = false;
    std::vector<GameObject *>::iterator it = std::find_if(mGameObjects.begin(), mGameObjects.end(),
                                                          [&](GameObject *gameObject) {
                                                              isFound = name == gameObject->getName();
                                                              return isFound;
                                                          });
    if (isFound) {
        return *it;
    } else {
        std::cerr << "Failed to find game object: \"" << name << "\" in scene: \"" << mName << "\"." << std::endl;
        return nullptr;
    }
}

void Scene::update() {
    std::for_each(mGameObjects.begin(), mGameObjects.end(),
                  [&](GameObject *gameObject) { if (gameObject != nullptr) gameObject->update(); });
}
