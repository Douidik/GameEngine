#pragma once

#include "EnginePCH.h"

#define BIT(x) (1 << x)

namespace Util {

    static GLsizeiptr GetSizeOfGLType(unsigned int GLType) {
        switch (GLType) {
            case GL_UNSIGNED_INT :
                return sizeof(GLuint);
            case GL_UNSIGNED_BYTE:
                return sizeof(GLubyte);
            case GL_FLOAT         :
                return sizeof(GLfloat);
            case GL_DOUBLE         :
                return sizeof(GLdouble);
            case GL_INT             :
                return sizeof(GLint);
            case GL_BYTE         :
                return sizeof(GLbyte);
                //Type is not allowed:
            default                 :
                std::cerr << "Type is not allowed." << std::endl;
                assert(0);
                return 0;
        }
    }

    template<typename T, typename Allocator>
    static size_t GetSizeOfVector(std::vector<T, Allocator> const &v) {
        return v.size() * sizeof(T);
    }

    template<typename T>
    static size_t GetLengthOfArray(T *arr) {
        return sizeof(arr) / sizeof(T);
    }


    template<typename T, typename U>
    bool CheckCast(T *in) {
        return dynamic_cast<U *>(in) != nullptr;
    }

#define RESOURCE_PATH(path) "../resources/" + path
}