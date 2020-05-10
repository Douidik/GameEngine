#pragma once

class VertexBuffer {
public:
    VertexBuffer() : mId(0) {}

    VertexBuffer(const void *data, GLsizeiptr size);

    inline void bind() const { glBindBuffer(GL_ARRAY_BUFFER, mId); }

    inline void unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

private:
    GLuint mId;
};

