#pragma once

struct WindowPtrDtor {
    void operator()(GLFWwindow *window) {
        glfwDestroyWindow(window);
    }
};

typedef std::unique_ptr<GLFWwindow, WindowPtrDtor> WindowPtr;


class Window {
public:
    static bool Initialize(unsigned int windowWidth, unsigned int windowHeight, const char *windowName);

    static void Update();

    inline static bool GetIsRunning() { return sIsRunning; }

    inline static GLFWwindow *Get() { return sWindowPtr.get(); }

    inline static void Close() {
        sIsRunning = false;
        sWindowPtr.release();
    }

    template<typename T>
    inline static T GetDeltaTime() { return static_cast<T>(sDeltaTime); }

    template<typename T>
    inline static T GetWidth() {
        int tmpWidth;
        glfwGetWindowSize(Get(), nullptr, &tmpWidth);
        return static_cast<T>(tmpWidth);
    }

    template<typename T>
    inline static T GetHeight() {
        int tmpHeight;
        glfwGetWindowSize(Get(), nullptr, &tmpHeight);
        return static_cast<T>(tmpHeight);
    }

    inline static float GetAspectRatio() { return GetWidth<float>() / GetHeight<float>(); }

    template<typename T>
    inline static T GetTime() { return glfwGetTime(); }

private:
    static WindowPtr sWindowPtr;
    static bool sIsRunning;

    static double sDeltaTime, sLastFrameTime;
};

