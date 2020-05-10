#pragma once

#include "EnginePCH.h"
#include "Primitives/Drawable.h"

#include "Util/Util.h"
#include "Graphics/Renderer.h"

class IMeshComponent : public IDrawableComponent {
protected:
    IMeshComponent(const std::string &name, int tags = 0)
            : IDrawableComponent(name, ComponentTag::Drawable | tags) {}


};

