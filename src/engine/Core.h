#pragma once

#include "EnginePCH.h"
#include "Context/Window.h"
#include "Graphics/Renderer.h"

namespace Core {

    namespace Clock {
        static void Reset() {
            glfwSetTime(0.0f);
        }

        static double GetTime() {
            return glfwGetTime();
        }
    }

    namespace Init {

        struct ContextParams {
            ContextParams(GLuint glMinorVersion, GLuint glMajorVersion, const char *windowName, GLuint windowWidth,
                          GLuint windowHeight, GLuint msaaFactor = 8)
                    : GLMinorVersion(glMinorVersion),
                      GLMajorVersion(glMajorVersion),
                      WindowName(windowName),
                      WindowWidth(windowWidth),
                      WindowHeight(windowHeight),
                      MsaaFactor(msaaFactor) {}


            GLuint GLMinorVersion;
            GLuint GLMajorVersion;

            const char *WindowName;
            GLuint WindowWidth;
            GLuint WindowHeight;

            GLuint MsaaFactor;
        };

        static bool InitGLFW(ContextParams params) {
            if (!glfwInit()) {
                std::cerr << "Failed to initialize GLFW." << std::endl;
                assert(0);
                return false;
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, params.GLMinorVersion);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, params.GLMajorVersion);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_SAMPLES, params.MsaaFactor);

            return true;
        }

        static bool InitGLEW(ContextParams params) {
            if (glewInit() != GLEW_OK) {
                std::cerr << "Failed to initialize GLEW." << std::endl;
                assert(0);
                glfwTerminate();
                return false;
            }

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);

            return true;
        }

    }

    static bool Initialize(::Core::Init::ContextParams params) {

        int result = 1;
        result *= Init::InitGLFW(params);
        result *= ::Window::Initialize(params.WindowWidth, params.WindowHeight, params.WindowName);
        result *= Init::InitGLEW(params);

        Clock::Reset();

        return (bool) result;
    }

    static void Destroy() {
        Window::Close();
        glfwTerminate();
    }

}