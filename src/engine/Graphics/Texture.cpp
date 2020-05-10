#include "EnginePCH.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION

#include <stb/stb_image.h>

Texture::Texture(const std::string &filepath, const std::string &type, GLint slot)
        : mSlot(slot), mFilePath(filepath), mType(type) {

    mUniformName = "uTexture" + mType + std::to_string(mSlot);

    glGenTextures(1, &mId);
    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int w, h, bpp;
    stbi_uc *data = stbi_load(filepath.c_str(), &w, &h, &bpp, 4);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    } else {
        std::string errorMessage = "Failed to load texture: " + filepath;
        std::cerr << errorMessage;
        assert(0); // Texture not found
    }

    stbi_image_free(data);
}