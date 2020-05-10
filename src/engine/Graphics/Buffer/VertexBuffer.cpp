#include "EnginePCH.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void *data, GLsizeiptr size) {
    glGenBuffers(1, &mId);
    glBindBuffer(GL_ARRAY_BUFFER, mId);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
