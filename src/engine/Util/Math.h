#pragma once

#include "EnginePCH.h"
#include <assimp/types.h>

namespace Util {
    namespace Math {

        template<typename T>
        static void Clamp(T &x, const T &minVal, const T &maxVal) {
            //x = (x <= minVal ? minVal : x >= maxVal ? maxVal : x);
            x = std::max(minVal, std::min(x, maxVal));
        }

        template<typename T>
        static void ClampLoop(T &x, const T &minVal, const T &maxVal) {
            if (x >= maxVal) {
                x = minVal;
            } else if (x <= minVal) {
                x = maxVal;
            }
        }

        static glm::mat3 AiMat3x3ToGlm(const aiMatrix3x3 &src) {
            glm::mat3 dest;
            dest[0][0] = src.a1;
            dest[1][0] = src.a2;
            dest[2][0] = src.a3;
            dest[0][1] = src.b1;
            dest[1][1] = src.b2;
            dest[2][1] = src.b3;
            dest[0][2] = src.c1;
            dest[1][2] = src.c2;
            dest[2][2] = src.c3;

            return dest;
        }

        static glm::mat4 AiMat4x4ToGlm(const aiMatrix4x4 &src) {
            glm::mat4 dest;
            dest[0][0] = src.a1;
            dest[1][0] = src.a2;
            dest[2][0] = src.a3;
            dest[3][0] = src.a4;
            dest[0][1] = src.b1;
            dest[1][1] = src.b2;
            dest[2][1] = src.b3;
            dest[3][1] = src.b4;
            dest[0][2] = src.c1;
            dest[1][2] = src.c2;
            dest[2][2] = src.c3;
            dest[3][2] = src.c4;
            dest[0][3] = src.d1;
            dest[1][3] = src.d2;
            dest[2][3] = src.d3;
            dest[3][3] = src.d4;

            return dest;
        }

        static glm::vec3 AiVec3ToGlm(const aiVector3D &src) {
            return {src.x, src.y, src.z};
        }

        static glm::vec2 AiVec2ToGlm(const aiVector2D &src) {
            return {src.x, src.y};
        }

        static glm::vec2 AiVec2ToGlm(const aiVector3D &src) {
            return {src.x, src.y};
        }

        static glm::quat AiQuatToGlm(const aiQuaternion &src) {
            return {src.w, src.x, src.y, src.z};
        }
    }
}