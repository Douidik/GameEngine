#include "EnginePCH.h"
#include "ElementBuffer.h"
#include "Util/Util.h"

ElementBuffer::ElementBuffer(const void *data, unsigned int count)
        : mCount(count) {
    glGenBuffers(1, &mId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mId);
    GLsizeiptr size = count * Util::GetSizeOfGLType(GL_UNSIGNED_INT);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
