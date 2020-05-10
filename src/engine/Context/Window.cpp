#include "EnginePCH.h"
#include "Window.h"

WindowPtr Window::sWindowPtr;
bool Window::sIsRunning;
double Window::sDeltaTime, Window::sLastFrameTime;

bool Window::Initialize(unsigned int windowWidth, unsigned int windowHeight, const char *windowName) {
    sWindowPtr.reset(glfwCreateWindow(windowWidth, windowHeight, windowName, nullptr, nullptr));

    if (sWindowPtr.get() == nullptr) {
        std::cerr << "Failed to create the window" << std::endl;
        assert(0);
        return false;
    }

    glfwMakeContextCurrent(Get());

    Window::sIsRunning = true;
    Window::sDeltaTime = Window::sLastFrameTime = 0.0;

    return true;
}

void Window::Update() {
    double frameTime = glfwGetTime();
    sDeltaTime = frameTime - sLastFrameTime;
    sLastFrameTime = frameTime;

    if (glfwWindowShouldClose(Get())) {
        Window::sIsRunning = false;
    }
    glfwSwapBuffers(Get());
    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
