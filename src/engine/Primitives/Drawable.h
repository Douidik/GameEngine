#pragma once

#include "EnginePCH.h"
#include "Component.h"
#include "Graphics/VertexArray.h"

struct IDrawableComponent : public IComponent {
    IDrawableComponent(const std::string &name, int tags = 0)
            : IComponent(name, ComponentTag::Drawable | tags) {}

protected:
    VertexArray mVertexArray;
    VertexBuffer mVertexBuffer;
    ElementBuffer mElementBuffer;
};