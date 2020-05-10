#include "EnginePCH.h"
#include "VertexArray.h"
#include "Util/Util.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &mId);
}

void VertexArray::addBuffer(const VertexBuffer &vertexBuffer, LayoutArray &layoutArray, Shader &shader) {
    glBindVertexArray(mId);
    vertexBuffer.bind();
    shader.bind();

    GLsizeiptr currentOffset = 0;

    std::for_each(layoutArray.Info.begin(), layoutArray.Info.end(), [&](Layout &layout) {
        layout.Location = shader.getLayoutLocation(layout.Name);
        layout.Offset = static_cast<GLuint>(currentOffset);
        currentOffset += layout.Size * Util::GetSizeOfGLType(layout.Type);
    });

    layoutArray.Stride = currentOffset;

    std::for_each(layoutArray.Info.begin(), layoutArray.Info.end(), [&](Layout &layout) {
        switch (layout.Type) {
            case (GL_FLOAT):
                addFloatLayout(layout, layoutArray.Stride);
                break;
            case (GL_INT):
                addIntLayout(layout, layoutArray.Stride);
                break;
            default:
                std::cerr << "type: " << layout.Type << " is not handled." << std::endl;
                assert(0);
                break;
        }
    });
}

void VertexArray::addFloatLayout(Layout &layout, GLsizeiptr stride) {
    if (layout.Location != -1) {
        glEnableVertexAttribArray(layout.Location);
        glVertexAttribPointer(layout.Location, layout.Size, GL_FLOAT, layout.Normalized, stride,
                              (GLvoid *) layout.Offset);
        return;
    }
}

void VertexArray::addIntLayout(Layout &layout, GLsizeiptr stride) {
    if (layout.Location != -1) {
        glEnableVertexAttribArray(layout.Location);
        glVertexAttribIPointer(layout.Location, layout.Size, GL_INT, stride, (const void *) layout.Offset);
        return;
    }
}
