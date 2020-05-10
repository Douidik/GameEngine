#pragma once

class ElementBuffer {
public:
    ElementBuffer() : mId(0), mCount(0) {}

    ElementBuffer(const void *data, unsigned int count);

    inline void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId); }

    inline void unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

    inline unsigned int getCount() const { return mCount; }

private:
    GLuint mId;
    unsigned int mCount;
};
