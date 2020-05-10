#pragma once

#include "Primitives/GameObject.h"

class Scene {
public:
    Scene(const std::string &name);

    void addGameObject(GameObject *pGameObject);

    void removeGameObject(GameObject *pGameObject);

    void removeGameObject(const std::string &name);

    GameObject *getGameObject(const std::string &name);

    void update();

public:
    inline void setName(const std::string &name) { mName = name; }

    inline std::string getName() const { return mName; }

private:
    std::vector<GameObject *> mGameObjects;
    std::string mName;
};

