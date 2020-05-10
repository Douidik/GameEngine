#pragma once

#include "Transform.h"
#include "Util/Util.h"

enum class ComponentTag {
    None = 0,

    Drawable = BIT(1),

    Mesh = BIT(2),
    StaticMesh = BIT(3),
    SkeletalMesh = BIT(4),

    Camera = BIT(5),
    FreeCamera = BIT(6)
};

int operator|(ComponentTag tag, int tag2);

int operator&(ComponentTag tag, int tag2);

class IComponent : public Transform {
    friend class GameObject;

protected:
    IComponent(const std::string &name, int tags)
            : mTags(0) {
        setName(name);
        mTags |= tags;
    }

public:
    inline std::string getName() const { return mName; }

    inline void setName(const std::string &name) { mName = name; }

    bool hasTags(std::initializer_list<ComponentTag> tags) {
        int result = 1;

        for (ComponentTag tag : tags) {
            result *= tag | mTags;
        }

        return (bool) result;
    }

    bool hasTag(ComponentTag tag) {
        bool isSame = (tag & (mTags));
        return isSame;
    }

    template<typename T>
    T *Cast() {
        return dynamic_cast<T *>(this);
    }

private:
    virtual void update() = 0;

private:
    std::string mName;
    int mTags;
};