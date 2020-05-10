#pragma once

#include "EnginePCH.h"
#include "Context/Window.h"

namespace Input {

    static bool IsKeyPressed(unsigned int key) {
        return (glfwGetKey(Window::Get(), key) == GLFW_PRESS);
    }

    static glm::dvec2 GetMousePosition() {
        glm::dvec2 tmpMousePos;
        glfwGetCursorPos(Window::Get(), &tmpMousePos.x, &tmpMousePos.y);
        return tmpMousePos;
    }

    static void LockMouse() {
        //if (glfwGetInputMode(Window::Get(), GLFW_CURSOR) != GLFW_CURSOR_DISABLED)
        //    glfwSetInputMode(Window::Get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        //glfwSetCursorPos(Window::Get(), Window::GetWidth<double>() / 2, Window::GetHeight<double>() / 2);
    }

    static void UnlockMouse() {
        if (glfwGetInputMode(Window::Get(), GLFW_CURSOR) != GLFW_CURSOR_NORMAL)
            glfwSetInputMode(Window::Get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

}