#pragma once

class Texture {
public:
    Texture() = default;

    Texture(const std::string &filepath, const std::string &type, GLint slot = 0);

    inline void bind() const {
        glActiveTexture(GL_TEXTURE0 + mSlot);
        glBindTexture(GL_TEXTURE_2D, mId);
    }

    inline static void UnBind() {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    inline const std::string &getUniformName() const { return mUniformName; }

    inline const std::string &getFilePath() const { return mFilePath; }

    inline const GLuint getSlot() const { return mSlot; }

private:
    GLuint mId;
    std::string mFilePath, mType, mUniformName;
    GLint mSlot;

};