#pragma once

#include "Buffer/VertexBuffer.h"
#include "Buffer/ElementBuffer.h"
#include "Shader.h"

struct Layout {
    Layout(const char *name, GLint size, GLenum type, GLboolean normalized = false)
            : Name(name), Size(size), Type(type), Normalized(normalized) {}

    const char *Name;
    GLint Size;
    GLenum Type;
    GLboolean Normalized;

    ///////////// Parsed by VertexArray class /////////////////
    int Location;
    GLuint Offset;
};

struct LayoutArray {
    LayoutArray() = default;

    LayoutArray(std::vector<Layout> layouts)
            : Info(layouts), Stride(0) {}

    std::vector<Layout> Info;

    ///////////// Parsed by VertexArray class /////////////////
    GLsizei Stride;
};

class VertexArray {
public:
    VertexArray();

    void addBuffer(const VertexBuffer &vertexBuffer, LayoutArray &layoutArray, Shader &shader);

    inline void bind() const { glBindVertexArray(mId); }

    inline void unbind() const { glBindVertexArray(0); }

private:
    void addFloatLayout(Layout &layout, GLsizeiptr stride);

    void addIntLayout(Layout &layout, GLsizeiptr stride);

private:
    GLuint mId;
};

