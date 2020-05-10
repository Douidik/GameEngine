#pragma once

#include "EnginePCH.h"
#include "Component.h"
#include "Graphics/Renderer.h"

class GameObject : public Transform {
public:
    GameObject(const std::string &name) {
        setName(name);
    }

    //Components modifiers:
public:
    void addComponent(IComponent *pComponent) {
        if (pComponent != nullptr) {
            //we don't set the parent transform if the component is a camera
            pComponent->setParentTransform(this);
            mComponents.push_back(pComponent);

            if (pComponent->hasTag(ComponentTag::Drawable)) {
                Renderer::AddDrawable(pComponent->Cast<IDrawableComponent>());
            }
        } else {
            std::cerr << "Component is nullptr" << std::endl;
        }
    }

    void removeComponent(IComponent *pComponent) {
        bool isFound = false;
        mComponents.erase(std::remove_if(mComponents.begin(), mComponents.end(), [&](IComponent *component) {
            isFound = pComponent == component;
            return isFound;
        }));
        if (isFound) {
            if (pComponent->hasTag(ComponentTag::Drawable))
                Renderer::DeleteDrawable(pComponent->Cast<IDrawableComponent>());
        } else {
            std::cerr << "Failed to find component: \"" << pComponent->getName() << "\" in game object: \"" << mName
                      << "\"." << std::endl;
        }
    }

    void removeComponent(const std::string &name) {
        bool isFound = false;
        mComponents.erase(std::remove_if(mComponents.begin(), mComponents.end(), [&](IComponent *component) {
            isFound = component->getName() == name;
            return isFound;
        }));
        if (isFound) {
            //Wip delete from renderer if is drawable
        } else {
            std::cerr << "Failed to find component: \"" << name << "\" in game object: \"" << mName << "\"."
                      << std::endl;
        }
    }

    IComponent *getComponent(const std::string &name) {
        bool isFound = false;
        std::vector<IComponent *>::iterator it = std::find_if(mComponents.begin(), mComponents.end(),
                                                              [&](IComponent *component) {
                                                                  isFound = component->getName() == name;
                                                                  return isFound;
                                                              });
        if (isFound) {
            return *it;
        } else {
            std::cerr << "Failed to find component: \"" << name << "\" in game object: \"" << mName << "\"."
                      << std::endl;
        }
    }

    virtual void update() {
        std::for_each(mComponents.begin(), mComponents.end(),
                      [&](IComponent *component) { if (component != nullptr) { component->update(); }});
    }

public:
    inline std::string getName() const { return mName; }

    inline void setName(const std::string &name) { mName = name; }

private:
    std::string mName;

private:
    std::vector<IComponent *> mComponents;

};